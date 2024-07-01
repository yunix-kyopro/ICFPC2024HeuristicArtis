use anyhow::Result;
use itertools::iproduct;
use lambdaman::{
    common::ChangeMinMax,
    grid::{D, L, R, U},
    problem::{Board, Input},
};
use rand::{Rng as _, SeedableRng};
use rand_pcg::Pcg64Mcg;

fn main() -> Result<()> {
    let input_path = format!("../../problem/lambdaman/in/4.txt");
    let input = Input::read(&std::fs::read_to_string(input_path)?)?;

    let mut best_remaining = usize::MAX;
    let mut best_op1 = vec![];
    let mut best_op2 = vec![];
    let mut rng = Pcg64Mcg::from_entropy();

    for iter in 0..100000 {
        let mut op1 = vec![];
        let mut op2 = vec![];

        for _ in 0..5 {
            let dir = rng.gen_range(0..4);
            op1.push(dir);
            op1.push(dir);
        }

        for _ in 0..5 {
            let dir = rng.gen_range(0..4);

            op2.push(dir);
            op2.push(dir);
        }

        if rng.gen_bool(0.5) {
            std::mem::swap(&mut op1, &mut op2);
        }

        let mut x = concat3(&concat3(&concat3(&op1)));
        let y = concat3(&concat3(&concat3(&op2)));
        x.extend_from_slice(&y);
        let operations = concat3(&concat3(&concat3(&x)));

        let board = Board::simulate_all(&input, &operations);

        let remaining = board.remaining_count();

        if best_remaining.change_min(remaining) {
            best_op1 = op1;
            best_op2 = op2;
        }

        if iter % 1000 == 0 {
            println!("best: {}", best_remaining);
        }
    }

    println!("best: {}", best_remaining);
    println!("{:?}", best_op1);
    println!("{:?}", best_op2);

    return Ok(());
}

fn concat3(s: &[usize]) -> Vec<usize> {
    let mut result = vec![];

    for i in 0..3 {
        if i == 1 {
            for &c in s.iter().skip(3) {
                result.push(c);
            }

            for &c in s.iter().take(3) {
                result.push(c);
            }
        } else {
            for &c in s.iter() {
                result.push(c);
            }
        }
    }

    result
}
