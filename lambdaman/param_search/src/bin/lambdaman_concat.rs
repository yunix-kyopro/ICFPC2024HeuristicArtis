use std::fmt::Display;

use anyhow::Result;
use clap::Parser;
use lambdaman::{
    common::ChangeMinMax,
    grid::DIRECTIONS,
    problem::{Board, Input},
};
use rand::{Rng, SeedableRng as _};
use rand_pcg::Pcg64Mcg;
use rayon::iter::{IntoParallelIterator, ParallelIterator as _};

#[derive(Debug, Clone, Parser)]
struct Cli {
    #[clap(short = 'p', long = "problem")]
    problem: usize,
    #[clap(short = 'l', long = "length")]
    length: usize,
    #[clap(short = 't', long = "move_twice")]
    move_twice: bool,
}

fn main() -> Result<()> {
    let cli = Cli::parse();
    let input_path = format!("../../problem/lambdaman/in/{}.txt", cli.problem);
    let input = Input::read(&std::fs::read_to_string(input_path)?)?;

    let repeat = if cli.move_twice { 2 } else { 1 };
    search(&input, cli.length, repeat);

    Ok(())
}

fn search(input: &Input, length: usize, repeat: usize) {
    let mut states = (0..10000)
        .into_par_iter()
        .map(|_| {
            let mut rng = Pcg64Mcg::from_entropy();
            let state = State::new(27, repeat, length, &mut rng);
            let state = annealing(input, state, 1.0, &mut rng);
            state
        })
        .collect::<Vec<_>>();

    states.sort_by_cached_key(|state| state.calc_score(input));

    for state in states.iter().take(10) {
        let score = state.calc_score(input);
        println!("score: {} | {}", score, state);
    }
}

#[derive(Debug, Clone)]
struct State {
    operations: Vec<usize>,
    outer_repeat_count: usize,
    inner_repeat_count: usize,
    length: usize,
}

impl State {
    fn new(
        outer_repeat_count: usize,
        inner_repeat_count: usize,
        length: usize,
        rng: &mut impl Rng,
    ) -> Self {
        let mut operations = vec![];

        for _ in 0..length {
            operations.push(rng.gen_range(0..4));
        }

        let len = operations.len();

        Self {
            operations,
            outer_repeat_count,
            inner_repeat_count,
            length: len,
        }
    }

    fn calc_score(&self, input: &Input) -> i32 {
        let mut operations =
            Vec::with_capacity(self.length * self.outer_repeat_count * self.inner_repeat_count);

        for _ in 0..self.outer_repeat_count {
            for dir in self.operations.iter().copied() {
                for _ in 0..self.inner_repeat_count {
                    operations.push(dir);
                }
            }
        }

        let board = Board::simulate_all(input, &operations);
        board.remaining_count() as i32
    }
}

impl Display for State {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for &dir in &self.operations {
            write!(f, "{}", DIRECTIONS[dir])?;
        }

        write!(f, " outer {} times, ", self.outer_repeat_count)?;
        write!(f, "inner {} times", self.inner_repeat_count)?;

        Ok(())
    }
}

trait Neigh {
    fn apply(&self, state: &mut State);

    fn revert(&self, state: &mut State);
}

struct ChangeNeigh {
    index: usize,
    dir: usize,
    prev_dir: usize,
}

impl ChangeNeigh {
    fn gen(state: &State, rng: &mut impl Rng) -> Box<dyn Neigh> {
        let index = rng.gen_range(0..state.length);
        let dir = loop {
            let dir = rng.gen_range(0..4);

            if dir != state.operations[index] {
                break dir;
            }
        };

        let prev_dir = state.operations[index];

        Box::new(Self {
            index,
            dir,
            prev_dir,
        })
    }
}

impl Neigh for ChangeNeigh {
    fn apply(&self, state: &mut State) {
        state.operations[self.index] = self.dir;
    }

    fn revert(&self, state: &mut State) {
        state.operations[self.index] = self.prev_dir;
    }
}

struct SwapNeigh {
    index0: usize,
    index1: usize,
}

impl SwapNeigh {
    fn gen(state: &State, rng: &mut impl Rng) -> Box<dyn Neigh> {
        let index0 = rng.gen_range(0..state.length);
        let index1 = loop {
            let i = rng.gen_range(0..state.length);

            if i != index0 {
                break i;
            }
        };

        Box::new(Self { index0, index1 })
    }
}

impl Neigh for SwapNeigh {
    fn apply(&self, state: &mut State) {
        state.operations.swap(self.index0, self.index1);
    }

    fn revert(&self, state: &mut State) {
        state.operations.swap(self.index0, self.index1);
    }
}

fn annealing(input: &Input, initial_solution: State, duration: f64, rng: &mut impl Rng) -> State {
    let mut solution = initial_solution;
    let mut best_solution = solution.clone();
    let mut current_score = solution.calc_score(input);
    let mut best_score = current_score;
    //let init_score = current_score;

    let mut all_iter = 0;
    //let mut valid_iter = 0;
    //let mut accepted_count = 0;
    //let mut update_count = 0;

    let duration_inv = 1.0 / duration;
    let since = std::time::Instant::now();

    let temp0 = 5e0;
    let temp1 = 1e-1;
    let mut inv_temp = 1.0 / temp0;

    loop {
        all_iter += 1;
        if (all_iter & ((1 << 4) - 1)) == 0 {
            let time = (std::time::Instant::now() - since).as_secs_f64() * duration_inv;
            let temp = f64::powf(temp0, 1.0 - time) * f64::powf(temp1, time);
            inv_temp = 1.0 / temp;

            if time >= 1.0 {
                break;
            }
        }

        // 変形
        let neigh = if rng.gen_bool(0.5) {
            ChangeNeigh::gen(&solution, rng)
        } else {
            SwapNeigh::gen(&solution, rng)
        };
        neigh.apply(&mut solution);

        // スコア計算
        let new_score = solution.calc_score(input);
        let score_diff = new_score - current_score;

        if score_diff <= 0 || rng.gen_bool(f64::exp(-score_diff as f64 * inv_temp)) {
            // 解の更新
            current_score = new_score;
            //accepted_count += 1;

            if best_score.change_min(current_score) {
                best_solution = solution.clone();
                //update_count += 1;
            }
        } else {
            // 解のロールバック
            neigh.revert(&mut solution);
        }

        //valid_iter += 1;
    }

    //eprintln!("===== annealing =====");
    //eprintln!("init score : {}", init_score);
    //eprintln!("score      : {}", best_score);
    //eprintln!("all iter   : {}", all_iter);
    //eprintln!("valid iter : {}", valid_iter);
    //eprintln!("accepted   : {}", accepted_count);
    //eprintln!("updated    : {}", update_count);
    //eprintln!("");

    best_solution
}
