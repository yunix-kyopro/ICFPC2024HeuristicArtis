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

const solve = lambda((f) =>
    lambda((s) =>
        app(
            f,
            app(f,
                app(f,
                    s
                )
            ),
        )
    )
);

const lambdaman5 = concat(
    string("solve lambdaman5 "),
    app(app(solve, duplicate), string("LLRDDDLLUUULLULLRUURUDRDRRRURDLD"))
);

console.log(evaluate(lambdaman5));
