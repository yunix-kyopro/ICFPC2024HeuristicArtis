#ifdef __GNUC__
// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")
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

// constants
struct Adj4 {
  static constexpr array<int, 4> dx = {-1,  0,  1,  0};
  static constexpr array<int, 4> dy = { 0, -1,  0,  1};
  static constexpr array<char, 4> dc = {'U', 'L', 'D', 'R'};
  static int reverse(const int dir) {
    assert(0 <= dir && dir < 4);
    return dir ^ 2;
  }
};

struct Consts {
};

// inputs
struct Input {
  string input;
};

// outputs
struct Output {
  string path;
};

// internals
struct Environment {
  vector<vector<char>> board;

  int initial_height;
  int initial_width;

  int start_x;
  int start_y;

  int pill_num;
  vector<vector<int>> pos_id;

  vector<Pii> pos_xy;

  vector<vector<int>> dist;
};

Input get_input() {
  Input input;
  cin >> input.input;
  return input;
}

Environment create_environment(const Input &input) {
  Environment env;
  env.board.push_back(vector<char>());
  for (const auto &c: input.input) {
    if (c == 'a') {
      env.board.back().push_back('#');
    }
    else if (c == 'l') {
      env.board.back().push_back('.');
    }
    else if (c == 'F') {
      env.board.back().push_back('L');
    }
    else if (c == '~') {
      env.board.push_back(vector<char>());
    }
  }
  while (!env.board.empty() && env.board.back().empty()) {
    env.board.pop_back();
  }

  env.initial_height = env.board.size();
  env.initial_width = env.board[0].size();

  env.pos_id = vector<vector<int>>(env.initial_height, vector<int>(env.initial_width, -1));
  {
    int id = 1;
    for (int i = 0; i < env.initial_height; i++) {
      for (int j = 0; j < env.initial_width; j++) {
        if (env.board[i][j] == 'L') {
          env.start_x = i;
          env.start_y = j;
          env.pos_id[i][j] = 0;
        }
        if (env.board[i][j] == '.') {
          env.pos_id[i][j] = id;
          id++;
        }
      }
    }
    env.pill_num = id;
  }

  env.pos_xy = vector<Pii>(env.pill_num);
  for (int i = 0; i < env.initial_height; i++) {
    for (int j = 0; j < env.initial_width; j++) {
      if (env.pos_id[i][j] != -1) {
        env.pos_xy[env.pos_id[i][j]] = Pii(i, j);
      }
    }
  }

  env.dist = vector<vector<int>>(env.pill_num, vector<int>(env.pill_num, 0));
  for (int si = 0; si < env.initial_height; si++) {
    for (int sj = 0; sj < env.initial_width; sj++) {
      if (env.pos_id[si][sj] == -1) continue;
      int start_id = env.pos_id[si][sj];
      vector<bool> visited(env.pill_num);
      queue<tuple<int, int, int>> que; // dist, x, y
      que.emplace(0, si, sj);
      while (!que.empty()) {
        auto [d, i, j] = que.front();
        que.pop();
        if (visited[env.pos_id[i][j]]) continue;
        visited[env.pos_id[i][j]] = true;
        env.dist[start_id][env.pos_id[i][j]] = d;
        for (int k = 0; k < 4; k++) {
          int ni = i + Adj4::dx[k];
          int nj = j + Adj4::dy[k];
          if (ni < 0 || ni >= env.initial_height || nj < 0 || nj >= env.initial_width) continue;
          if (env.board[ni][nj] == '#') continue;
          if (visited[env.pos_id[ni][nj]]) continue;
          que.emplace(d + 1, ni, nj);
        }
      }
    }
  }

  return env;
}

