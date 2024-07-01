use anyhow::Result;
use lambdaman::{
    grid::{D, L, R, U},
    problem::{Board, Input},
};

fn main() -> Result<()> {
    let input_path = format!("../../problem/lambdaman/in/10.txt");
    let input = Input::read(&std::fs::read_to_string(input_path)?)?;
    let mut operations = vec![];

    const N1: usize = 23;
    const N2: usize = 6;
    const N3: usize = 6;

    for _ in 0..N1 {
        for _ in 0..N2 {
            for _ in 0..N3 {
                operations.push(R);
            }

            operations.push(D);

            for _ in 0..N3 {
                operations.push(R);
            }

            operations.push(U);
        }

        operations.push(D);

        for _ in 0..N2 {
            for _ in 0..N3 {
                operations.push(L);
            }

            operations.push(D);

            for _ in 0..N3 {
                operations.push(L);
            }

            operations.push(U);
        }

        operations.push(D);
    }

    for _ in 0..N1 {
        for _ in 0..N2 {
            for _ in 0..N3 {
                operations.push(R);
            }

            operations.push(U);

            for _ in 0..N3 {
                operations.push(R);
            }

            operations.push(D);
        }

        operations.push(U);

        for _ in 0..N2 {
            for _ in 0..N3 {
                operations.push(L);
            }

            operations.push(U);

            for _ in 0..N3 {
                operations.push(L);
            }

            operations.push(D);
        }

        operations.push(U);
    }

    let board = Board::simulate_all(&input, &operations);

    eprintln!("{}", board);
    eprintln!("score: {}", board.remaining_count());

    return Ok(());
}
