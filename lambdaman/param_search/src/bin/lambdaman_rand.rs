use ac_library::ModInt;
use anyhow::Result;
use clap::Parser;
use lambdaman::lcg::{solve_lcg, Lcg, LcgResult, MoveOnce, MoveStrategy, MoveTwice};
use lambdaman::problem::Input;
use rayon::iter::{IntoParallelIterator, ParallelIterator as _};

#[derive(Debug, Clone, Parser)]
struct Cli {
    #[clap(short = 'p', long = "problem")]
    problem: usize,
    #[clap(short = 't', long = "move_twice")]
    move_twice: bool,
}

fn main() -> Result<()> {
    let cli = Cli::parse();
    let input_path = format!("../../problem/lambdaman/in/{}.txt", cli.problem);
    let input = Input::read(&std::fs::read_to_string(input_path)?)?;

    let primes = calc_primes(700000, 830584);

    if cli.move_twice {
        search(&input, &primes, cli.problem, MoveTwice, 38053529);
    } else {
        search(&input, &primes, cli.problem, MoveOnce, 78074891);
    }

    Ok(())
}

fn search<T: MoveStrategy + Sync>(
    input: &Input,
    a_list: &[u32],
    problem: usize,
    strategy: T,
    modulus: u32,
) {
    ModInt::set_modulus(modulus);

    let mut best_result_overall: Option<LcgResult> = None;

    for (iter, &a) in a_list.iter().enumerate() {
        let best_result = (1..8336)
            .into_par_iter()
            .map(|seed| {
                let result = solve_lcg(&input, Lcg::new(a, modulus, seed), false, &strategy);
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

        if best_result.remaining == 0 && best_result.end_state.is_some() {
            print!("\x1b[33m");
        }

        println!("lambdaman{} | {}", problem, best_result);
        print!("\x1b[m");

        if (iter + 1) % 100 == 0 {
            let best_result_overall = best_result_overall.unwrap();

            println!();

            if best_result_overall.remaining == 0 && best_result_overall.end_state.is_some() {
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
