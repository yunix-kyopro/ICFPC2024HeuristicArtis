use crate::grid::{Coord, CoordIndex, Map2d, ADJACENTS};
use anyhow::{anyhow, bail, ensure, Result};
use itertools::Itertools;
use std::fmt::Display;

#[derive(Debug, Clone)]
pub struct Input {
    pub map: Map2d<bool>,
    pub graph: Map2d<[CoordIndex; 4]>,
    pub start: Coord,
    pub height: usize,
    pub width: usize,
}

impl Input {
    pub fn read(s: &str) -> Result<Self> {
        let mut map = vec![];
        let mut start = None;

        let mut s = s.lines();
        let mut first_line = s.next().ok_or(anyhow!("no input"))?.split_whitespace();
        let height = first_line.next().ok_or(anyhow!("no height"))?.parse()?;
        let width = first_line.next().ok_or(anyhow!("no width"))?.parse()?;

        for (row, line) in s.enumerate() {
            let line = line.trim().chars().collect_vec();

            if line.len() == 0 {
                continue;
            }

            ensure!(line.len() == width, "inconsistent line length");

            for (col, &c) in line.iter().enumerate() {
                match c {
                    '.' => {
                        map.push(false);
                    }
                    '#' => {
                        map.push(true);
                    }
                    'L' => {
                        map.push(false);
                        start = Some(Coord::new(row, col));
                    }
                    _ => bail!("invalid character: {}", c),
                }
            }
        }

        let Some(start) = start else {
            bail!("no start position found")
        };

        let map = Map2d::new(map, height, width);
        let mut graph = Map2d::new_with([CoordIndex(0); 4], height, width);

        for row in 0..height {
            for col in 0..width {
                let coord = Coord::new(row, col);
                for (i, &diff) in ADJACENTS.iter().enumerate() {
                    let next = coord + diff;

                    if next.in_map(height, width) && !map[next] {
                        graph[coord][i] = next.to_index(width);
                    } else {
                        graph[coord][i] = coord.to_index(width);
                    }
                }
            }
        }

        Ok(Self {
            map,
            graph,
            start,
            height,
            width,
        })
    }
}

#[derive(Debug, Clone)]
pub struct Board<'a> {
    pub visited: Map2d<bool>,
    pub current: CoordIndex,
    pub input: &'a Input,
}

impl<'a> Board<'a> {
    pub fn init(input: &'a Input) -> Self {
        let mut visited = Map2d::new_with(false, input.height, input.width);
        visited[input.start] = true;

        Self {
            visited,
            input,
            current: input.start.to_index(input.width),
        }
    }

    pub fn move_to(&mut self, dir: usize) {
        let next = self.input.graph[self.current][dir];
        self.visited[next] = true;
        self.current = next;
    }

    pub fn simulate_all(input: &'a Input, moves: &[usize]) -> Self {
        let mut board = Self::init(input);

        for &dir in moves {
            board.move_to(dir);
        }

        board
    }

    pub fn remaining_count(&self) -> usize {
        self.visited
            .iter()
            .zip(self.input.map.iter())
            .filter(|(&visited, &wall)| !visited && !wall)
            .count()
    }

    pub fn all_visited(&self) -> bool {
        self.visited
            .iter()
            .zip(self.input.map.iter())
            .all(|(&visited, &wall)| visited || wall)
    }
}

impl<'a> Display for Board<'a> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for row in 0..self.visited.height {
            for col in 0..self.visited.width {
                let coord = Coord::new(row, col).to_index(self.input.width);
                let c = if coord == self.current {
                    'L'
                } else if self.visited[coord] {
                    'o'
                } else if self.input.map[coord] {
                    '#'
                } else {
                    'x'
                };

                write!(f, "{}", c)?;
            }

            writeln!(f)?;
        }

        Ok(())
    }
}
