use std::cmp::Reverse;

use itertools::Itertools;
use num_bigint::BigUint;

#[derive(Debug, Clone)]
pub struct Instance {
    pub constraints: Vec<Vec<Constraint>>,
    pub base: u32,
    pub digits: usize,
}

impl Instance {
    fn new(constraints: Vec<Vec<Constraint>>, base: u32, digits: usize) -> Self {
        Self {
            constraints,
            base,
            digits,
        }
    }

    pub fn to_value(&self, x: &[u32]) -> BigUint {
        let mut base = BigUint::new(vec![1]);
        let mul = BigUint::new(vec![self.base]);
        let mut result = BigUint::default();

        for &x in x.iter() {
            result += &BigUint::new(vec![x]) * &base;
            base *= &mul;
        }

        result
    }
}

#[derive(Debug, Clone, Copy)]
pub enum Constraint {
    Literal(usize, u32),
    Eq(usize, usize, bool),
}

impl Constraint {
    pub fn is_satisfied(&self, x: &[u32]) -> bool {
        match *self {
            Constraint::Literal(digit, value) => x[digit] == value,
            Constraint::Eq(digit1, digit2, bool) => (x[digit1] == x[digit2]) == bool,
        }
    }

    pub fn min_digit(&self) -> usize {
        match *self {
            Constraint::Literal(digit, _) => digit,
            Constraint::Eq(digit1, digit2, _) => digit1.min(digit2),
        }
    }
}

pub fn efficiency7() -> Instance {
    const INSTANCE: &str = "!v18 || !v15 && !v14 || !v9 && !v19 || v37 || v12 && !v39 && !v20 || v18 && !v8 || v16 || !v24 && !v29 || !v39 && !v2 || v19 && v15 && !v37 || v19 || !v6 && v25 || !v23 && !v17 || v40 || v21 && !v23 || v35 || v24 && !v30 || !v28 && v15 && !v37 || v19 || v6 && !v3 || !v11 && !v35 || !v3 && !v29 || v39 || v22 && !v27 || !v10 && v28 || !v8 && !v4 || v39 && v10 || v26 && v22 || v14 || v15 && !v13 && v36 || v28 || !v35 && !v8 || v16 || v24 && !v7 || v3 || !v40 && v22 || v14 || v15 && !v13 && !v8 || v16 || v24 && !v19 || v37 || v12 && v10 || !v26 && !v20 || !v18 && !v8 || !v16 && !v3 || v11 || !v23 && !v16 || v37 && !v38 || !v11 && !v31 || v13 || v14 && !v33 || v19 && !v14 || v9 || !v29 && v6 || v16 && v36 || v28 || v35 && !v19 || !v37 && !v5 || v6 && v10 || v26 && !v3 || v11 || v23 && v26 || v37 || !v16 && v22 || v14 || !v15 && v25 || v23 || v38 && v36 || !v28 && !v35 || v3 && !v34 || v35 || !v37 && !v5 || !v6 && !v33 || !v19 && !v17 || v40 || v21 && !v30 || v28 || v4 && !v34 || v35 || v37 && v28 || v8 || v29 && !v21 && !v18 || v15 || v39 && v40 && !v3 || v11 || v23 && !v17 || !v40 && !v35 || v3 && !v33 || v19 && v25 || v23 || !v38 && !v27 || v10 && v36 || v28 || v35 && !v7 || v3 || v40 && !v11 || v35 && v6 || v16 && !v30 || v28 || v4 && !v11 || !v35 && !v32 || v19 && !v37 || !v19 && v26 || !v37 && !v30 || v28 || !v4 && !v21 && !v20 || v18 && !v9 || v31 && v28 || v8 || v29 && !v31 || v13 || !v14 && !v24 || v32 || v35 && v12 || v16 && !v29 || v39 || v22 && !v14 || v9 || v29 && !v39 && !v4 || !v39 && !v37 || v19 || v6 && !v23 || !v35 && !v29 || v39 || !v22 && !v5 || v6 && v40 && v25 || v23 || v38 && !v2 || v19 && v12 || v16 && !v23 || v35 || v24 && !v31 || !v13 && !v34 || !v35 && !v32 || v19 && !v24 || v32 || v35 && v26 || v37 || v16 && !v38 || v11 && !v16 || v37 && !v7 || v3 || v40 && !v4 || v39 && !v7 || !v3 && !v24 || v32 || !v35 && !v34 || v35 || v37 && !v11 || v35 && v1 && !v27 || v10 && !v23 || v35 || !v24 && !v18 || v15 || !v39 && !v19 || v37 || !v12 && v26 || v37 || v16 && v6 || !v16 && !v17 || v40 || !v21 && !v9 || !v31 && !v32 || !v19 && !v38 || v11 && !v9 || v31 && !v14 || v9 || v29 && !v18 || v15 || v39 && v12 || !v16 && !v16 || !v37 && v22 || !v14 && v28 || v8 || !v29 && v1 && !v24 || !v32 && !v2 || !v19 && !v31 || v13 || v14";
    parse_sat(INSTANCE, 40, 2)
}

