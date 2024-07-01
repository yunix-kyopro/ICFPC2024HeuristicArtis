#ifdef __GNUC__
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target ("avx2")
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <random>
#include <functional>
#include <memory>
#include <thread>
#include <chrono>
#include <cmath>
#include <cassert>

#include <gmpxx.h>

#include <atcoder/all>

#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

struct xorshift64 {
  unsigned long long int x = 88172645463325252ULL;
  inline unsigned short nextUShort() {
    x = x ^ (x << 7);
    return x = x ^ (x >> 9);
  }
  inline unsigned int nextUShortMod(unsigned long long int mod) {
    x = x ^ (x << 7);
    x = x ^ (x >> 9);
    return ((x & 0x0000ffffffffffff) * mod) >> 48;
  }
  inline unsigned int nextUInt() {
    x = x ^ (x << 7);
    return x = x ^ (x >> 9);
  }
  inline unsigned int nextUIntMod(unsigned long long int mod) {
    x = x ^ (x << 7);
    x = x ^ (x >> 9);
    return ((x & 0x00000000ffffffff) * mod) >> 32;
  }
  inline unsigned long long int nextULL() {
    x = x ^ (x << 7);
    return x = x ^ (x >> 9);
  }
  inline double nextDouble() {
    x = x ^ (x << 7);
    x = x ^ (x >> 9);
    return (double)x * 5.42101086242752217e-20;
  }
};

struct timer {
  double t = 0.0;
  double lastStop = 0.0;
  bool stopped = false;
  timer() {
    restart();
  }
  inline void restart() {
    t = now();
    stopped = false;
  }
  inline void start() {
    if (stopped) {
      t += now() - lastStop;
      stopped = false;
    }
  }
  inline void stop() {
    if (!stopped) {
      lastStop = now();
      stopped = true;
    }
  }
  inline double time() {
    if (stopped) return lastStop - t;
    else return now() - t;
  }
  inline double now() {
    #ifdef _MSC_VER
      #ifdef LOCAL
        // return __rdtsc() * 2.857142857142857e-10; // 1 / 3.5e9, for local (Ryzen 9 3950X)
        return __rdtsc() * 3.846153846153846e-10; // 1 / 2.6e9, for local (Core i9-9750H)
      #else
        //return __rdtsc() * 3.5714285714285715e-10; // 1 / 2.8e9, for AWS EC2 C3 (Xeon E5-2680 v2)
        //return __rdtsc() * 3.4482758620689656e-10; // 1 / 2.9e9, for AWS EC2 C4 (Xeon E5-2666 v3)
        //return __rdtsc() * 3.333333333333333e-10; // 1 / 3.0e9, for AWS EC2 C5 (Xeon Platinum 8124M / Xeon Platinum 8275CL)
        return __rdtsc() * 3.4482758620689656e-10; // 1 / 2.9e9, for AWS EC2 C6i (Xeon Platinum 8375C)
      #endif
    #else
      unsigned long long l, h;
        __asm__ ("rdtsc" : "=a"(l), "=d"(h));
      #ifdef LOCAL
        // return (double)(l | h << 32) * 2.857142857142857e-10; // 1 / 3.5e9, for local (Ryzen 9 3950X)
        return (double)(l | h << 32) * 3.846153846153846e-10; // 1 / 2.6e9, for local (Core i9-9750H)
      #else
        //return (double)(l | h << 32) * 3.5714285714285715e-10; // 1 / 2.8e9, for AWS EC2 C3 (Xeon E5-2680 v2)
        //return (double)(l | h << 32) * 3.4482758620689656e-10; // 1 / 2.9e9, for AWS EC2 C4 (Xeon E5-2666 v3)
        //return (double)(l | h << 32) * 3.333333333333333e-10; // 1 / 3.0e9, for AWS EC2 C5 (Xeon Platinum 8124M / Xeon Platinum 8275CL)
        return (double)(l | h << 32) * 3.4482758620689656e-10; // 1 / 2.9e9, for AWS EC2 C6i (Xeon Platinum 8375C)
      #endif
    #endif
  }
};

using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> Pii;
typedef unsigned char uchar;

const ll mod = 998244353;

timer theTimer;
xorshift64 theRandom;
mt19937_64 theMersenne(1);

