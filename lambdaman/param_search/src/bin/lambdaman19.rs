use anyhow::Result;
use lambdaman::problem::{Board, Input};
use std::fs::File;
use std::io::Write;

fn main() -> Result<()> {
    let input_path = "../../problem/lambdaman/in/19.txt";
    let input = Input::read(&std::fs::read_to_string(input_path)?)?;
    let mut moves = vec![];
    solve_dfs(&input, 64, &mut moves);

    let board = Board::simulate_all(&input, &moves);

    println!("visited_all: {}", board.all_visited());

    let visited_path = "./visited.txt";
    let mut file = File::create(visited_path)?;

    write!(file, "{}", board)?;

    Ok(())
}

fn solve_dfs(input: &Input, len: usize, moves: &mut Vec<usize>) {
    if len == 0 {
        return;
    }

    for dir in 0..4 {
        for _ in 0..len {
            moves.push(dir);
        }

        solve_dfs(input, len / 2, moves);

        for _ in 0..len {
            moves.push(dir ^ 2);
        }
    }
}
