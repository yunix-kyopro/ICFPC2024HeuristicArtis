use crate::instances::Constraint;

pub fn dfs(
    digit: usize,
    base: u32,
    constraints: &[Vec<Constraint>],
    x: &mut [u32],
) -> Option<Vec<u32>> {
    if digit > x.len() {
        return Some(x.iter().copied().collect());
    } else {
        'search: for i in 0..base {
            x[digit] = i;

            for constraints in constraints.iter() {
                let mut ok = false;

                for constraint in constraints.iter() {
                    ok |= constraint.min_digit() < digit || constraint.is_satisfied(x);
                }

                if !ok {
                    continue 'search;
                }
            }

            let result = dfs(digit.wrapping_sub(1), base, constraints, x);

            if let Some(result) = result {
                return Some(result);
            }
        }
    }

    return None;
}
