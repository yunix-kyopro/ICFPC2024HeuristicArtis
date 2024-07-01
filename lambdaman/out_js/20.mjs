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

const repeat = lambda((g) =>
  lambda((m) =>
    lambda((c) =>
      if_(
        eq(m, integer(0)),
        string(""),
        concat(c, app(app(g, sub(m, integer(1))), c))
      )
    )
  )
);

const urdl = lambda((idx) =>
  head(integer(1), tail(mod(idx, integer(4)), string("URDL")))
);

const solve = app(
  lambda((lrud) =>
    lambda((rep) =>
      lambda((self) =>
        lambda((n) =>
          lambda((idx) =>
            if_(
              lt(n, integer(1)),
              string(""),
              concats(
                app(app(rep, div(n, integer(2))), app(lrud, idx)),
                app(app(self, div(n, integer(4))), add(idx, integer(3))),
                app(app(self, div(n, integer(4))), add(idx, integer(1))),
                app(app(rep, div(n, integer(2))), app(lrud, idx)),
                app(app(self, div(n, integer(2))), add(idx, integer(3))),
                app(app(self, div(n, integer(2))), add(idx, integer(0))),
                app(app(self, div(n, integer(2))), add(idx, integer(1))),
                app(app(rep, n), app(lrud, add(idx, integer(2))))
              )
            )
          )
        )
      )
    )
  ),
  urdl
);

const final = app(
  lambda((ycomb) => app(ycomb, app(solve, app(ycomb, repeat)))),
  Ycomb
);

const solveLambdaman20 = concat(
  string("solve lambdaman20 "),
  app(
    lambda((f) =>
      concats(
        app(app(f, integer(64)), integer(0)),
        app(app(f, integer(64)), integer(1)),
        app(app(f, integer(64)), integer(2)),
        app(app(f, integer(64)), integer(3))
      )
    ),
    final
  )
);

console.log(evaluate(solveLambdaman20));
