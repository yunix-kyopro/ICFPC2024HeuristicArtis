use instances::{efficiency10, efficiency7, efficiency8};
use solver::dfs;

pub mod instances;
pub mod solver;

fn main() {
    let instance = efficiency8();
    eprintln!("{:?}", instance.constraints);
    let mut x = vec![0; instance.digits];

    let result = dfs(
        instance.digits - 1,
        instance.base,
        &instance.constraints,
        &mut x,
    );

    let Some(result) = result else {
        return;
    };

    println!("{:?}", result);
    println!("{}", instance.to_value(&result));
}
