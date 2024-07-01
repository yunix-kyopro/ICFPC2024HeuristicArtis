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

const concats = (...args) => {
  let ret = concat(args[0], args[1]);
  for (let i = 2; i < args.length; i++) {
    ret = concat(ret, args[i]);
  }
  return ret;
};

const udlr = lambda((idx) => head(integer(1), tail(idx, string("UDDULRRL"))));

const dfs = lambda((self) =>
  lambda((n) =>
    lambda((idx) =>
      if_(
        lt(idx, integer(0)),
        string(""),
        if_(
          eq(n, integer(0)),
          string(""),
          concat(
            app(udlr, div(idx, n)),
            concat(
              if_(
                eq(mod(idx, mul(n, integer(2))), n),
                app(
                  app(self, div(n, integer(2))),
                  sub(mul(n, integer(4)), integer(1))
                ),
                string("")
              ),
              app(app(self, n), sub(idx, integer(1)))
            )
          )
        )
      )
    )
  )
);

const solve19 = concat(
  string("solve lambdaman19 "),
  app(app(app(Ycomb, dfs), integer(64)), integer(64 * 8 - 1))
);
console.log(evaluate(solve19));