pub fn efficiency8() -> Instance {
    const INSTANCE: &str = "!v3 || v36 || v7 && !v3 || !v42 || !v48 && !v49 || !v47 || !v41 && v8 || !v40 || v17 && !v21 || !v31 || !v39 && v36 || !v22 || v49 && v27 || v38 || v14 && v15 || !v18 || v6 && v6 || v7 || !v43 && v34 || !v7 || v23 && v2 || v14 || !v13 && v2 || v47 || !v42 && !v33 || !v35 || v3 && v44 || v40 || v49 && v50 || v36 || v31 && !v36 || !v3 || !v37 && v26 || !v29 || v43 && v15 || v29 || !v45 && v24 || !v11 || v18 && !v47 || !v26 || v6 && !v50 || !v33 || !v10 && v32 || v6 || v16 && !v34 || v37 || v41 && v7 || !v28 || !v17 && !v44 || v46 || v19 && v7 || v22 || !v48 && v3 || v39 || v34 && v31 || v46 || !v43 && !v27 || v32 || v23 && v37 || !v50 || !v18 && v20 || v5 || v11 && !v45 || !v24 || v6 && !v34 || !v23 || !v14 && !v22 || v21 || v20 && !v17 || v50 || v24 && !v25 || !v24 || !v27 && v3 || v35 || v21 && !v26 || v47 || !v36 && !v28 || !v45 || v49 && !v21 || !v6 || v12 && !v17 || !v15 || !v39 && v41 || v2 || !v14 && v25 || v36 || !v23 && !v39 || !v3 || !v40 && v50 || v20 || v35 && v27 || v31 || !v39 && v45 || !v15 || !v40 && v34 || v50 || v35 && !v1 || !v48 || v12 && v18 || !v35 || !v30 && v27 || !v24 || !v25 && !v4 || !v33 || !v12 && !v43 || !v24 || !v37 && !v37 || v31 || !v44 && !v9 || !v38 || v14 && v33 || !v16 || v34 && v4 || !v35 || !v5 && !v3 || !v21 || !v19 && !v35 || !v36 || !v29 && v7 || !v43 || v36 && v30 || v14 || v41 && !v35 || !v24 || !v7 && v35 || !v42 || v6 && !v1 || !v15 || v39 && v27 || v49 || !v16 && !v37 || v49 || !v10 && v50 || !v46 || !v3 && !v41 || v20 || v34 && !v1 || v23 || v28 && !v12 || !v30 || !v20 && !v24 || v29 || !v37 && v12 || v5 || !v44 && !v6 || !v2 || v48 && !v2 || !v49 || !v43 && v1 || !v50 || v24 && !v7 || !v50 || !v44 && !v41 || v43 || v4 && v13 || v15 || !v11 && !v3 || !v11 || v23 && v33 || v48 || v41 && v9 || v23 || !v49 && !v43 || v47 || v1 && !v40 || v16 || !v29 && v30 || v19 || v3 && v19 || !v34 || v48 && !v16 || !v44 || v14 && v38 || !v45 || !v12 && !v4 || !v14 || !v31 && !v48 || v35 || !v1 && v45 || !v13 || v19 && v9 || v42 || !v7 && !v1 || !v15 || v8 && !v13 || !v44 || !v14 && !v43 || !v37 || !v31 && !v27 || !v29 || v47 && v7 || v4 || v17 && v7 || v10 || v35 && !v25 || v20 || v17 && v35 || !v5 || !v42 && !v50 || v24 || !v5 && !v21 || !v26 || v2 && !v8 || v45 || !v21 && !v16 || v33 || v49 && !v38 || v6 || v16 && v5 || v21 || v37 && v8 || v38 || v31 && !v21 || v33 || v14 && v20 || v40 || !v5 && !v29 || !v9 || v31 && !v7 || v42 || !v22 && !v48 || v8 || v26 && v48 || !v38 || v33 && !v34 || v49 || v46 && !v14 || !v46 || v25 && !v46 || v4 || v18 && v36 || !v12 || !v31 && v12 || !v18 || v14 && !v7 || v46 || !v16 && v9 || !v8 || v7 && v49 || !v42 || !v22 && v22 || !v15 || v38 && v34 || !v41 || v47 && v22 || !v26 || v32 && !v25 || !v45 || !v21 && !v26 || v32 || !v11 && v15 || v26 || !v25 && !v1 || v46 || v25 && !v14 || !v31 || v30 && !v9 || !v22 || v12 && !v18 || v26 || !v35 && !v16 || !v32 || !v21 && v31 || !v49 || !v21 && v11 || v9 || v41 && !v13 || !v30 || v19 && !v10 || v4 || v6 && !v4 || v3 || !v22 && !v25 || !v50 || !v18 && !v40 || v4 || v9 && v37 || v20 || v46 && !v27 || v22 || !v29 && v34 || v14 || v3 && v3 || !v31 || v20 && !v50 || v2 || !v26 && v17 || !v29 || v38 && !v49 || v12 || !v41 && v15 || !v35 || !v43 && !v22 || !v23 || !v49 && !v9 || v33 || v48 && v26 || v29 || v35 && v27 || !v50 || v37 && !v7 || v46 || !v43 && !v46 || !v37 || !v8 && !v40 || v36 || !v24 && !v44 || v46 || v15 && !v3 || v36 || !v16 && !v48 || v9 || v43 && !v25 || !v4 || v44 && !v22 || v37 || !v7 && !v31 || !v17 || !v22 && !v11 || !v48 || v17 && v23 || v34 || !v28 && v23 || !v48 || !v39 && !v37 || !v1 || !v23 && !v19 || v27 || v14 && !v22 || v33 || !v6 && !v6 || !v32 || !v26 && v18 || !v20 || !v46 && v43 || v22 || v27 && !v13 || v34 || v49 && !v35 || !v46 || v3 && v32 || v39 || !v43 && v6 || !v39 || !v9 && v27 || v39 || !v16 && v25 || !v17 || !v15 && !v43 || v27 || v34 && !v6 || v49 || v5 && !v38 || v11 || v14 && v40 || !v38 || v47 && v37 || !v14 || v17 && v39 || v29 || v36 && !v39 || !v28 || v1 && !v18 || v14 || !v16 && !v40 || v50 || v15 && v37 || !v42 || v18 && !v13 || v31 || v33 && v2 || !v42 || v33 && v8 || !v3 || !v22 && v1 || v23 || !v31 && !v20 || !v45 || v26 && v42 || v11 || v49 && v29 || v11 || !v43 && !v20 || !v21 || v30 && v23 || v45 || !v35 && v38 || !v30 || !v14 && !v9 || v48 || !v29 && v11 || !v18 || !v23 && !v41 || !v1 || !v29 && v5 || v41 || v26 && v44 || !v30 || !v7 && v38 || !v6 || !v41 && v46 || v48 || !v15 && !v18 || !v10 || !v47 && v38 || v46 || !v32 && !v32 || v46 || v12 && v31 || v40 || v14 && !v18 || v2 || v49 && v28 || !v38 || v27 && !v16 || !v21 || v14 && !v29 || v15 || v12 && v49 || v34 || v5 && v14 || v22 || !v12 && v30 || v33 || v20 && !v24 || v22 || v25 && v4 || !v48 || !v23 && !v30 || !v36 || v9 && v44 || v12 || !v35 && v38 || v3 || !v21 && !v11 || v33 || v49";
    parse_sat(INSTANCE, 50, 2)
}