Output solve_sa(const Environment &env) {
  struct SAState {
    const Environment &env;

    vector<int> visit_order;
    ll score;

    SAState(const Environment &env) : env(env) {
      visit_order = vector<int>(env.pill_num);
      iota(visit_order.begin(), visit_order.end(), 0);
      // shuffle(visit_order.begin() + 1, visit_order.end(), theMersenne);
      update_score_full();
    }

    void update_score_full() {
      score = 0;
      for (int i = 0; i + 1 < env.pill_num; i++) {
        score += env.dist[visit_order[i]][visit_order[i + 1]];
      }
    }

    void update_score_partial(int i, int j, bool is_add) {
      if (j < 0 || j >= env.pill_num) return;
      int partial_score = env.dist[visit_order[i]][visit_order[j]];
      score += is_add ? partial_score : -partial_score;
    }

    ll get_score() {
      return score;
    }

    Output create_output() {
      Output output;
      vector<vector<bool>> visited(env.initial_height, vector<bool>(env.initial_width));
      vector<vector<int>> prev(env.initial_height, vector<int>(env.initial_width));
      for (int k = 1; k < env.pill_num; k++) {
        int x = env.pos_xy[visit_order[k-1]].first;
        int y = env.pos_xy[visit_order[k-1]].second;
        for (int i = 0; i < env.initial_height; i++) {
          for (int j = 0; j < env.initial_width; j++) {
            visited[i][j] = false;
          }
        }
        queue<tuple<int, int, int>> que; // x, y, dir
        que.emplace(x, y, -1);
        while (!que.empty()) {
          auto [i, j, dir] = que.front();
          que.pop();
          if (visited[i][j]) continue;
          visited[i][j] = true;
          if (dir != -1) prev[i][j] = dir;
          if (env.pos_id[i][j] == visit_order[k]) {
            break;
          }
          for (int d = 0; d < 4; d++) {
            int ni = i + Adj4::dx[d];
            int nj = j + Adj4::dy[d];
            if (ni < 0 || ni >= env.initial_height || nj < 0 || nj >= env.initial_width) continue;
            if (env.board[ni][nj] == '#') continue;
            if (visited[ni][nj]) continue;
            que.emplace(ni, nj, Adj4::reverse(d));
          }
        }
        int px = env.pos_xy[visit_order[k]].first;
        int py = env.pos_xy[visit_order[k]].second;
        string path;
        while (px != x || py != y) {
          int d = prev[px][py];
          path += Adj4::dc[Adj4::reverse(d)];
          px += Adj4::dx[d];
          py += Adj4::dy[d];
        }
        reverse(path.begin(), path.end());
        output.path += path;
      }
      return output;
    }
  };

  SAState state(env);
  {
    ll score = state.get_score();
    ll last_score = score;
    ll best_score = score;

    const double base_temperature = 1e1;
    const double target_temperature = 1e-1;
    // const double decay_rate = 4e-5;
    double temperature = base_temperature;

    int iter_count = 0;
    double time_start = theTimer.time();
    const double time_limit = 300.970;

    while (true) {
      if (iter_count % 1024 == 0 && theTimer.time() > time_limit) break;
      const double roll = theRandom.nextDouble();
      if (roll < 0.4) {
        int i = theRandom.nextUIntMod(env.pill_num - 1) + 1;
        int j = theRandom.nextUIntMod(env.pill_num - 1) + 1;
        if (i == j) continue;

        state.update_score_partial(i - 1, i, false);
        state.update_score_partial(i, i + 1, false);
        state.update_score_partial(j - 1, j, false);
        state.update_score_partial(j, j + 1, false);

        swap(state.visit_order[i], state.visit_order[j]);

        state.update_score_partial(i - 1, i, true);
        state.update_score_partial(i, i + 1, true);
        state.update_score_partial(j - 1, j, true);
        state.update_score_partial(j, j + 1, true);

        score = state.get_score();

        #ifdef DEBUG
        if (iter_count % 100000 == 0) cerr << iter_count << " " << score << " " << last_score << " " << best_score << " " << temperature << " " << theTimer.time() << endl;
        #endif

        if (score <= last_score) {
          last_score = score;
          if (score < best_score) {
            best_score = score;
          }
        }
        else if (theRandom.nextDouble() < exp(double(last_score - score) / temperature)) { // accept
          last_score = score;
        }
        else { // rollback
          state.update_score_partial(i - 1, i, false);
          state.update_score_partial(i, i + 1, false);
          state.update_score_partial(j - 1, j, false);
          state.update_score_partial(j, j + 1, false);

          swap(state.visit_order[i], state.visit_order[j]);

          state.update_score_partial(i - 1, i, true);
          state.update_score_partial(i, i + 1, true);
          state.update_score_partial(j - 1, j, true);
          state.update_score_partial(j, j + 1, true);

          score = last_score;
        }
      }
      else if (roll < 0.8) {
        int i = theRandom.nextUIntMod(env.pill_num - 1) + 1;
        int j = theRandom.nextUIntMod(env.pill_num - 1) + 1;
        if (i == j) continue;

        state.update_score_partial(i - 1, i, false);
        state.update_score_partial(i, i + 1, false);
        state.update_score_partial(i - 1, i + 1, true);
        state.update_score_partial(j < i ? j - 1 : j, i, true);
        state.update_score_partial(i, j < i ? j : j + 1, true);
        state.update_score_partial(j < i ? j - 1 : j, j < i ? j : j + 1, false);

        score = state.get_score();

        #ifdef DEBUG
        if (iter_count % 100000 == 0) cerr << iter_count << " " << score << " " << last_score << " " << best_score << " " << temperature << " " << theTimer.time() << endl;
        #endif

        if (score <= last_score) {
          int visit_order_to_insert = state.visit_order[i];
          state.visit_order.erase(state.visit_order.begin() + i);
          state.visit_order.insert(state.visit_order.begin() + j, visit_order_to_insert);
          last_score = score;
          if (score < best_score) {
            best_score = score;
          }
        }
        else if (theRandom.nextDouble() < exp(double(last_score - score) / temperature)) { // accept
          int visit_order_to_insert = state.visit_order[i];
          state.visit_order.erase(state.visit_order.begin() + i);
          state.visit_order.insert(state.visit_order.begin() + j, visit_order_to_insert);
          last_score = score;
        }
        else { // rollback
          state.update_score_partial(i - 1, i, true);
          state.update_score_partial(i, i + 1, true);
          state.update_score_partial(i - 1, i + 1, false);
          state.update_score_partial(j < i ? j - 1 : j, i, false);
          state.update_score_partial(i, j < i ? j : j + 1, false);
          state.update_score_partial(j < i ? j - 1 : j, j < i ? j : j + 1, true);
          score = last_score;
        }
      }
      else if (roll < 1.0) {
        int i = theRandom.nextUIntMod(env.pill_num) + 1;
        int j = theRandom.nextUIntMod(env.pill_num) + 1;
        if (i == j) continue;
        if (i > j) swap(i, j);

        state.update_score_partial(i - 1, i, false);
        state.update_score_partial(j - 1, j, false);
        state.update_score_partial(i - 1, j - 1, true);
        state.update_score_partial(i, j, true);

        score = state.get_score();

        #ifdef DEBUG
        if (iter_count % 100000 == 0) cerr << iter_count << " " << score << " " << last_score << " " << best_score << " " << temperature << " " << theTimer.time() << endl;
        #endif

        if (score <= last_score) {
          reverse(state.visit_order.begin() + i, state.visit_order.begin() + j);
          last_score = score;
          if (score < best_score) {
            best_score = score;
          }
        }
        else if (theRandom.nextDouble() < exp(double(last_score - score) / temperature)) { // accept
          reverse(state.visit_order.begin() + i, state.visit_order.begin() + j);
          last_score = score;
        }
        else { // rollback
          state.update_score_partial(i - 1, i, true);
          state.update_score_partial(j - 1, j, true);
          state.update_score_partial(i - 1, j - 1, false);
          state.update_score_partial(i, j, false);
          score = last_score;
        }
      }

      // temperature *= 1.0 - decay_rate;
      temperature = exp(log(base_temperature) - ((log(base_temperature) - log(target_temperature)) * ((theTimer.time() - time_start) * (1.0 / (time_limit - time_start)))));
      iter_count++;
    }

    cerr << "iter_count  = " << iter_count << endl;
    cerr << "last_score  = " << last_score << endl;
    cerr << "best_score  = " << best_score << endl;
    cerr << "temperature = " << temperature << endl;
  }

  Output output = state.create_output();
  return output;
}

Output solve(const Environment &env) {
  Output output = solve_sa(env);
  return output;
}

void print_output(const Output &output) {
  cout << output.path << endl;
}

int main(int argc, char *argv[]) {
  cin.tie(0);
  ios::sync_with_stdio(false);

  HyperParameter::load_hyper_parameter(argc, argv);

  const auto input = get_input();

  const auto env = create_environment(input);

  const auto output = solve(env);

  print_output(output);

  return 0;
}
