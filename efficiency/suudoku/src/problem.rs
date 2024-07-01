use itertools::Itertools;

#[derive(Debug, Clone)]
pub struct Board {
    pub values: Vec<Vec<Option<u32>>>,
    pub h: Vec<u32>,
    pub v: Vec<u32>,
    pub sq: Vec<Vec<u32>>,
}

impl Board {
    pub fn new(init: &[(usize, usize, u32)]) -> Self {
        let values = vec![vec![None; 9]; 9];
        let h = vec![0; 9];
        let v = vec![0; 9];
        let sq = vec![vec![0; 3]; 3];

        let mut state = Self { values, h, v, sq };

        for &(row, col, value) in init.iter() {
            state.place(row, col, value);
        }

        state
    }

    pub fn can_place(&self, row: usize, col: usize, value: u32) -> bool {
        self.values[row][col].is_none()
            && (self.h[row] >> value) & 1 == 0
            && (self.v[col] >> value) & 1 == 0
            && (self.sq[row / 3][col / 3] >> value) & 1 == 0
    }

    pub fn place(&mut self, row: usize, col: usize, value: u32) {
        self.values[row][col] = Some(value);
        self.h[row] |= 1 << value;
        self.v[col] |= 1 << value;
        self.sq[row / 3][col / 3] |= 1 << value;
    }

    pub fn remove(&mut self, row: usize, col: usize) {
        let value = self.values[row][col].unwrap();

        self.values[row][col] = None;
        self.h[row] &= !(1 << value);
        self.v[col] &= !(1 << value);
        self.sq[row / 3][col / 3] &= !(1 << value);
    }
}

pub fn efficient11() -> Board {
    const INPUT: &str = "v12 == 6 && v13 == 4 && v17 == 7 && v25 == 2 && v28 == 3 && v29 == 6 && v33 == 1 && v41 == 2 && v42 == 3 && v45 == 8 && v54 == 7 && v57 == 1 && v59 == 4 && v71 == 9 && v81 == 8 && v88 == 2 && v94 == 4";
    let mut init = vec![];

    for tokens in INPUT.split("&&") {
        let tokens = tokens.split_whitespace().collect_vec();
        let sq = tokens[0].chars().collect_vec();

        let row = sq[1] as usize - '1' as usize;
        let col = sq[2] as usize - '1' as usize;
        let v: u32 = tokens[2].parse().unwrap();
        init.push((row, col, v - 1));
    }

    eprintln!("{:?}", init);
    Board::new(&init)
}
