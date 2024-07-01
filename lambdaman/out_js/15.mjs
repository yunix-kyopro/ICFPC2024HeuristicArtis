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

const Ycomb = lambda((f) =>
  app(
    lambda((x) => app(f, app(x, x))),
    lambda((x) => app(f, app(x, x)))
  )
);

const recursion = (f, n) => app(app(Ycomb, f), n);


//case 15
const p = 77985662;
const a = 16;
const seed = 1092;
const end = 8;

const calc = lambda((f) =>
  lambda((n) =>
    if_(
      eq(n, integer(end)),
      string("solve lambdaman15 "),
      concat(
        app(f, mod(mul(n, integer(a)), integer(p))),
        head(
          integer(2),
          tail(mod(n, integer(8)), string("UURRDDLL"))
        )
      )
    )
  )
);

const solve = recursion(calc, integer(seed));

console.log(evaluate(solve));
