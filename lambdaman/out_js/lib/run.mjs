class Thunk {
  constructor(value) {
    this.value = value;
  }
}

class Lambda {
  constructor(fn) {
    this.fn = fn;
  }
}

class App {
  constructor(fn, arg) {
    this.fn = fn;
    this.arg = arg;
  }
}

export function evaluate(val) {
  while (val instanceof Thunk) {
    val = val.value();
    if (val instanceof App) {
      val = peelLambda(evaluate(val.fn))(val.arg);
    }
  }
  return val;
}

function peelLambda(lam) {
  if (!(lam instanceof Lambda)) {
    console.log(lam);
    throw "type error: apply a non-lambda to a value";
  }
  return lam.fn;
}

function apply(fn) {
  return function (arg) {
    return new Thunk(function () {
      return new App(fn, arg);
    });
  };
}

// リテラル
export const true_ = new Thunk(function () {
  return true;
});

export const false_ = new Thunk(function () {
  return false;
});

export const integer = function (n) {
  return new Thunk(function () {
    return n;
  });
};

export const string = function (s) {
  return new Thunk(function () {
    return s;
  });
};

// 単項演算
const minus_ = new Lambda(function (x) {
  return new Thunk(function () {
    return -evaluate(x);
  });
});
export const minus = (x) => apply(minus_)(x);

const not_ = new Lambda(function (x) {
  return new Thunk(function () {
    return !evaluate(x);
  });
});
export const not = (x) => apply(not_)(x);

// 二項演算
// 数値系
const add_ = new Lambda(function (x) {
  return new Lambda(function (y) {
    return new Thunk(function () {
      return evaluate(x) + evaluate(y);
    });
  });
});
export const add = (x, y) => apply(apply(add_)(x))(y);

const sub_ = new Lambda(function (x) {
  return new Lambda(function (y) {
    return new Thunk(function () {
      return evaluate(x) - evaluate(y);
    });
  });
});
export const sub = (x, y) => apply(apply(sub_)(x))(y);

const mul_ = new Lambda(function (x) {
  return new Lambda(function (y) {
    return new Thunk(function () {
      return evaluate(x) * evaluate(y);
    });
  });
});
export const mul = (x, y) => apply(apply(mul_)(x))(y);

const div_ = new Lambda(function (x) {
  return new Lambda(function (y) {
    return new Thunk(function () {
      return Math.floor(evaluate(x) / evaluate(y));
    });
  });
});
export const div = (x, y) => apply(apply(div_)(x))(y);

const mod_ = new Lambda(function (x) {
  return new Lambda(function (y) {
    return new Thunk(function () {
      return evaluate(x) % evaluate(y);
    });
  });
});
export const mod = (x, y) => apply(apply(mod_)(x))(y);

// 比較系

const eq_ = new Lambda(function (x) {
  return new Lambda(function (y) {
    return new Thunk(function () {
      return evaluate(x) === evaluate(y);
    });
  });
});
export const eq = (x, y) => apply(apply(eq_)(x))(y);

const gt_ = new Lambda(function (x) {
  return new Lambda(function (y) {
    return new Thunk(function () {
      return evaluate(x) > evaluate(y);
    });
  });
});
export const gt = (x, y) => apply(apply(gt_)(x))(y);

const lt_ = new Lambda(function (x) {
  return new Lambda(function (y) {
    return new Thunk(function () {
      return evaluate(x) < evaluate(y);
    });
  });
});
export const lt = (x, y) => apply(apply(lt_)(x))(y);

const or_ = new Lambda(function (x) {
  return new Lambda(function (y) {
    return new Thunk(function () {
      return evaluate(x) || evaluate(y);
    });
  });
});
export const or = (x, y) => apply(apply(or_)(x))(y);

const and_ = new Lambda(function (x) {
  return new Lambda(function (y) {
    return new Thunk(function () {
      return evaluate(x) && evaluate(y);
    });
  });
});
export const and = (x, y) => apply(apply(and_)(x))(y);

// 文字列系
const concat_ = new Lambda(function (x) {
  return new Lambda(function (y) {
    return new Thunk(function () {
      return evaluate(x) + evaluate(y);
    });
  });
});
export const concat = (x, y) => apply(apply(concat_)(x))(y);

const head_ = new Lambda(function (s) {
  return new Lambda(function (n) {
    return new Thunk(function () {
      return evaluate(s).slice(0, evaluate(n));
    });
  });
});
export const head = (n, s) => apply(apply(head_)(s))(n);

const tail_ = new Lambda(function (s) {
  return new Lambda(function (n) {
    return new Thunk(function () {
      return evaluate(s).slice(evaluate(n));
    });
  });
});
export const tail = (n, s) => apply(apply(tail_)(s))(n);

// 制御系
export const app = (f, x) => apply(f)(x);

export const lambda = (fn) => new Lambda(fn);

// if
const if__ = new Lambda(function (cond) {
  return new Lambda(function (t) {
    return new Lambda(function (f) {
      return new Thunk(function () {
        return evaluate(cond) ? evaluate(t) : evaluate(f);
      });
    });
  });
});
export const if_ = (cond, t, f) => apply(apply(apply(if__)(cond))(t))(f);

// B$ -> apply, L -> Lambda
const example = concat(
  string("L"),
  app(
    app(
      lambda((c) =>
        app(
          lambda((g) =>
            app(
              lambda((h) => app(g, app(h, h))),
              lambda((h) => app(g, app(h, h)))
            )
          ),
          lambda((f) =>
            lambda((n) => if_(eq(n, 1), c, concat(c, app(f, sub(n, 1)))))
          )
        )
      ),
      string(".")
    ),
    integer(199)
  )
);

// console.log(evaluate(example)); //Lのあとに.が199個

const test = app(
  app(
    lambda((v1) =>
      app(
        lambda((v2) => app(v1, app(v2, v2))),
        lambda((v2) => app(v1, app(v2, v2)))
      )
    ),
    lambda((v1) =>
      lambda((v2) =>
        if_(
          eq(v2, integer(0)),
          integer(1),
          app(
            lambda((v3) => add(app(v1, v3), app(v1, v3))),
            sub(v2, integer(1))
          )
        )
      )
    )
  ),
  integer(4)
);
// console.log(evaluate(test)); // 16

// console.log(evaluate(test2));

// const act3timesToR8 = lambda((v1) =>
//   app(v1, app(v1, app(v1, string("RRRRRRRR"))))
// );

// const concat3 = lambda((s) => concat(s, concat(s, s)));

// const solveLambdaman6 = concat(
//   string("solve lambdaman6 "),
//   app(act3timesToR8, concat3)
// );

// console.log(evaluate(solveLambdaman6));

// const act3times = lambda((f) => lambda((x) => app(f, app(f, app(f, x)))));
// const concat27AndD = lambda((s) =>
//   concat(app(app(act3times, concat3), s), string("D"))
// );

// const solve = lambda((c27) =>
//   app(c27, concat(app(c27, string("RR")), app(c27, string("LL"))))
// );

// const solveLambdaman9 = concat(
//   string("solve lambdaman9 "),
//   app(solve, concat27AndD)
// );

// console.log(evaluate(solveLambdaman9));