// libraries
namespace Lib {
  vector<string> split_string(const string &s, char delim) {
    vector<string> elems;
    string item;
    for (char ch: s) {
        if (ch == delim) {
            if (!item.empty())
                elems.push_back(item);
            item.clear();
        }
        else {
            item += ch;
        }
    }
    if (!item.empty())
        elems.push_back(item);
    return elems;
  }

  struct pair_hash {
    template<class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);

        size_t res = 0;
        res ^= hash1 + 0x9e3779b9 + (res << 6) + (res >> 2);
        res ^= hash2 + 0x9e3779b9 + (res << 6) + (res >> 2);
        return res;
    }
  };
}

// hyper parameters
namespace HyperParameter {
  void load_hyper_parameter(int argc, char *argv[]) {
  }
}

// enums

// structs
struct Token {
  char op;
  mpz_class value;

  static Token create_op(const char op) {
    return Token{op, 0};
  }

  static Token create_value(const mpz_class value) {
    return Token{'x', value};
  }

  bool is_op() const {
    return op != 'x';
  }

  bool is_value() const {
    return op == 'x';
  }

  bool is_empty() const {
    return op == '.';
  }

  bool operator==(const Token &rhs) const {
    return op == rhs.op && value == rhs.value;
  }

  bool operator!=(const Token &rhs) const {
    return !(*this == rhs);
  }
};

struct Board {
  unordered_map<Pii, Token, Lib::pair_hash> board;
  mpz_class result = 0;
  bool is_finished = false;

  Board() {}

public:
  bool is_empty(const Pii &pos) const {
    return board.find(pos) == board.end() || board.at(pos).is_empty();
  }

