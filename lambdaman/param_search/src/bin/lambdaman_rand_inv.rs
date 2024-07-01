use ac_library::ModInt;
use anyhow::Result;
use clap::Parser;
use itertools::{iproduct, Itertools};
use lambdaman::lcg_inv::{solve_lcg, InvLcg, LcgResult, MoveOnce, MoveStrategy, MoveTwice};
use lambdaman::problem::Input;
use rayon::iter::{IntoParallelRefIterator as _, ParallelIterator as _};

#[derive(Debug, Clone, Parser)]
struct Cli {
    #[clap(short = 'p', long = "problem")]
    problem: usize,
    #[clap(short = 't', long = "move_twice")]
    move_twice: bool,
}

const POW94X1: u32 = 94;
const POW94X2: u32 = POW94X1 * 94;
const POW94X3: u32 = POW94X2 * 94;
const POW94X4: u32 = POW94X3 * 94;

fn main() -> Result<()> {
    let cli = Cli::parse();
    let input_path = format!("../../problem/lambdaman/in/{}.txt", cli.problem);
    let input = Input::read(&std::fs::read_to_string(input_path)?)?;

    if cli.move_twice {
        let primes = calc_primes(3, POW94X4 / 2);
        search(&input, cli.problem, MoveTwice, &primes);
    } else {
        let primes = calc_primes(3, POW94X4);
        search(&input, cli.problem, MoveOnce, &primes);
    }

    Ok(())
}

fn search<T: MoveStrategy + Sync>(input: &Input, problem: usize, strategy: T, primes: &[u32]) {
    let mut best_result_overall: Option<LcgResult> = None;

    let mut iter = 0;

    let prod_a_end =
        iproduct!(2..POW94X1, 1..POW94X1 / strategy.move_per_each() as u32).collect_vec();

    for &modulus in primes.iter().rev() {
        ModInt::set_modulus(modulus);

        iter += 1;
        let best_result = prod_a_end
            .par_iter()
            .map(|&(a, end_state)| {
                let result =
                    solve_lcg(&input, InvLcg::new(a, modulus, end_state), false, &strategy);
                result
            })
            .min_by_key(|result| (result.remaining, result.digits))
            .unwrap();

        let comp_pair = match &best_result_overall {
            Some(result) => {
                (best_result.remaining, best_result.digits) < (result.remaining, result.digits)
            }
            None => true,
        };

        if comp_pair {
            best_result_overall = Some(best_result);
        }

        if best_result.remaining == 0 && best_result.seed.is_some() {
            print!("\x1b[33m");
        }

        println!("lambdaman{} | {}", problem, best_result);
        print!("\x1b[m");

        if iter % 100 == 0 {
            let best_result_overall = best_result_overall.unwrap();

            println!();

            if best_result_overall.remaining == 0 && best_result_overall.seed.is_some() {
                print!("\x1b[33m");
            }

            println!("[Current best] {}", best_result_overall);
            print!("\x1b[m");
            println!();
        }
    }

    println!("lambdaman{} | not found", problem);
}

fn calc_primes(min: u32, max_exclusive: u32) -> Vec<u32> {
    let mut is_prime = vec![true; max_exclusive as usize];
    is_prime[0] = false;
    is_prime[1] = false;

    for i in 2..max_exclusive {
        if is_prime[i as usize] {
            for j in (2 * i..max_exclusive).step_by(i as usize) {
                is_prime[j as usize] = false;
            }
        }
    }

    is_prime
        .iter()
        .enumerate()
        .filter_map(|(i, &is_prime)| {
            if is_prime && i as u32 >= min {
                Some(i as u32)
            } else {
                None
            }
        })
        .collect()
}
