import {
    integer,
    string,
    true_,
    false_,
    minus,
    not,
    add,
    sub,
    mul,
    div,
    mod,
    concat,
    head,
    tail,
    eq,
    gt,
    lt,
    app,
    if_,
    lambda,
    evaluate,
} from "./lib/index.mjs";

const duplicate = lambda((x) =>
    concat(x, concat(x, x))
)

const apply = lambda((f) =>
    lambda((s) =>
        concat(
            app(f, app(f, app(f, s))),
            string("D")
        )
    )
)

const solve = lambda((f) =>
    app(
        f,
        concat(
            app(
                f,
                string("RR")
            ),
            app(
                f,
                string("LL")
            )
        )
    )
);

const lambdaman9 = concat(
    string("solve lambdaman9 "),
    app(solve, app(apply, duplicate))
);

console.log(evaluate(lambdaman9));