  void advance() {
    vector<Pii> token_pos_to_remove;
    vector<pair<Pii, Token>> token_to_add;
    for (const auto &[pos, token]: board) {
      if (token.is_value()) continue;
      if (token.op == '<') {
        const auto pos_from = Pii(pos.first, pos.second + 1);
        const auto pos_to = Pii(pos.first, pos.second - 1);
        if (!is_empty(pos_from)) {
          const auto arg = board.at(pos_from);
          token_pos_to_remove.push_back(pos_from);
          token_to_add.emplace_back(pos_to, arg);
        }
      }
      else if (token.op == '>') {
        const auto pos_from = Pii(pos.first, pos.second - 1);
        const auto pos_to = Pii(pos.first, pos.second + 1);
        if (!is_empty(pos_from)) {
          const auto arg = board.at(pos_from);
          token_pos_to_remove.push_back(pos_from);
          token_to_add.emplace_back(pos_to, arg);
        }
      }
      else if (token.op == '^') {
        const auto pos_from = Pii(pos.first + 1, pos.second);
        const auto pos_to = Pii(pos.first - 1, pos.second);
        if (!is_empty(pos_from)) {
          const auto arg = board.at(pos_from);
          token_pos_to_remove.push_back(pos_from);
          token_to_add.emplace_back(pos_to, arg);
        }
      }
      else if (token.op == 'v') {
        const auto pos_from = Pii(pos.first - 1, pos.second);
        const auto pos_to = Pii(pos.first + 1, pos.second);
        if (!is_empty(pos_from)) {
          const auto arg = board.at(pos_from);
          token_pos_to_remove.push_back(pos_from);
          token_to_add.emplace_back(pos_to, arg);
        }
      }
      else if (token.op == '+') {
        const auto pos_from1 = Pii(pos.first, pos.second - 1);
        const auto pos_from2 = Pii(pos.first - 1, pos.second);
        const auto pos_to1 = Pii(pos.first, pos.second + 1);
        const auto pos_to2 = Pii(pos.first + 1, pos.second);
        if (!is_empty(pos_from1) && !is_empty(pos_from2)) {
          const auto arg1 = board.at(pos_from1);
          const auto arg2 = board.at(pos_from2);
          if (arg1.is_value() && arg2.is_value()) {
            token_pos_to_remove.push_back(pos_from1);
            token_pos_to_remove.push_back(pos_from2);
            token_to_add.emplace_back(pos_to1, Token::create_value(arg1.value + arg2.value));
            token_to_add.emplace_back(pos_to2, Token::create_value(arg1.value + arg2.value));
          }
        }
      }
      else if (token.op == '-') {
        const auto pos_from1 = Pii(pos.first, pos.second - 1);
        const auto pos_from2 = Pii(pos.first - 1, pos.second);
        const auto pos_to1 = Pii(pos.first, pos.second + 1);
        const auto pos_to2 = Pii(pos.first + 1, pos.second);
        if (!is_empty(pos_from1) && !is_empty(pos_from2)) {
          const auto arg1 = board.at(pos_from1);
          const auto arg2 = board.at(pos_from2);
          if (arg1.is_value() && arg2.is_value()) {
            token_pos_to_remove.push_back(pos_from1);
            token_pos_to_remove.push_back(pos_from2);
            token_to_add.emplace_back(pos_to1, Token::create_value(arg1.value - arg2.value));
            token_to_add.emplace_back(pos_to2, Token::create_value(arg1.value - arg2.value));
          }
        }
      }
      else if (token.op == '*') {
        const auto pos_from1 = Pii(pos.first, pos.second - 1);
        const auto pos_from2 = Pii(pos.first - 1, pos.second);
        const auto pos_to1 = Pii(pos.first, pos.second + 1);
        const auto pos_to2 = Pii(pos.first + 1, pos.second);
        if (!is_empty(pos_from1) && !is_empty(pos_from2)) {
          const auto arg1 = board.at(pos_from1);
          const auto arg2 = board.at(pos_from2);
          if (arg1.is_value() && arg2.is_value()) {
            token_pos_to_remove.push_back(pos_from1);
            token_pos_to_remove.push_back(pos_from2);
            token_to_add.emplace_back(pos_to1, Token::create_value(arg1.value * arg2.value));
            token_to_add.emplace_back(pos_to2, Token::create_value(arg1.value * arg2.value));
          }
        }
      }
      else if (token.op == '/') {
        const auto pos_from1 = Pii(pos.first, pos.second - 1);
        const auto pos_from2 = Pii(pos.first - 1, pos.second);
        const auto pos_to1 = Pii(pos.first, pos.second + 1);
        const auto pos_to2 = Pii(pos.first + 1, pos.second);
        if (!is_empty(pos_from1) && !is_empty(pos_from2)) {
          const auto arg1 = board.at(pos_from1);
          const auto arg2 = board.at(pos_from2);
          if (arg1.is_value() && arg2.is_value() && arg2.value != 0) { // 0除算の場合は実行されない
            token_pos_to_remove.push_back(pos_from1);
            token_pos_to_remove.push_back(pos_from2);
            token_to_add.emplace_back(pos_to1, Token::create_value(arg1.value / arg2.value));
            token_to_add.emplace_back(pos_to2, Token::create_value(arg1.value / arg2.value));
          }
        }
      }
      else if (token.op == '%') {
        const auto pos_from1 = Pii(pos.first, pos.second - 1);
        const auto pos_from2 = Pii(pos.first - 1, pos.second);
        const auto pos_to1 = Pii(pos.first, pos.second + 1);
        const auto pos_to2 = Pii(pos.first + 1, pos.second);
        if (!is_empty(pos_from1) && !is_empty(pos_from2)) {
          const auto arg1 = board.at(pos_from1);
          const auto arg2 = board.at(pos_from2);
          if (arg1.is_value() && arg2.is_value() && arg2.value != 0) { // 0除算の場合は実行されない
            token_pos_to_remove.push_back(pos_from1);
            token_pos_to_remove.push_back(pos_from2);
            token_to_add.emplace_back(pos_to1, Token::create_value(arg1.value % arg2.value));
            token_to_add.emplace_back(pos_to2, Token::create_value(arg1.value % arg2.value));
          }
        }
      }
      else if (token.op == '=') {
        const auto pos_from1 = Pii(pos.first, pos.second - 1);
        const auto pos_from2 = Pii(pos.first - 1, pos.second);
        const auto pos_to1 = Pii(pos.first, pos.second + 1);
        const auto pos_to2 = Pii(pos.first + 1, pos.second);
        if (!is_empty(pos_from1) && !is_empty(pos_from2)) {
          const auto arg1 = board.at(pos_from1);
          const auto arg2 = board.at(pos_from2);
          if (arg1 == arg2) {
            token_pos_to_remove.push_back(pos_from1);
            token_pos_to_remove.push_back(pos_from2);
            token_to_add.emplace_back(pos_to1, arg1);
            token_to_add.emplace_back(pos_to2, arg2);
          }
        }
      }
      else if (token.op == '#') {
        const auto pos_from1 = Pii(pos.first, pos.second - 1);
        const auto pos_from2 = Pii(pos.first - 1, pos.second);
        const auto pos_to1 = Pii(pos.first + 1, pos.second);
        const auto pos_to2 = Pii(pos.first, pos.second + 1);
        if (!is_empty(pos_from1) && !is_empty(pos_from2)) {
          const auto arg1 = board.at(pos_from1);
          const auto arg2 = board.at(pos_from2);
          if (arg1 != arg2) {
            token_pos_to_remove.push_back(pos_from1);
            token_pos_to_remove.push_back(pos_from2);
            token_to_add.emplace_back(pos_to1, arg1);
            token_to_add.emplace_back(pos_to2, arg2);
          }
        }
      }
    }

    for (const auto &pos: token_pos_to_remove) {
      board.erase(pos);
    }

    unordered_set<Pii, Lib::pair_hash> added_token_pos_set;
    for (const auto &[pos, token]: token_to_add) {
      if (added_token_pos_set.find(pos) != added_token_pos_set.end()) {
        cerr << "Error: pos == (" << pos.first << ", " << pos.second << ") へ複数同時に書き込みが行われました。" << endl;
        exit(1);
      }
      added_token_pos_set.insert(pos);
      if (board[pos].is_op() && board[pos].op == 'S') {
        result = token.value;
        is_finished = true;
      }
      board[pos] = token;
    }
  }

