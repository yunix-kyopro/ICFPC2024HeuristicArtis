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


//case 17
const p = 830579;
const a = 7;
const seed = 2;
const end = 1;

const calc = lambda((f) =>
  lambda((n) =>
    if_(
      eq(n, integer(end)),
      string("solve lambdaman17 "),
      concat(
        app(f, mod(mul(n, integer(a)), integer(p))),
        head(
          integer(1),
          tail(mod(n, integer(4)), string("URDL"))
        )
      )
    )
  )
);

const solve = recursion(calc, integer(seed));

console.log(evaluate(solve));
