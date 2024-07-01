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

const duplicate = lambda((x) => concat(x, concat(x, x)));

const apply = lambda((f) =>
  lambda((s) => app(f, app(f, app(f, app(f, app(f, s))))))
);

const solve = lambda((f) =>
  app(f, concat(app(f, string("DL")), app(f, string("UR"))))
);

const lambdaman8 = concat(
  string("solve lambdaman8 "),
  app(solve, app(apply, duplicate))
);

console.log(evaluate(lambdaman8));
