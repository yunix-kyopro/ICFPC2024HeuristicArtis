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


//case 12
const p = 78064478;
const a = 43;
const seed = 2550;
const end = 34;

const calc = lambda((f) =>
  lambda((n) =>
    if_(
      eq(n, integer(end)),
      string("solve lambdaman12 "),
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
