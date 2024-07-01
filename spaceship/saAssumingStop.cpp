

namespace atcoder {}

#ifdef LOCAL
#define dbg(x) cerr << __LINE__ << " : " << #x << " = " << (x) << endl;
#else
#define NDEBUG
#define dbg(x) true;
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#endif

#ifdef GTEST
#include <gtest/gtest.h>
#endif

#include <math.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#ifdef PERF
#include <gperftools/profiler.h>
#endif

using namespace std;
using namespace atcoder;
#define fast_io                     \
  ios_base::sync_with_stdio(false); \
  cin.tie(0);                       \
  cout.tie(0);
#define ll long long int
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define reps(i, n) for (int i = 1; i <= (int)(n); i++)
#define REP(i, n) for (int i = n - 1; i >= 0; i--)
#define REPS(i, n) for (int i = n; i > 0; i--)
#define MOD (long long int)(1e9 + 7)
#define INF (int)(1e9)
#define LINF (long long int)(1e18)
#define all(v) v.begin(), v.end()
typedef pair<int, int> Pii;
typedef pair<ll, ll> Pll;
constexpr double PI = M_PI;

#ifdef NDEBUG
#define CHECK(v1, op, v2)
#else
#define CHECK(v1, op, v2)                            \
  if (!((v1)op(v2))) {                               \
    cerr << "ERROR:" << (v1) << " " << (v2) << endl; \
    assert((v1)op(v2));                              \
  }
#endif

long double nCr(const int n, const int r) {
  long double ret = 1;
  rep(t, r) {
    ret *= (n - t);
    ret /= (r - t);
  }
  return ret;
}

template <typename T>
string to_string(const vector<T>& vec) {
  string ret = "";
  rep(i, vec.size()) {
    ret += vec[i].to_string();
    if (i + 1 != vec.size()) {
      ret += ",";
    }
  }
  return ret;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec) {
  os << to_string(vec);
  return os;
}

uint32_t xorshift() {
  static uint32_t x = 12345789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;
  uint32_t t;
  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  w ^= t ^ (t >> 8) ^ (w >> 19);

  return w;
}

int rand(const uint32_t l, const uint32_t r) {
  return xorshift() % (r - l) + l;
}

uint32_t rand_other_than(const uint32_t l, const uint32_t r,
                         const uint32_t other) {
  const uint32_t num = rand(l, r - 1);
  return num + (num >= other);
}

template <typename T>
const T& rand_vec(const vector<T>& vec) {
  assert(vec.size() > 0);
  return vec[rand(0, vec.size())];
}

template <typename T>
void shuffle(vector<T>& vec) {
  rep(l, (int)vec.size() - 1) {
    const int idx = rand(l, vec.size());
    swap(vec[idx], vec[l]);
  }
}

template <class T, class U = T>
bool chmin(T& x, U&& y) {
  return y < x && (x = std::forward<U>(y), true);
}

template <class T, class U = T>
bool chmax(T& x, U&& y) {
  return x < y && (x = std::forward<U>(y), true);
}

template <typename Ret, typename T>
Ret Sum(const vector<T>& vec) {
  return std::accumulate(all(vec), (Ret)0);
}

template <typename Ret, typename T>
Ret Mean(const vector<T>& vec) {
  assert((int)vec.size() > 0);
  return Sum<T, Ret>(vec) / vec.size();
}

template <typename Ret, typename T>
Ret Std(const vector<T>& vec) {
  assert((int)vec.size() > 0);
  const auto mean = Mean<Ret>(vec);
  const auto sum2 = std::accumulate(
      all(vec), (Ret)0,
      [](const Ret acc, const T val) { return acc + (Ret)val * val; });
  return (Ret)sum2 / vec.size() - mean * mean;
}

class Timer {
  chrono::system_clock::time_point _start, _end;
  ll _sum = 0, _count = 0;

 public:
  void start() { _start = chrono::system_clock::now(); }

  void stop() { _end = chrono::system_clock::now(); }

  void add() {
    const chrono::system_clock::time_point now = chrono::system_clock::now();
    _sum += static_cast<double>(
        chrono::duration_cast<chrono::nanoseconds>(now - _start).count());
    _count++;
  }

  ll sum() const { return _sum / 1000; }

  int count() const { return _count; }

  string average() const {
    if (_count == 0) {
      return "NaN";
    }
    return to_string(_sum / 1000 / _count);
  }

  void reset() {
    _start = chrono::system_clock::now();
    _sum = 0;
    _count = 0;
  }

