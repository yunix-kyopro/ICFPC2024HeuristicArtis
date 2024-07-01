use std::collections::HashSet;

use ac_library::ModInt;

use crate::{
    common::ChangeMinMax,
    problem::{Board, Input},
};

const TURN_LIMIT: usize = 1000000;

#[derive(Debug, Clone, Copy)]
pub struct Lcg {
    a: ModInt,
    modulo: u32,
    state: ModInt,
}

impl Lcg {
    pub fn new(a: u32, modulo: u32, seed: u32) -> Self {
        Self {
            a: ModInt::new(a),
            modulo,
            state: ModInt::new(seed),
        }
    }

    fn next(&mut self) {
        self.state *= self.a;
    }
}

#[derive(Debug, Clone, Copy)]
pub struct LcgResult {
    pub remaining: usize,
    pub a: u32,
    pub modulo: u32,
    pub seed: u32,
    pub end_state: Option<u32>,
    pub digits: u32,
}

impl LcgResult {
    pub fn new(
        remaining: usize,
        a: u32,
        modulo: u32,
        seed: u32,
        input: &Input,
        strategy: &impl MoveStrategy,
    ) -> Self {
        let mul = strategy.move_per_each() as u32;
        let end_state = Self::calc_end_state(remaining, a, modulo, seed, input, strategy);

        let modulo = modulo * mul;
        let seed = seed * mul;
        let digits = calc_digit(a)
            + calc_digit(modulo)
            + calc_digit(seed)
            + calc_digit(end_state.unwrap_or(u32::MAX / 2));

        Self {
            remaining,
            a,
            end_state,
            modulo,
            seed,
            digits,
        }
    }

    fn calc_end_state(
        remaining: usize,
        a: u32,
        modulo: u32,
        seed: u32,
        input: &Input,
        strategy: &impl MoveStrategy,
    ) -> Option<u32> {
        if remaining > 0 {
            return None;
        }

        let mut ok = TURN_LIMIT / strategy.move_per_each();
        let mut ng = 0;

        while ok - ng > 1 {
            let mid = (ok + ng) / 2;
            let mut lcg = Lcg::new(a, modulo, seed);

            let mut board = Board::init(&input);
            for _ in 0..mid {
                let dir = lcg.state.val() % 4;
                lcg.next();
                strategy.apply_move(&mut board, dir as usize);
            }

            let not_visited = board
                .visited
                .iter()
                .zip(input.map.iter())
                .filter(|(&v, &c)| !v && !c)
                .count();

            if not_visited == 0 {
                ok = mid;
            } else {
                ng = mid;
            }
        }

        let mut lcg = Lcg::new(a, modulo, seed);
        let mut board = Board::init(&input);
        let mut states = HashSet::new();
        let mut min_end_state = u32::MAX;

        for _ in 0..ok {
            if !states.insert(lcg.state.val()) {
                return None;
            }

            let dir = lcg.state.val() % 4;
            lcg.next();

            strategy.apply_move(&mut board, dir as usize);
        }

        for _ in ok..TURN_LIMIT / strategy.move_per_each() {
            if !states.insert(lcg.state.val()) {
                continue;
            }

            min_end_state.change_min(lcg.state.val());
            lcg.next();
        }

        Some(min_end_state * strategy.move_per_each() as u32)
    }
}

impl std::fmt::Display for LcgResult {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let end_state = self.end_state.map_or("None".to_string(), |v| v.to_string());

        write!(
            f,
            "remaining: {}, a: {}, modulo: {}, seed: {}, end_state: {}, digits: {}",
            self.remaining, self.a, self.modulo, self.seed, end_state, self.digits
        )
    }
}

pub trait MoveStrategy {
    fn move_per_each(&self) -> usize;

    fn apply_move(&self, board: &mut Board, dir: usize);
}

#[derive(Debug, Clone, Copy)]
pub struct MoveOnce;

impl MoveStrategy for MoveOnce {
    fn move_per_each(&self) -> usize {
        1
    }

    fn apply_move(&self, board: &mut Board, dir: usize) {
        board.move_to(dir);
    }
}

#[derive(Debug, Clone, Copy)]
pub struct MoveTwice;

impl MoveStrategy for MoveTwice {
    fn move_per_each(&self) -> usize {
        2
    }

    fn apply_move(&self, board: &mut Board, dir: usize) {
        board.move_to(dir);
        board.move_to(dir);
    }
}

pub fn solve_lcg(
    input: &Input,
    mut lcg: Lcg,
    print: bool,
    strategy: &impl MoveStrategy,
) -> LcgResult {
    let seed = lcg.state.val();
    let mut board = Board::init(input);
    let move_per_each = strategy.move_per_each();

    for _ in 0..TURN_LIMIT / move_per_each {
        let dir = lcg.state.val() % 4;
        lcg.next();
        strategy.apply_move(&mut board, dir as usize);
    }

    let not_visited = board
        .visited
        .iter()
        .zip(input.map.iter())
        .filter(|(&v, &c)| !v && !c)
        .count();

    if print {
        println!("{}", board);
    }

    LcgResult::new(not_visited, lcg.a.val(), lcg.modulo, seed, input, strategy)
}

fn calc_digit(mut value: u32) -> u32 {
    if value == 0 {
        return 1;
    }

    let mut digit = 0;

    while value > 0 {
        value /= 94;
        digit += 1;
    }

    digit
}
