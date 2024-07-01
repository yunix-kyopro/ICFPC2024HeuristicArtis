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

const ldru = lambda((idx) =>
  head(integer(1), tail(mod(idx, integer(4)), string("LDRU")))
);

const saiki = lambda((self) =>
  lambda((ldru) =>
    lambda((n) =>
      lambda((firstDirIdx) =>
        lambda((isHalf) =>
          lambda((t) =>
            if_(
              lt(mul(n, isHalf), integer(2)),
              app(ldru, firstDirIdx),
              if_(
                eq(t, mul(n, integer(12))),
                string(""),
                concat(
                  if_(
                    lt(t, mul(n, integer(4))),
                    app(ldru, firstDirIdx),
                    if_(
                      lt(t, mul(n, integer(8))),
                      app(app(app(app(app(self, ldru),
                        div(n, integer(2))),
                        add(add(add(firstDirIdx, div(t, n)), mul(isHalf, integer(2))), integer(1))),
                        add(div(t, add(mul(integer(7), n), div(n, integer(128)))), integer(1))),
                        integer(0)),
                      app(ldru, add(firstDirIdx, integer(2)))
                    )
                  ),
                  app(app(app(app(app(self, ldru),
                    n),
                    firstDirIdx),
                    isHalf),
                    add(
                      t,
                      if_(
                        gt(mod(div(t, n), integer(8)), integer(3)),
                        mul(isHalf, n),
                        integer(4)
                      )
                    )
                  )
                )
              )
            )
          )
        )
      )
    )
  )
)

const solveLambdaman20 = concat(string("solve lambdaman20 "), app(app(app(app(app(app(Ycomb, saiki), ldru), integer(128)), integer(1)), integer(1)), integer(128 * 4)));
console.log(evaluate(solveLambdaman20));