  inline int ms() const {
    const chrono::system_clock::time_point now = chrono::system_clock::now();
    return static_cast<double>(
        chrono::duration_cast<chrono::microseconds>(now - _start).count() /
        1000);
  }

  inline int ns() const {
    const chrono::system_clock::time_point now = chrono::system_clock::now();
    return static_cast<double>(
        chrono::duration_cast<chrono::microseconds>(now - _start).count());
  }
};

#ifdef LOCAL
struct Timers : unordered_map<string, Timer> {
  friend ostream& operator<<(ostream& os, const Timers& timers) {
    for (const auto& pa : timers) {
      os << pa.first << " time: " << pa.second.sum() / 1000
         << " count: " << pa.second.count() << endl;
    }
    return os;
  }
};
#else
struct Timers {
  struct Dummy {
    void start() const {}
    void add() const {}
  };
  Dummy dummy;
  const Dummy& operator[](const std::string& str) { return dummy; }
  friend ostream& operator<<(ostream& os, const Timers& timers) { return os; }
};
#endif

Timers global_timers;

/* start */

Timer global_timer;

int N;
vector<ll> dist2Turns;
struct Pos {
  ll x, y;
  Pos(ll x, ll y) : x(x), y(y) {}

  ll NeedTurn(const Pos& other) const {
    const ll maxDist = max(abs(x - other.x), abs(y - other.y));
    assert(maxDist < (int)dist2Turns.size());
    return dist2Turns[maxDist];
  }

  static void StaticInit() {
    dist2Turns.resize((int)1e7);
    for (ll t = 0; t < (int)1e7; t++) {
      ll maxDist = t * t;
      if (maxDist + 1 >= (int)dist2Turns.size()) break;
      dist2Turns[maxDist + 1] = (t + 1) * 2;
    }
    // 累積和
    for (ll i = 1; i < (int)1e7; i++) {
      dist2Turns[i] = max(dist2Turns[i], dist2Turns[i - 1]);
    }
  }

  bool operator==(const Pos& other) const {
    return x == other.x && y == other.y;
  }
};
vector<Pos> input_poses;

struct Output {
  static void StaticInit(istream& is) {
    global_timer.start();
    cin >> N;
    Pos::StaticInit();
    rep(i, N) {
      ll x, y;
      cin >> x >> y;
      cerr << x << " " << y << endl;
      input_poses.emplace_back(x, y);
    }
  }
  friend ostream& operator<<(ostream& os, const Output& output) { return os; }
};

/* start */

vector<double> PARAMS = {1.0, 0.1};

/* start */

// NBD = neighborhood
template <class Solution, class NBDGenerator>
struct SimulatedAnnealing {
 public:
  SimulatedAnnealing(double end_time, double start_temp, double end_temp)
      : end_time_(end_time * 1000),  // ns
        inv_time_(1.0 / end_time_),
        cur_time_(0.0),
        start_temp_(start_temp),
        end_temp_(end_temp),
        diff_temp_(end_temp_ / start_temp_),
        cur_temp_(start_temp) {
    assert(start_temp >= end_temp);
    timer_.start();
  }

  Solution run(const Solution& initial_sol, NBDGenerator& nbd_generator) {
    Solution sol(initial_sol);

    int acc = 0;
    int g = 0;
    for (;; ++g) {
      if ((g & 0xff) == 0) {
#ifdef SA_MAX_G
        if (g >= SA_MAX_G) {
          break;
        }
#endif
        UpdateTime();
        UpdateTemp();
        if (cur_time_ > end_time_) {
          break;
        }
      }

      const auto nbd = nbd_generator.Generate(&sol, g, cur_time_ * inv_time_);
      constexpr int mod = 1'000'000'000;
      const int r = rand(0, mod);
      if (static_cast<double>(r) / mod < exp(-nbd->Diff() / cur_temp_)) {
        acc++;
        nbd->Update(&sol);
      } else {
        nbd->Restore(&sol);
      }
    }
    cerr << "g,acc: " << g << " " << acc << endl;
    return sol;
  }

 private:
  double end_time_, inv_time_, cur_time_;
  double start_temp_, end_temp_, diff_temp_, cur_temp_;
  Timer timer_;

  void UpdateTime() { cur_time_ = timer_.ns(); }
  void UpdateTemp() {
    cur_temp_ = start_temp_ * pow(diff_temp_, cur_time_ * inv_time_);
    // cur_temp_ = max(0.0, start_temp_ - cur_time_ * diff_temp_ * inv_time_);
  }
};

/*

実装手順
0. Output::StaticInit(istream&)を実装
1. Solutionの初期解生成を書く
2. Solutionに対する操作とEvalの更新を書く
3. Evalの初期値計算を書く
4. Eval::Sum()とSolution::Score()を書く
5. 近傍操作と復元操作を書く
6. 近傍の各確率を調整

*/

