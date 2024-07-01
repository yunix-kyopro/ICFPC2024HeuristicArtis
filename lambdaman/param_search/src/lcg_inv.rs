use std::collections::HashSet;

use ac_library::ModInt;

use crate::{
    common::ChangeMinMax,
    problem::{Board, Input},
};

const TURN_LIMIT: usize = 1000000;

#[derive(Debug, Clone, Copy)]
pub struct InvLcg {
    a: ModInt,
    inv_a: ModInt,
    modulo: u32,
    state: ModInt,
}

impl InvLcg {
    pub fn new(a: u32, modulo: u32, end_state: u32) -> Self {
        let a = ModInt::new(a);
        let inv_a = a.inv();

        Self {
            a,
            inv_a,
            modulo,
            state: ModInt::new(end_state),
        }
    }

    fn next(&mut self) {
        self.state *= self.inv_a;
    }
}

#[derive(Debug, Clone, Copy)]
pub struct LcgResult {
    pub remaining: usize,
    pub a: u32,
    pub modulo: u32,
    pub seed: Option<u32>,
    pub end_state: u32,
    pub digits: u32,
}

impl LcgResult {
    pub fn new(
        remaining: usize,
        lcg_init: &InvLcg,
        input: &Input,
        strategy: &impl MoveStrategy,
    ) -> Self {
        let mul = strategy.move_per_each() as u32;
        let end_state = lcg_init.state.val() * mul;
        let modulo = lcg_init.modulo * mul;
        let seed = Self::calc_seed(remaining, lcg_init, input, strategy);

        let digits = calc_digit(lcg_init.a.val())
            + calc_digit(modulo)
            + calc_digit(end_state)
            + calc_digit(seed.unwrap_or(u32::MAX / 2));

        Self {
            remaining,
            a: lcg_init.a.val(),
            end_state,
            modulo,
            seed,
            digits,
        }
    }

    fn calc_seed(
        remaining: usize,
        lcg_init: &InvLcg,
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
            let mut lcg = lcg_init.clone();

            let mut board = Board::init(&input);
            for _ in 0..mid {
                lcg.next();
                let dir = lcg.state.val() % 4;
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

        let mut lcg = lcg_init.clone();
        let mut board = Board::init(&input);
        let mut states = HashSet::new();
        let mut min_seed = u32::MAX;
        states.insert(lcg.state.val());

        for _ in 0..ok {
            lcg.next();
            let dir = lcg.state.val() % 4;
            strategy.apply_move(&mut board, dir as usize);

            if !states.insert(lcg.state.val()) {
                return None;
            }
        }

        for _ in ok..TURN_LIMIT / strategy.move_per_each() {
            lcg.next();

            if !states.insert(lcg.state.val()) {
                continue;
            }

            min_seed.change_min(lcg.state.val());
        }

        Some(min_seed * strategy.move_per_each() as u32)
    }
}

impl std::fmt::Display for LcgResult {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let seed = self.seed.map_or("None".to_string(), |v| v.to_string());

        write!(
            f,
            "remaining: {}, a: {}, modulo: {}, seed: {}, end_state: {}, digits: {}",
            self.remaining, self.a, self.modulo, seed, self.end_state, self.digits
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
    mut lcg: InvLcg,
    print: bool,
    strategy: &impl MoveStrategy,
) -> LcgResult {
    let lcg_init = lcg.clone();
    let mut board = Board::init(input);
    let move_per_each = strategy.move_per_each();

    for _ in 0..TURN_LIMIT / move_per_each {
        lcg.next();
        let dir = lcg.state.val() % 4;
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

    LcgResult::new(not_visited, &lcg_init, input, strategy)
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
