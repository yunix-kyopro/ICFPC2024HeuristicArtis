use problem::{efficient11, Board};

pub mod problem;

fn main() {
    let mut board = efficient11();
    let result = dfs(0, &mut board);

    let Some(result) = result else {
        return;
    };

    let mut s = String::new();

    for row in 0..9 {
        for col in 0..9 {
            s.push((result.values[row][col].unwrap() as u8 + '1' as u8) as char)
        }
    }

    println!("{:}", s);
}

fn dfs(depth: usize, board: &mut Board) -> Option<Board> {
    if depth == 9 * 9 {
        return Some(board.clone());
    }

    let row = depth / 9;
    let col = depth % 9;

    if board.values[row][col].is_some() {
        if let Some(board) = dfs(depth + 1, board) {
            return Some(board);
        }
    } else {
        for i in 0..9 {
            if board.can_place(row, col, i) {
                board.place(row, col, i);

                if let Some(board) = dfs(depth + 1, board) {
                    return Some(board);
                }

                board.remove(row, col);
            }
        }
    }

    None
}