struct Eval {
  // 最大化問題の場合は符号を反転すること
  ll needTurnSum = 0;
  double Sum() const { return needTurnSum; }
};

struct Solution {
  vector<int> orders;
  Eval eval;

  Solution() {}
  void InitEval() {
    eval.needTurnSum = 0;
    rep(i, N) { eval.needTurnSum += NeedTurn(i, (i + 1) % N); }
  }
  const Pos& GetPos(const int order) const {
    return input_poses[orders[order]];
  }
  ll NeedTurn(const int i, const int j) const {
    return GetPos(i).NeedTurn(GetPos(j));
  }

  void TwoOpt(const int l, const int r) {
    eval.needTurnSum -=
        NeedTurn((l - 1 + N) % N, l) + NeedTurn((r - 1 + N) % N, r % N);
    eval.needTurnSum +=
        NeedTurn((l - 1 + N) % N, (r - 1 + N) % N) + NeedTurn(r % N, l);
  }

  void AcceptTwoOpt(const int l, const int r) {
    reverse(orders.begin() + l, orders.begin() + r);
  }

  void RestoreTwoOpt(const int l, const int r) {
    eval.needTurnSum +=
        NeedTurn((l - 1 + N) % N, l) + NeedTurn((r - 1 + N) % N, r % N);
    eval.needTurnSum -=
        NeedTurn((l - 1 + N) % N, (r - 1 + N) % N) + NeedTurn(r % N, l);
  }

  static Solution CreateInitialSol() {
    Solution sol;
    sol.orders.resize(N);
    std::iota(all(sol.orders), 0);
    sol.InitEval();
    return sol;
  }
  double Eval() const { return eval.Sum(); }
  double Score() const { return -Eval(); }
  friend ostream& operator<<(ostream& os, const Solution& sol) { return os; }
};

struct NBD {
  double Diff() const { return diff; }
  virtual void Update(Solution*) const = 0;
  virtual void Restore(Solution*) const = 0;
  double diff;
};

struct NBD1 : public NBD {
  NBD1() {}
  NBD1(Solution* const sol) {
    diff = -sol->Eval();
    rep(t, 100) {
      l = rand(0, N);
      r = rand(0, N);
      if (l == r) continue;
      if (l > r) swap(l, r);
      if (l + 1 == r) continue;
      sol->TwoOpt(l, r);
      diff += sol->Eval();
      return;
    }
    assert(false);
  }
  void Update(Solution* sol) const override {
    sol->AcceptTwoOpt(l, r);
    // auto memo = sol->eval;
    // sol->InitEval();
    // if(memo.needTurnSum != sol->eval.needTurnSum){
    //   cerr << memo.needTurnSum << " " << sol->eval.needTurnSum << endl;
    //   cerr << l << " " << r << endl;
    // }
    // assert(memo.needTurnSum == sol->eval.needTurnSum);
  }
  void Restore(Solution* sol) const override {
    sol->RestoreTwoOpt(l, r);
    // auto memo = sol->eval;
    // sol->InitEval();
    // if(memo.needTurnSum != sol->eval.needTurnSum){
    //   cerr << memo.needTurnSum << " " << sol->eval.needTurnSum << endl;
    //   cerr << l << " " << r << endl;
    // }
    // assert(memo.needTurnSum == sol->eval.needTurnSum);
  }

  int l, r;
};

struct NBD2 : public NBD {
  NBD2() {}
  NBD2(Solution* const sol) {}
  void Update(Solution* sol) const override {}
  void Restore(Solution* sol) const override {}
};

struct NBDGenerator {
  NBD* Generate(Solution* const sol, const int g, const double progress) {
    // if (sol->Eval() > best_sol.Eval()) {
    //   best_sol = *sol;
    // }
    const int random = rand(0, 100);
    if (random < 100) {
      nbd1_ = NBD1(sol);
      return &nbd1_;
    } else if (random < 100) {
      nbd2_ = NBD2(sol);
    } else {
      assert(false);
    }
  }
  const Solution& GetBestSol() const { return best_sol; }

 private:
  NBD1 nbd1_;
  NBD2 nbd2_;
  Solution best_sol;
};