  vector<vector<string>> get_output() const {
    int min_height = 1 << 30;
    int max_height = -(1 << 30);
    int min_width = 1 << 30;
    int max_width = -(1 << 30);
    for (const auto &elem: board) {
      min_height = min(min_height, elem.first.first);
      max_height = max(max_height, elem.first.first);
      min_width = min(min_width, elem.first.second);
      max_width = max(max_width, elem.first.second);
    }

    vector<int> col_width(max_width - min_width + 1, 0);
    vector<vector<string>> res;
    for (int i = min_height; i <= max_height; i++) {
      vector<string> row;
      for (int j = min_width; j <= max_width; j++) {
        if (is_empty(Pii(i, j))) {
          row.push_back(".");
          col_width[j - min_width] = max(col_width[j - min_width], 1);
        }
        else {
          const auto& token = board.at(Pii(i, j));
          if (token.is_op()) {
            row.push_back(string(1, token.op));
            col_width[j - min_width] = max(col_width[j - min_width], 1);
          }
          else {
            string s;
            size_t l2 = mpz_sizeinbase(token.value.get_mpz_t(), 2);
            if (l2 <= 21) {
              s = token.value.get_str();
            }
            else if (token.value < 0) {
              s = "-(2^" + to_string(l2 - 1) + ")";
            }
            else {
              s = "2^" + to_string(l2 - 1);
            }
            row.push_back(s);
            col_width[j - min_width] = max(col_width[j - min_width], (int) s.size());
          }
        }
      }
      res.push_back(row);
    }
    for (int i = min_height; i <= max_height; i++) {
      for (int j = min_width; j <= max_width; j++) {
        while ((int) res[i - min_height][j - min_width].size() < col_width[j - min_width]) {
          res[i - min_height][j - min_width] = " " + res[i - min_height][j - min_width];
        }
        res[i - min_height][j - min_width] += " ";
      }
    }

    return res;
  }

  struct TimeWarp {
    Token token_to_send;
    Pii pos_to_send;
    ll time_delta;
  };

  vector<TimeWarp> get_time_warps() {
    vector<TimeWarp> res;
    for (const auto &[pos, token]: board) {
      if (token.is_value()) continue;
      if (token.op == '@') {
        const auto pos1 = Pii(pos.first - 1, pos.second);
        const auto pos2 = Pii(pos.first, pos.second - 1);
        const auto pos3 = Pii(pos.first, pos.second + 1);
        const auto pos4 = Pii(pos.first + 1, pos.second);
        if (!is_empty(pos1) && !is_empty(pos2) && !is_empty(pos3) && !is_empty(pos4)) {
          const auto arg1 = board.at(pos1);
          const auto arg2 = board.at(pos2);
          const auto arg3 = board.at(pos3);
          const auto arg4 = board.at(pos4);
          if (arg2.is_value() && arg3.is_value() && arg4.is_value()) {
            res.push_back(TimeWarp{arg1, Pii((int)(pos.first - mpz_get_si(arg3.value.get_mpz_t())), (int)(pos.second - mpz_get_si(arg2.value.get_mpz_t()))), arg4.value.get_si()});
          }
        }
      }
    }
    return res;
  }
};

