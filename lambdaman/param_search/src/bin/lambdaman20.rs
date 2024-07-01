use anyhow::Result;
use lambdaman::grid::{D, L, R, U};
use lambdaman::problem::{Board, Input};
use std::fs::File;
use std::io::Write;

const DIR: [usize; 4] = [L, D, R, U];

fn main() -> Result<()> {
    let input_path = "../../problem/lambdaman/in/20.txt";
    let input = Input::read(&std::fs::read_to_string(input_path)?)?;
    let mut moves = vec![];
    solve_dfs(&input, 64, 1, 1, &mut moves);

    let board = Board::simulate_all(&input, &moves);

    println!("visited_all: {}", board.all_visited());

    let visited_path = "./visited.txt";
    let mut file = File::create(visited_path)?;

    write!(file, "{}", board)?;

    Ok(())
}

fn solve_dfs(input: &Input, len: usize, back: usize, prev_dir: usize, moves: &mut Vec<usize>) {
    if len == 2 {
        return;
    }

    for i in 0..4 {
        for _ in 0..len {
            moves.push(DIR[(prev_dir + i + 3) % 4]);
        }

        solve_dfs(
            input,
            len / 2,
            if i == 3 { 0 } else { 1 },
            (prev_dir + i + 3) % 4,
            moves,
        );

        for _ in 0..len - back {
            moves.push(DIR[(prev_dir + i + 1) % 4]);
        }
    }
}