void GoTo(vector<int>& dxs, vector<int>& dys, const Pos from, const Pos to,
          const int turn) {
  if (turn == 0) {
    return;
  }
  vector<int> addDxs(turn);
  vector<int> addDys(turn);
  const int dx = from.x < to.x ? 1 : -1;
  const int dy = from.y < to.y ? 1 : -1;
  int remainDiffX = abs(from.x - to.x);
  int remainDiffY = abs(from.y - to.y);
  assert(turn % 2 == 0);

  int xl = 0;
  int xr = turn - 1;
  int yl = 0;
  int yr = turn - 1;
  while (true) {
    if (remainDiffX > 0) {
      const int moveX = (turn - xl) - (turn - xr);
      assert(moveX > 0);
      if (moveX > remainDiffX) {
        xr--;
        continue;
      }
      remainDiffX -= moveX;
      addDxs[xl++] = dx;
      addDxs[xr--] = -dx;
      continue;
    }
    if (remainDiffY > 0) {
      const int moveY = (turn - yl) - (turn - yr);
      assert(moveY > 0);
      if (moveY > remainDiffY) {
        yr--;
        continue;
      }
      remainDiffY -= moveY;
      addDys[yl++] = dy;
      addDys[yr--] = -dy;
      continue;
    }
    break;
  }

  {
    // シミュレーションでデバッグ
    Pos currentPos = from;
    Pos currentV = Pos(0, 0);
    rep(i, turn) {
      currentV.x += addDxs[i];
      currentV.y += addDys[i];
      currentPos.x += currentV.x;
      currentPos.y += currentV.y;
    }
    assert(currentPos == to);
    assert(currentV == Pos(0, 0));
  }

  dxs.insert(dxs.end(), all(addDxs));
  dys.insert(dys.end(), all(addDys));
}

// dx, dyを返す
pair<vector<int>, vector<int>> Fukugen(vector<int>& order) {
  vector<int> dxVec, dyVec;
  Pos currentPos = Pos(0, 0);
  ll minTurn = LINF;
  int bestIdx = -1;
  bool isRev = false;

  rep(i, N) {
    // 初期地点からtoに向かう
    {
      // reverseはしない
      const auto to = input_poses[order[i]];
      const int needTurn =
          currentPos.NeedTurn(to) -
          input_poses[order[i]].NeedTurn(input_poses[order[(i - 1 + N) % N]]);
      if (chmin(minTurn, needTurn)) {
        bestIdx = i;
        isRev = false;
      }
    }
    {
      // reverseする
      const auto to = input_poses[order[i]];
      const int needTurn =
          currentPos.NeedTurn(to) -
          input_poses[order[i]].NeedTurn(input_poses[order[(i + 1) % N]]);
      if (chmin(minTurn, needTurn)) {
        bestIdx = i;
        isRev = true;
      }
    }
  }

  if (isRev) {
    reverse(order.begin(), order.end());
    bestIdx = N - bestIdx - 1;
  }
  // bestIdxが先頭に来るようにする
  vector<int> newOrder(N);
  rep(i, N) { newOrder[i] = order[(bestIdx + i) % N]; }
  order = newOrder;

  rep(i, N) {
    const auto to = input_poses[newOrder[i]];
    GoTo(dxVec, dyVec, currentPos, to, currentPos.NeedTurn(to));
    currentPos = to;
  }

  return std::make_pair(dxVec, dyVec);
}

int DeltaToUchu(const int dx, const int dy) { return dx + dy * 3 + 5; }

void Run() {
  Solution first_sol = Solution::CreateInitialSol();
  NBDGenerator gen;
  SimulatedAnnealing<Solution, NBDGenerator> SA(59500 - global_timer.ms(), 1e4,
                                                1e-1);
  const auto final_sol = SA.run(first_sol, gen);
  auto orders = final_sol.orders;
  const auto [dxVec, dyVec] = Fukugen(orders);
  cerr << "score: " << dxVec.size() << endl;
  cout << "score: " << dxVec.size() << endl;
  cout << endl;
  cout << N << endl;
  rep(i, N) {
    cout << input_poses[orders[i]].x << " " << input_poses[orders[i]].y << endl;
  }
  cout << endl;
  assert(dxVec.size() == dyVec.size());
  rep(i, dxVec.size()) {
    const auto dx = dxVec[i];
    const auto dy = dyVec[i];
    cout << DeltaToUchu(dx, dy);
  }
  cout << endl;
}

/* start */

class Solver {
 public:
  Solver() {}
  void Solve() {
    Run();
    return;
  }

 private:
};

int main(int argc, char* argv[]) {
  fast_io;

  if (argc >= 2) {
    int idx = 0;
    for (int i = 1; i < argc; ++i) {
      PARAMS[idx++] = std::stod(argv[i]);
    }
  }

  Timer timer;
  timer.start();
  Output::StaticInit(cin);
  Solver solver;
  solver.Solve();
  return 0;
}