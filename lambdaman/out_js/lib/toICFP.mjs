export const true_ = () => "T";

export const false_ = () => "F";

export const integer = (n) => {
  if (n == 0) {
    return `I!`;
  }
  let result = "";
  while (n > 0) {
    result = String.fromCharCode(33 + (n % 94)) + result;
    n = Math.floor(n / 94);
  }
  return `I${result}`;
};

const order =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`|~ \n";

export const string = (s) => {
  let result = "";
  for (let i = 0; i < s.length; i++) {
    result += String.fromCharCode(order.indexOf(s[i]) + 33);
  }
  return `S${result}`;
};

// 単項演算
export const minus = (x) => `U- ${x}`;

export const not = (x) => `U! ${x}`;

// 二項演算
// 数値系
export const add = (x, y) => `B+ ${x} ${y}`;

export const sub = (x, y) => `B- ${x} ${y}`;

export const mul = (x, y) => `B* ${x} ${y}`;

export const div = (x, y) => `B/ ${x} ${y}`;

export const mod = (x, y) => `B% ${x} ${y}`;

// 比較系

export const eq = (x, y) => `B= ${x} ${y}`;

export const gt = (x, y) => `B> ${x} ${y}`;

export const lt = (x, y) => `B< ${x} ${y}`;

// 文字列系
export const concat = (x, y) => `B. ${x} ${y}`;

export const head = (n, s) => `BT ${n} ${s}`;

export const tail = (n, s) => `BD ${n} ${s}`;

// 制御系
export const app = (f, x) => `B$ ${f} ${x}`;

let __FUNCTION_COUNTER__ = 33;
export const lambda = (fn) => {
  const functionCounter = __FUNCTION_COUNTER__++;
  const id = String.fromCharCode(functionCounter);
  return `L${id} ${fn(`v${id}`)}`;
};

const reset = () => {
  __FUNCTION_COUNTER__ = 33;
};

// if
export const if_ = (cond, t, f) => `? ${cond} ${t} ${f}`;

export const evaluate = (expr) => {
  reset();
  console.log(expr.length);
  return expr;
};