pub fn efficiency10() -> Instance {
    const INSTANCE: &str = "!v11 == v12 && !v11 == v13 && !v11 == v14 && !v11 == v15 && !v11 == v16 && !v11 == v17 && !v11 == v18 && !v11 == v19 && !v11 == v21 && !v11 == v22 && !v11 == v23 && !v11 == v31 && !v11 == v32 && !v11 == v33 && !v11 == v41 && !v11 == v51 && !v11 == v61 && !v11 == v71 && !v11 == v81 && !v11 == v91 && !v12 == v13 && !v12 == v14 && !v12 == v15 && !v12 == v16 && !v12 == v17 && !v12 == v18 && !v12 == v19 && !v12 == v21 && !v12 == v22 && !v12 == v23 && !v12 == v31 && !v12 == v32 && !v12 == v33 && !v12 == v42 && !v12 == v52 && !v12 == v62 && !v12 == v72 && !v12 == v82 && !v12 == v92 && !v13 == v14 && !v13 == v15 && !v13 == v16 && !v13 == v17 && !v13 == v18 && !v13 == v19 && !v13 == v21 && !v13 == v22 && !v13 == v23 && !v13 == v31 && !v13 == v32 && !v13 == v33 && !v13 == v43 && !v13 == v53 && !v13 == v63 && !v13 == v73 && !v13 == v83 && !v13 == v93 && !v14 == v15 && !v14 == v16 && !v14 == v17 && !v14 == v18 && !v14 == v19 && !v14 == v24 && !v14 == v25 && !v14 == v26 && !v14 == v34 && !v14 == v35 && !v14 == v36 && !v14 == v44 && !v14 == v54 && !v14 == v64 && !v14 == v74 && !v14 == v84 && !v14 == v94 && !v15 == v16 && !v15 == v17 && !v15 == v18 && !v15 == v19 && !v15 == v24 && !v15 == v25 && !v15 == v26 && !v15 == v34 && !v15 == v35 && !v15 == v36 && !v15 == v45 && !v15 == v55 && !v15 == v65 && !v15 == v75 && !v15 == v85 && !v15 == v95 && !v16 == v17 && !v16 == v18 && !v16 == v19 && !v16 == v24 && !v16 == v25 && !v16 == v26 && !v16 == v34 && !v16 == v35 && !v16 == v36 && !v16 == v46 && !v16 == v56 && !v16 == v66 && !v16 == v76 && !v16 == v86 && !v16 == v96 && !v17 == v18 && !v17 == v19 && !v17 == v27 && !v17 == v28 && !v17 == v29 && !v17 == v37 && !v17 == v38 && !v17 == v39 && !v17 == v47 && !v17 == v57 && !v17 == v67 && !v17 == v77 && !v17 == v87 && !v17 == v97 && !v18 == v19 && !v18 == v27 && !v18 == v28 && !v18 == v29 && !v18 == v37 && !v18 == v38 && !v18 == v39 && !v18 == v48 && !v18 == v58 && !v18 == v68 && !v18 == v78 && !v18 == v88 && !v18 == v98 && !v19 == v27 && !v19 == v28 && !v19 == v29 && !v19 == v37 && !v19 == v38 && !v19 == v39 && !v19 == v49 && !v19 == v59 && !v19 == v69 && !v19 == v79 && !v19 == v89 && !v19 == v99 && !v21 == v22 && !v21 == v23 && !v21 == v24 && !v21 == v25 && !v21 == v26 && !v21 == v27 && !v21 == v28 && !v21 == v29 && !v21 == v31 && !v21 == v32 && !v21 == v33 && !v21 == v41 && !v21 == v51 && !v21 == v61 && !v21 == v71 && !v21 == v81 && !v21 == v91 && !v22 == v23 && !v22 == v24 && !v22 == v25 && !v22 == v26 && !v22 == v27 && !v22 == v28 && !v22 == v29 && !v22 == v31 && !v22 == v32 && !v22 == v33 && !v22 == v42 && !v22 == v52 && !v22 == v62 && !v22 == v72 && !v22 == v82 && !v22 == v92 && !v23 == v24 && !v23 == v25 && !v23 == v26 && !v23 == v27 && !v23 == v28 && !v23 == v29 && !v23 == v31 && !v23 == v32 && !v23 == v33 && !v23 == v43 && !v23 == v53 && !v23 == v63 && !v23 == v73 && !v23 == v83 && !v23 == v93 && !v24 == v25 && !v24 == v26 && !v24 == v27 && !v24 == v28 && !v24 == v29 && !v24 == v34 && !v24 == v35 && !v24 == v36 && !v24 == v44 && !v24 == v54 && !v24 == v64 && !v24 == v74 && !v24 == v84 && !v24 == v94 && !v25 == v26 && !v25 == v27 && !v25 == v28 && !v25 == v29 && !v25 == v34 && !v25 == v35 && !v25 == v36 && !v25 == v45 && !v25 == v55 && !v25 == v65 && !v25 == v75 && !v25 == v85 && !v25 == v95 && !v26 == v27 && !v26 == v28 && !v26 == v29 && !v26 == v34 && !v26 == v35 && !v26 == v36 && !v26 == v46 && !v26 == v56 && !v26 == v66 && !v26 == v76 && !v26 == v86 && !v26 == v96 && !v27 == v28 && !v27 == v29 && !v27 == v37 && !v27 == v38 && !v27 == v39 && !v27 == v47 && !v27 == v57 && !v27 == v67 && !v27 == v77 && !v27 == v87 && !v27 == v97 && !v28 == v29 && !v28 == v37 && !v28 == v38 && !v28 == v39 && !v28 == v48 && !v28 == v58 && !v28 == v68 && !v28 == v78 && !v28 == v88 && !v28 == v98 && !v29 == v37 && !v29 == v38 && !v29 == v39 && !v29 == v49 && !v29 == v59 && !v29 == v69 && !v29 == v79 && !v29 == v89 && !v29 == v99 && !v31 == v32 && !v31 == v33 && !v31 == v34 && !v31 == v35 && !v31 == v36 && !v31 == v37 && !v31 == v38 && !v31 == v39 && !v31 == v41 && !v31 == v51 && !v31 == v61 && !v31 == v71 && !v31 == v81 && !v31 == v91 && !v32 == v33 && !v32 == v34 && !v32 == v35 && !v32 == v36 && !v32 == v37 && !v32 == v38 && !v32 == v39 && !v32 == v42 && !v32 == v52 && !v32 == v62 && !v32 == v72 && !v32 == v82 && !v32 == v92 && !v33 == v34 && !v33 == v35 && !v33 == v36 && !v33 == v37 && !v33 == v38 && !v33 == v39 && !v33 == v43 && !v33 == v53 && !v33 == v63 && !v33 == v73 && !v33 == v83 && !v33 == v93 && !v34 == v35 && !v34 == v36 && !v34 == v37 && !v34 == v38 && !v34 == v39 && !v34 == v44 && !v34 == v54 && !v34 == v64 && !v34 == v74 && !v34 == v84 && !v34 == v94 && !v35 == v36 && !v35 == v37 && !v35 == v38 && !v35 == v39 && !v35 == v45 && !v35 == v55 && !v35 == v65 && !v35 == v75 && !v35 == v85 && !v35 == v95 && !v36 == v37 && !v36 == v38 && !v36 == v39 && !v36 == v46 && !v36 == v56 && !v36 == v66 && !v36 == v76 && !v36 == v86 && !v36 == v96 && !v37 == v38 && !v37 == v39 && !v37 == v47 && !v37 == v57 && !v37 == v67 && !v37 == v77 && !v37 == v87 && !v37 == v97 && !v38 == v39 && !v38 == v48 && !v38 == v58 && !v38 == v68 && !v38 == v78 && !v38 == v88 && !v38 == v98 && !v39 == v49 && !v39 == v59 && !v39 == v69 && !v39 == v79 && !v39 == v89 && !v39 == v99 && !v41 == v42 && !v41 == v43 && !v41 == v44 && !v41 == v45 && !v41 == v46 && !v41 == v47 && !v41 == v48 && !v41 == v49 && !v41 == v51 && !v41 == v52 && !v41 == v53 && !v41 == v61 && !v41 == v62 && !v41 == v63 && !v41 == v71 && !v41 == v81 && !v41 == v91 && !v42 == v43 && !v42 == v44 && !v42 == v45 && !v42 == v46 && !v42 == v47 && !v42 == v48 && !v42 == v49 && !v42 == v51 && !v42 == v52 && !v42 == v53 && !v42 == v61 && !v42 == v62 && !v42 == v63 && !v42 == v72 && !v42 == v82 && !v42 == v92 && !v43 == v44 && !v43 == v45 && !v43 == v46 && !v43 == v47 && !v43 == v48 && !v43 == v49 && !v43 == v51 && !v43 == v52 && !v43 == v53 && !v43 == v61 && !v43 == v62 && !v43 == v63 && !v43 == v73 && !v43 == v83 && !v43 == v93 && !v44 == v45 && !v44 == v46 && !v44 == v47 && !v44 == v48 && !v44 == v49 && !v44 == v54 && !v44 == v55 && !v44 == v56 && !v44 == v64 && !v44 == v65 && !v44 == v66 && !v44 == v74 && !v44 == v84 && !v44 == v94 && !v45 == v46 && !v45 == v47 && !v45 == v48 && !v45 == v49 && !v45 == v54 && !v45 == v55 && !v45 == v56 && !v45 == v64 && !v45 == v65 && !v45 == v66 && !v45 == v75 && !v45 == v85 && !v45 == v95 && !v46 == v47 && !v46 == v48 && !v46 == v49 && !v46 == v54 && !v46 == v55 && !v46 == v56 && !v46 == v64 && !v46 == v65 && !v46 == v66 && !v46 == v76 && !v46 == v86 && !v46 == v96 && !v47 == v48 && !v47 == v49 && !v47 == v57 && !v47 == v58 && !v47 == v59 && !v47 == v67 && !v47 == v68 && !v47 == v69 && !v47 == v77 && !v47 == v87 && !v47 == v97 && !v48 == v49 && !v48 == v57 && !v48 == v58 && !v48 == v59 && !v48 == v67 && !v48 == v68 && !v48 == v69 && !v48 == v78 && !v48 == v88 && !v48 == v98 && !v49 == v57 && !v49 == v58 && !v49 == v59 && !v49 == v67 && !v49 == v68 && !v49 == v69 && !v49 == v79 && !v49 == v89 && !v49 == v99 && !v51 == v52 && !v51 == v53 && !v51 == v54 && !v51 == v55 && !v51 == v56 && !v51 == v57 && !v51 == v58 && !v51 == v59 && !v51 == v61 && !v51 == v62 && !v51 == v63 && !v51 == v71 && !v51 == v81 && !v51 == v91 && !v52 == v53 && !v52 == v54 && !v52 == v55 && !v52 == v56 && !v52 == v57 && !v52 == v58 && !v52 == v59 && !v52 == v61 && !v52 == v62 && !v52 == v63 && !v52 == v72 && !v52 == v82 && !v52 == v92 && !v53 == v54 && !v53 == v55 && !v53 == v56 && !v53 == v57 && !v53 == v58 && !v53 == v59 && !v53 == v61 && !v53 == v62 && !v53 == v63 && !v53 == v73 && !v53 == v83 && !v53 == v93 && !v54 == v55 && !v54 == v56 && !v54 == v57 && !v54 == v58 && !v54 == v59 && !v54 == v64 && !v54 == v65 && !v54 == v66 && !v54 == v74 && !v54 == v84 && !v54 == v94 && !v55 == v56 && !v55 == v57 && !v55 == v58 && !v55 == v59 && !v55 == v64 && !v55 == v65 && !v55 == v66 && !v55 == v75 && !v55 == v85 && !v55 == v95 && !v56 == v57 && !v56 == v58 && !v56 == v59 && !v56 == v64 && !v56 == v65 && !v56 == v66 && !v56 == v76 && !v56 == v86 && !v56 == v96 && !v57 == v58 && !v57 == v59 && !v57 == v67 && !v57 == v68 && !v57 == v69 && !v57 == v77 && !v57 == v87 && !v57 == v97 && !v58 == v59 && !v58 == v67 && !v58 == v68 && !v58 == v69 && !v58 == v78 && !v58 == v88 && !v58 == v98 && !v59 == v67 && !v59 == v68 && !v59 == v69 && !v59 == v79 && !v59 == v89 && !v59 == v99 && !v61 == v62 && !v61 == v63 && !v61 == v64 && !v61 == v65 && !v61 == v66 && !v61 == v67 && !v61 == v68 && !v61 == v69 && !v61 == v71 && !v61 == v81 && !v61 == v91 && !v62 == v63 && !v62 == v64 && !v62 == v65 && !v62 == v66 && !v62 == v67 && !v62 == v68 && !v62 == v69 && !v62 == v72 && !v62 == v82 && !v62 == v92 && !v63 == v64 && !v63 == v65 && !v63 == v66 && !v63 == v67 && !v63 == v68 && !v63 == v69 && !v63 == v73 && !v63 == v83 && !v63 == v93 && !v64 == v65 && !v64 == v66 && !v64 == v67 && !v64 == v68 && !v64 == v69 && !v64 == v74 && !v64 == v84 && !v64 == v94 && !v65 == v66 && !v65 == v67 && !v65 == v68 && !v65 == v69 && !v65 == v75 && !v65 == v85 && !v65 == v95 && !v66 == v67 && !v66 == v68 && !v66 == v69 && !v66 == v76 && !v66 == v86 && !v66 == v96 && !v67 == v68 && !v67 == v69 && !v67 == v77 && !v67 == v87 && !v67 == v97 && !v68 == v69 && !v68 == v78 && !v68 == v88 && !v68 == v98 && !v69 == v79 && !v69 == v89 && !v69 == v99 && !v71 == v72 && !v71 == v73 && !v71 == v74 && !v71 == v75 && !v71 == v76 && !v71 == v77 && !v71 == v78 && !v71 == v79 && !v71 == v81 && !v71 == v82 && !v71 == v83 && !v71 == v91 && !v71 == v92 && !v71 == v93 && !v72 == v73 && !v72 == v74 && !v72 == v75 && !v72 == v76 && !v72 == v77 && !v72 == v78 && !v72 == v79 && !v72 == v81 && !v72 == v82 && !v72 == v83 && !v72 == v91 && !v72 == v92 && !v72 == v93 && !v73 == v74 && !v73 == v75 && !v73 == v76 && !v73 == v77 && !v73 == v78 && !v73 == v79 && !v73 == v81 && !v73 == v82 && !v73 == v83 && !v73 == v91 && !v73 == v92 && !v73 == v93 && !v74 == v75 && !v74 == v76 && !v74 == v77 && !v74 == v78 && !v74 == v79 && !v74 == v84 && !v74 == v85 && !v74 == v86 && !v74 == v94 && !v74 == v95 && !v74 == v96 && !v75 == v76 && !v75 == v77 && !v75 == v78 && !v75 == v79 && !v75 == v84 && !v75 == v85 && !v75 == v86 && !v75 == v94 && !v75 == v95 && !v75 == v96 && !v76 == v77 && !v76 == v78 && !v76 == v79 && !v76 == v84 && !v76 == v85 && !v76 == v86 && !v76 == v94 && !v76 == v95 && !v76 == v96 && !v77 == v78 && !v77 == v79 && !v77 == v87 && !v77 == v88 && !v77 == v89 && !v77 == v97 && !v77 == v98 && !v77 == v99 && !v78 == v79 && !v78 == v87 && !v78 == v88 && !v78 == v89 && !v78 == v97 && !v78 == v98 && !v78 == v99 && !v79 == v87 && !v79 == v88 && !v79 == v89 && !v79 == v97 && !v79 == v98 && !v79 == v99 && !v81 == v82 && !v81 == v83 && !v81 == v84 && !v81 == v85 && !v81 == v86 && !v81 == v87 && !v81 == v88 && !v81 == v89 && !v81 == v91 && !v81 == v92 && !v81 == v93 && !v82 == v83 && !v82 == v84 && !v82 == v85 && !v82 == v86 && !v82 == v87 && !v82 == v88 && !v82 == v89 && !v82 == v91 && !v82 == v92 && !v82 == v93 && !v83 == v84 && !v83 == v85 && !v83 == v86 && !v83 == v87 && !v83 == v88 && !v83 == v89 && !v83 == v91 && !v83 == v92 && !v83 == v93 && !v84 == v85 && !v84 == v86 && !v84 == v87 && !v84 == v88 && !v84 == v89 && !v84 == v94 && !v84 == v95 && !v84 == v96 && !v85 == v86 && !v85 == v87 && !v85 == v88 && !v85 == v89 && !v85 == v94 && !v85 == v95 && !v85 == v96 && !v86 == v87 && !v86 == v88 && !v86 == v89 && !v86 == v94 && !v86 == v95 && !v86 == v96 && !v87 == v88 && !v87 == v89 && !v87 == v97 && !v87 == v98 && !v87 == v99 && !v88 == v89 && !v88 == v97 && !v88 == v98 && !v88 == v99 && !v89 == v97 && !v89 == v98 && !v89 == v99 && !v91 == v92 && !v91 == v93 && !v91 == v94 && !v91 == v95 && !v91 == v96 && !v91 == v97 && !v91 == v98 && !v91 == v99 && !v92 == v93 && !v92 == v94 && !v92 == v95 && !v92 == v96 && !v92 == v97 && !v92 == v98 && !v92 == v99 && !v93 == v94 && !v93 == v95 && !v93 == v96 && !v93 == v97 && !v93 == v98 && !v93 == v99 && !v94 == v95 && !v94 == v96 && !v94 == v97 && !v94 == v98 && !v94 == v99 && !v95 == v96 && !v95 == v97 && !v95 == v98 && !v95 == v99 && !v96 == v97 && !v96 == v98 && !v96 == v99 && !v97 == v98 && !v97 == v99 && !v98 == v99 && v17 == 6 && v18 == 8 && v25 == 7 && v26 == 3 && v29 == 9 && v31 == 3 && v33 == 9 && v38 == 4 && v39 == 5 && v41 == 4 && v42 == 9 && v51 == 8 && v53 == 3 && v55 == 5 && v57 == 9 && v59 == 2 && v68 == 3 && v69 == 6 && v71 == 9 && v72 == 6 && v77 == 3 && v79 == 8 && v81 == 7 && v84 == 6 && v85 == 8 && v92 == 2 && v93 == 8";
    parse_suudoku(INSTANCE, 81, 9)
}