// constants
struct Consts {
  static constexpr ll output_tick_interval = 1;
};

// inputs
struct Input {
  mpz_class a, b;
  vector<string> input;
};

// outputs

// internals
struct Environment {
  Board initial_board;

  int initial_height;
  int initial_width;
};

Input get_input() {
  Input input;
  cin >> input.a >> input.b;
  cin.ignore();
  while (true) {
    string s;
    getline(cin, s);
    if (s.empty()) {
      break;
    }
    input.input.push_back(s);
  }
  return input;
}

Environment create_environment(const Input &input) {
  Environment env;

  env.initial_height = input.input.size();

  {
    int max_width = 0;
    for (int i = 0; i < env.initial_height; i++) {
      max_width = max(max_width, (int)input.input[i].size());
    }
    env.initial_width = max_width;
  }

  env.initial_board = Board();
  for (int i = 0; i < env.initial_height; i++) {
    auto elems = Lib::split_string(input.input[i], ' ');
    for (int j = 0; j < env.initial_width; j++) {
      if (j < (int) elems.size()) {
        if (elems[j].size() == 1 && !('0' <= elems[j][0] && elems[j][0] <= '9')) {
          if (elems[j][0] == 'A') {
            env.initial_board.board[Pii(i, j)] = Token::create_value(input.a);
          }
          else if (elems[j][0] == 'B') {
            env.initial_board.board[Pii(i, j)] = Token::create_value(input.b);
          }
          else {
            env.initial_board.board[Pii(i, j)] = Token::create_op(elems[j][0]);
          }
        }
        else {
          env.initial_board.board[Pii(i, j)] = Token::create_value(mpz_class(elems[j]));
        }
      }
    }
  }

  return env;
}

Board simulate(const Environment &env) {
  ll total_tick = 0;
  auto board = env.initial_board;
  {
    auto output_initial = board.get_output();
    for (const auto &row: output_initial) {
      for (const auto &elem: row) {
        cout << elem;
      }
      cout << endl;
    }
    cout << endl;
  }
  vector<Board> board_history = {board};
  while (true) {
    this_thread::sleep_for(chrono::milliseconds(0));
    auto time_warps = board.get_time_warps();
    board.advance();
    if (board.is_finished) {
      cout << "result = " << board.result << endl;
      break;
    }
    if (!time_warps.empty()) {
      ll time_delta = time_warps[0].time_delta;
      for (const auto& time_warp: time_warps) {
        if (time_warp.time_delta != time_delta) {
          cerr << "Error: 時間の変更量が一定ではありません(dt = {" << time_delta << ", " << time_warp.time_delta << "})。" << endl;
          exit(1);
        }
      }
      if (time_delta <= 0) {
        cerr << "Error: 時間の変更量は正でなければなりません(dt = " << time_delta << ")。" << endl;
        exit(1);
      }
      if (time_delta >= (int) board_history.size()) {
        cerr << "Error: 時間の変更量が大きすぎます(dt = " << time_delta << ", history.size() = " << board_history.size() << ")。" << endl;
        exit(1);
      }
      board = board_history[board_history.size() - (time_delta + 1)];
      for (int i = 0; i < time_delta; i++) {
        board_history.pop_back();
      }
      for (const auto &time_warp: time_warps) {
        if (board.board[time_warp.pos_to_send].is_op() && board.board[time_warp.pos_to_send].op == 'S') {
          board.is_finished = true;
          board.result = time_warp.token_to_send.value;
        }
        else {
          board.board[time_warp.pos_to_send] = time_warp.token_to_send;
        }
      }
      board_history.back() = board;
    }
    else {
      board_history.push_back(board);
    }
    total_tick++;
    if (total_tick % Consts::output_tick_interval == 0) {
      auto output = board.get_output();
      cout << "t = " << board_history.size() - 1 << endl;
      cout << "total_tick = " << total_tick << endl;
      for (const auto &row: output) {
        for (const auto &elem: row) {
          cout << elem;
        }
        cout << endl;
      }
      cout << endl;
    }
  }

  return board;
}

int main(int argc, char *argv[]) {
  cin.tie(0);
  ios::sync_with_stdio(false);

  HyperParameter::load_hyper_parameter(argc, argv);

  const auto input = get_input();

  const auto env = create_environment(input);

  simulate(env);

  return 0;
}
