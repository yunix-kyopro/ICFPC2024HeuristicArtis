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
}

// hyper parameters
namespace HyperParameter {
  void load_hyper_parameter(int argc, char *argv[]) {
  }
}

// enums

// structs
struct Cell {
  char type;
  bool passed;

  Cell(char type) : type(type), passed(false) {}

  bool is_wall() const {
    return type == '#';
  }

  bool is_empty() const {
    return !is_wall();
  }
};

struct Board {
  vector<vector<Cell>> board;
  int height;
  int width;

  Board() : Board(0, 0) {}
  Board(int height, int width) : height(height), width(width) {
    board = vector<vector<Cell>>(height, vector<Cell>(width, Cell('#')));
  }

  bool all_passed() const {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (board[i][j].is_empty() && !board[i][j].passed) {
          return false;
        }
      }
    }
    return true;
  }
};

// constants
struct Consts {
  static constexpr int output_interval = 10000;
};

// inputs
struct Input {
  string movement;
  vector<string> board;
};

// outputs

// internals
struct Environment {
  string movement;
  int movement_length;

  Board initial_board;
  int start_pos_x;
  int start_pos_y;

  Environment() {
    movement = "";
    movement_length = 0;
    initial_board = Board(0, 0);
    start_pos_x = 0;
    start_pos_y = 0;
  }
};

struct State {
  const Environment &env;

  Board board;
  int pos_x;
  int pos_y;
  int turn;

  State(const Environment &env) : 
    env(env),
    board(env.initial_board),
    pos_x(env.start_pos_x),
    pos_y(env.start_pos_y),
    turn(0)
  {
    board.board[pos_x][pos_y].passed = true;
  }

private:
  bool can_move_to(int x, int y) const {
    if (x < 0 || x >= board.height || y < 0 || y >= board.width) {
      return false;
    }
    if (board.board[x][y].is_wall()) {
      return false;
    }
    return true;
  }

public:
  bool is_finished() const {
    return turn >= env.movement_length;
  }

  void advance() {
    if (is_finished()) {
      return;
    }

    const char move = env.movement[turn];
    int next_x = pos_x;
    int next_y = pos_y;
    if (move == 'U') {
      next_x--;
    }
    else if (move == 'D') {
      next_x++;
    }
    else if (move == 'L') {
      next_y--;
    }
    else if (move == 'R') {
      next_y++;
    }
    else {
      cerr << "Error: 答えにURDL以外の文字が含まれています(turn = " << turn << ", move = " << move << ")" << endl;
      exit(1);
    }

    if (can_move_to(next_x, next_y)) {
      pos_x = next_x;
      pos_y = next_y;
      board.board[pos_x][pos_y].passed = true;
    }

    turn++;
  }

  bool all_passed() const {
    return board.all_passed();
  }

  vector<string> get_output() const {
    vector<string> output(board.height);
    for (int i = 0; i < board.height; i++) {
      for (int j = 0; j < board.width; j++) {
        if (i == pos_x && j == pos_y) {
          output[i].push_back('L');
        }
        else if (board.board[i][j].is_wall()) {
          output[i].push_back('#');
        }
        else if (board.board[i][j].passed) {
          output[i].push_back('.');
        }
        else {
          output[i].push_back('x');
        }
      }
    }
    return output;
  }
};

Input get_input() {
  Input input;
  cin >> input.movement;
  cin.ignore();
  while (true) {
    string line;
    getline(cin, line);
    if (line.empty()) {
      break;
    }
    input.board.push_back(line);
  }
  return input;
}

Environment create_environment(const Input &input) {
  Environment env;

  env.movement = input.movement;
  env.movement_length = input.movement.size();

  const int height = input.board.size();
  const int width = input.board[0].size();

  env.initial_board = Board(height, width);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      env.initial_board.board[i][j] = Cell(input.board[i][j]);
      if (input.board[i][j] == 'L') {
        env.start_pos_x = i;
        env.start_pos_y = j;
      }
    }
  }

  return env;
}

void simulate(const Environment &env) {
  State state(env);
  while (!state.is_finished()) {
    if (state.turn % Consts::output_interval == 0) {
      const auto output = state.get_output();
      cout << "t = " << state.turn << endl;
      for (const auto &line : output) {
        cout << line << endl;
      }
      cout << endl;
    }
    state.advance();
  }
  const auto output = state.get_output();
  cout << "finished" << endl;
  cout << "t = " << state.turn << endl;
  for (const auto &line : output) {
    cout << line << endl;
  }
  cout << "all_passed = " << (state.all_passed() ? "true" : "false") << endl;
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