fn parse_sat(raw_constraints: &str, digits: usize, base: u32) -> Instance {
    let raw_constraints = raw_constraints.split("&&");
    let mut all_constraints = vec![];

    for raw_constraint in raw_constraints {
        let mut constraint = vec![];

        for token in raw_constraint.split_whitespace() {
            if token.starts_with("v") {
                let v: usize = token.replace("v", "").parse().unwrap();
                constraint.push(Constraint::Literal(v - 1, 1));
            } else if token.starts_with("!v") {
                let v: usize = token.replace("!v", "").parse().unwrap();
                constraint.push(Constraint::Literal(v - 1, 0));
            } else {
                assert_eq!(token, "||");
            }
        }

        all_constraints.push(constraint);
    }

    all_constraints
        .sort_unstable_by_key(|c| Reverse(c.iter().map(|c| c.min_digit()).min().unwrap()));

    Instance::new(all_constraints, base, digits)
}

fn parse_suudoku(raw_constraints: &str, digits: usize, base: u32) -> Instance {
    let raw_constraints = raw_constraints.split("&&");
    let mut all_constraints = vec![];

    for raw_constraint in raw_constraints {
        let mut constraint = vec![];
        let tokens = raw_constraint.split_whitespace().collect_vec();
        eprintln!("{}", raw_constraint);

        if tokens[2].starts_with("v") {
            if tokens[0].starts_with("!v") {
                let digit1: usize = tokens[0].replace("!v", "").parse().unwrap();
                let digit2: usize = tokens[2].replace("v", "").parse().unwrap();
                constraint.push(Constraint::Eq(
                    search_digit(digit1),
                    search_digit(digit2),
                    false,
                ));
            } else if tokens[0].starts_with("v") {
                let digit1: usize = tokens[0].replace("v", "").parse().unwrap();
                let digit2: usize = tokens[2].replace("v", "").parse().unwrap();
                constraint.push(Constraint::Eq(
                    search_digit(digit1),
                    search_digit(digit2),
                    true,
                ));
            } else {
                unreachable!();
            }
        } else {
            if tokens[0].starts_with("!v") {
                let digit: usize = tokens[0].replace("!v", "").parse().unwrap();
                let value: u32 = tokens[2].parse().unwrap();
                constraint.push(Constraint::Literal(search_digit(digit), value - 1));
            } else if tokens[0].starts_with("v") {
                let digit: usize = tokens[0].replace("v", "").parse().unwrap();
                let value: u32 = tokens[2].parse().unwrap();
                constraint.push(Constraint::Literal(search_digit(digit), value - 1));
            } else {
                unreachable!();
            }
        }

        all_constraints.push(constraint);
    }

    all_constraints.sort_unstable_by_key(|c| {
        Reverse(c.iter().any(|c| matches!(c, Constraint::Literal(_, _))))
    });

    Instance::new(all_constraints, base, digits)
}

fn search_digit(index: usize) -> usize {
    let mut i = 0;

    for j in 1..=9 {
        for k in 1..=9 {
            if j * 10 + k == index {
                return i;
            }

            i += 1
        }
    }

    unreachable!();
}
