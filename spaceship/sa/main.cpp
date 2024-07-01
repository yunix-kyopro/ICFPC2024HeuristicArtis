
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <chrono>
#include <algorithm>
#include <random>
#include <map>
#include <set>
#include <queue>
#include <random>
#include <chrono>
#include <cmath>
#include <climits>
#include <bitset>
#include <time.h>
#include <cassert>
#include <iomanip>

using namespace std;
using Ps = pair<short, short>;
using vec_int = vector<int>;
using P = pair<int, int>;
using P2 = pair<P, P>;
using P3 = pair<float, int>;
using Tu = tuple<int, int, int>;
using T2 = tuple<float, int, int>;
using T3 = tuple<float, int, int, int, int>;
using T4 = tuple<int, int, int, int>;
using T5 = tuple<int, int, int, int, int>;
using TT = tuple<int, int, int>;
using ll = long long;
using uc = unsigned char;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int h[20][20];

// #pragma GCC optimize("Ofast")

std::mt19937 mt{12345};
double TIME_LIMIT = 15000; // ms
int RAND_ARR_LEN = 100000;
int RAND_RANGE = 1000000000;
const int JOB_MAX_LEN = 1003;
std::uniform_int_distribution<int> dist(1, RAND_RANGE);

int WAITING_TASK = 1001;

void remove_val_and_pop_from_last(vec_int &A, int val)
{
    for (int i = 0; i < A.size(); i++)
    {
        if (A.at(i) == val)
        {
            A.at(i) = A.at(A.size() - 1);
            A.pop_back();
            return;
        }
    }
    throw runtime_error("trying to remove non-existing value");
}

class Rand
{
private:
    int count = 0;
    vec_int rand_arr;

public:
    Rand(){
        rep(i, RAND_ARR_LEN){
            rand_arr.push_back(dist(mt));
}
}
;
int get();
int get_rand(int from, int to);
float get_float();
}
;

int Rand::get()
{
    int num = rand_arr.at(count);
    count += 1;
    count %= RAND_ARR_LEN;
    return num;
}

int Rand::get_rand(int from, int to)
{
    int diff = to - from;
    int num = get() % diff;
    return num + from;
}

float Rand::get_float()
{
    // 0~1の間の一様乱数
    return (float)get() / (float)RAND_RANGE;
}

Rand ro;

class PseudoSet
{
private:
    vec_int index_arr;

public:
    vec_int data;
    PseudoSet(){};
    PseudoSet(int value_range)
    {
        index_arr = vec_int(value_range, -1);
    }

    bool count(int value);
    void insert(int value);
    void erase(int value);
    vec_int get_data() { return data; };
    int size() { return data.size(); };
    int get_random() { return data.at(ro.get_rand(0, size())); };
};

bool PseudoSet::count(int value)
{
    return index_arr[value] != -1;
}

void PseudoSet::insert(int value)
{
    if (count(value))
        return;
    index_arr[value] = data.size();
    data.push_back(value);
}

void PseudoSet::erase(int value)
{
    if (!count(value))
    {
        // throw runtime_error("no existing value:"+to_string(value));
        return;
    }
    int tail_value = data[data.size() - 1];
    if (value == tail_value)
    {
        data.pop_back();
        index_arr[value] = -1;
    }
    else
    {
        index_arr[tail_value] = index_arr[value];
        index_arr[value] = -1;
        data[index_arr[tail_value]] = tail_value;
        data.pop_back();
    }
}

float get_time(bool init)
{
    static std::chrono::system_clock::time_point start;
    if (init)
    {
        start = std::chrono::system_clock::now();
    }
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // 処理に要した時間をミリ秒に変換
}

double current_tmp(double current_time, double T0, double T1)
{
    return T1 + (T0 - T1) * (TIME_LIMIT - current_time) / (TIME_LIMIT);
    // double start_time = TIME_LIMIT * 0.6;
    // double x = (current_time - start_time) / (TIME_LIMIT * 0.32);
    // return pow(T1, 1 - x) + (T0, x);
}

bool is_valid_transition(int diff, double current_time, double T0, float T1)
{
    float t = current_tmp(current_time, T0, T1);
    float rand = ro.get_float();
    // diffが正だったら常にアクセぷと
    return rand < exp(((float)diff) / t);
}

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vl = vector<ll>;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vector<T>>;

#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define repr(i, n) for (int i = (n) - 1; i >= 0; i--)
#define repe(i, l, r) for (int i = (l); i < (r); i++)
#define reper(i, l, r) for (int i = (r) - 1; i >= (l); i--)
#define repa(i, n) for (auto &i : n)

template <class T1, class T2>
inline bool chmax(T1 &a, const T2 &b)
{
    if (a < b)
    {
        a = b;
        return 1;
    }
    return 0;
}
template <class T1, class T2>
inline bool chmin(T1 &a, const T2 &b)
{
    if (b < a)
    {
        a = b;
        return 1;
    }
    return 0;
}

struct init
{
    init()
    {
        cin.tie(0);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(15);
        // cerr << fixed << setprecision(15);
    }
} init_;

template <typename T, typename U>
ostream &operator<<(ostream &out, const pair<T, U> &a) { return out << a.first << ' ' << a.second; }
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &a)
{
    for (auto it = a.begin(); it != a.end();)
    {
        out << *it;
        if (++it != a.end())
            out << ' ';
    }
    return out;
}
template <typename T, size_t N>
ostream &operator<<(ostream &out, const array<T, N> &a)
{
    for (auto it = a.begin(); it != a.end();)
    {
        out << *it;
        if (++it != a.end())
            out << ' ';
    }
    return out;
}
template <typename T>
ostream &operator<<(ostream &out, const set<T> &a)
{
    for (auto it = a.begin(); it != a.end();)
    {
        out << *it;
        if (++it != a.end())
            out << ' ';
    }
    return out;
}
template <typename T, typename U>
ostream &operator<<(ostream &out, const map<T, U> &a)
{
    for (auto it = a.begin(); it != a.end();)
    {
        out << *it;
        if (++it != a.end())
            out << '\n';
    }
    return out;
}

#ifndef DEBUG
template <class T, class N>
void verr(const vector<T> &a, const N &n)
{
    return;
    rep(i, n) cerr << a[i] << " ";
    cerr << endl;
}
template <class T, class N, size_t AN>
void verr(const array<T, AN> &a, const N &n)
{
    return;
    rep(i, n) cerr << a[i] << " ";
    cerr << endl;
}
ll dbgt = 1;
void err()
{
    return;
    cerr << "passed " << dbgt++ << endl;
}
template <class H, class... T>
void err(H &&h, T &&...t)
{
    return;
    cerr << h << (sizeof...(t) ? " " : "\n") << flush;
    if (sizeof...(t) > 0)
        err(forward<T>(t)...);
}
#else
void err() {}
template <class H, class... T>
void err(H &&h, T &&...t) {}
template <class H, class... T>
void verr(H &&h, T &&...t) {}
#endif

// const ll INF = 4e18;
const int INF = 1e9;
const ld EPS = 1e-11;
const ld PI = acos(-1.0L);
// const ll MOD = 1e9 + 7;
const ll MOD = 998244353;
//--------------------------------------------------------------------------------//

inline uint32_t pcg32()
{
    static uint64_t x = 0x0123456789012345u;
    unsigned count = (unsigned)(x >> 61);
    x *= 3;
    x ^= x >> 22;
    return (uint32_t)(x >> (22 + count));
}
#pragma endregion

// 時間を出力
chrono::system_clock::time_point startTime, endTime;

// 経過時間(ms) を取得
int get_diff_time()
{
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - startTime).count();
}

// [0, a)の整数乱数
inline int get_randint(int a)
{
    return (long long)pcg32() * a >> 32;
}

// [0, 1]の乱数
inline double get_randdouble()
{
    return pcg32() / (double)numeric_limits<uint32_t>::max();
}

// 固定パラメータ

// ハイパーパラメータ ---------------------------------
int ZERO = 0;

enum hyper_param_idx
{
    ZERO_ID,
};

using Pair = pair<ll, ll>;

Pair add(Pair a, Pair b)
{
    return {a.first + b.first, a.second + b.second};
}

Pair sub(Pair a, Pair b)
{
    return {a.first - b.first, a.second - b.second};
}

const int dx[] = {-1, 0, 1}, dy[] = {-1, 0, 1};
Pair get_differential(int d)
{
    assert(0 <= d && d < 9);
    return {dx[d % 3], dy[d / 3]};
}

int get_diff_idx(Pair p)
{
    assert(-1 <= p.first && p.first <= 1);
    assert(-1 <= p.second && p.second <= 1);
    return (p.second + 1) * 3 + (p.first + 1);
}

void solve_greedy(vc<pair<ll, ll>> input)
{
    ll N = input.size();

    // const int N = input.size();
    vector<int> ans;
    Pair p = {0, 0}, v = {0, 0};

    rep(i, N)
    {
        auto calc = [&](ll diff) -> vector<int>
        {
            if (diff == 0)
                return vector<int>(0);
            const int dist = abs(diff);
            vector<int> ret;
            ll ok = 0, ng = 1e6;
            while (ng - ok > 1)
            {
                ll mid = (ok + ng) / 2;
                ll sum = mid * mid;
                // err("sum", sum, "mid", mid, "dist", dist);
                (sum <= dist ? ok : ng) = mid;
            }

            ll rest = dist - ok * ok;
            assert(rest >= 0);
            // err("ok", ok, dist, rest);

            ll u = diff == 0 ? 0 : diff / abs(diff);

            ll nowd = 0, nowv = 0;
            rep(_, ok)
            {
                ret.eb(u);
                nowv += u;
                nowd += abs(nowv);
            }
            rep(v, ok)
            {
                while (rest >= ok - v)
                {
                    nowd += abs(nowv);
                    rest -= ok - v;
                    ret.eb(0);
                }
                ret.eb(-u);
                nowv += -u;
                nowd += abs(nowv);
            }

            assert(nowd == dist);

            return ret;
        };

        auto xs = calc(input[i].first - p.first);
        auto ys = calc(input[i].second - p.second);

        // err(i);
        // err(xs);
        // err(ys);

        while (xs.size() < ys.size())
            xs.eb(0);
        while (ys.size() < xs.size())
            ys.eb(0);
        assert(xs.size() == ys.size());

        rep(j, xs.size())
        {
            ans.eb(get_diff_idx({xs[j], ys[j]}));
        }

        p = input[i];
    }

    string res;
    p = {0, 0}, v = {0, 0};
    rep(i, ans.size())
    {
        res += to_string(ans[i] + 1);
        v = add(v, get_differential(ans[i]));
        p = add(p, v);
    }
    cout << res << endl;
}

constexpr int V = 10;
constexpr int MAX_N = 1000;
constexpr int MAX_TURN = 12;
constexpr int K = V;
// ほかの速度の下界に対して別の速度を採用する猶予
constexpr int LB_MARGIN = 1000;
using TP = int32_t;
const TP dpinf = numeric_limits<TP>::max();
pair<TP, TP> from[MAX_N + 1][2 * V + 1][2 * V + 1];
// dp[i][vx][vy] := i番目の移動を終えたときに座標(vx, vy)にいるときの最小の経過ターン数
TP dp[MAX_N + 1][2 * V + 1][2 * V + 1];
int mindiff[MAX_TURN + 1][2 * V + 1][2 * V + 1], maxdiff[MAX_TURN + 1][2 * V + 1][2 * V + 1];

// turnでdiffだけ変化して始端速度(svx,svy)から終端速度(tvx,tvy)に変化するときの経路
// 経路が必ず存在すると仮定
string get_route(int turn, int svx, int svy, int tvx, int tvy, int diffx, int diffy)
{
    auto route = [&](int sv, int tv, int diff) -> vector<int>
    {
        vector<int> ret;

        vector<int> order;
        {
            int u = (tv - sv) == 0 ? 0 : (tv - sv) / abs(tv - sv);
            for (int k = 0; k < abs(tv - sv) + 1; k++)
                order.emplace_back(sv + k * u);
            for (int k = 0; k < turn - abs(tv - sv); k++)
                order.emplace_back(tv);
        }
        int M = order.size();
        int now = accumulate(order.begin() + 1, order.end(), 0);
        int rest = diff - now;

        while (rest != 0)
        {
            for (int i = 1; i < M - 1; i++)
            {
                if (rest > 0)
                {
                    if (order[i - 1] >= order[i] && order[i] <= order[i + 1])
                    {
                        order[i]++;
                        rest--;
                    }
                }
                else if (rest < 0)
                {
                    if (order[i - 1] <= order[i] && order[i] >= order[i + 1])
                    {
                        order[i]--;
                        rest++;
                    }
                }
                if (rest == 0)
                    break;
            }
            if (rest == 0)
                break;
        }

        for (int i = 0; i < M - 1; i++)
        {
            ret.emplace_back(order[i + 1] - order[i]);
        }

        return ret;
    };

    auto xs = route(svx, tvx, diffx);
    auto ys = route(svy, tvy, diffy);
    assert(xs.size() == ys.size());

    string ret;
    for (int j = (int)xs.size() - 1; j >= 0; j--)
    {
        ret += to_string((xs[j] + 1) + 1 + (ys[j] + 1) * 3);
    }

    return ret;
}

string solve_dp(vector<P> input)
{
    int N = input.size();
    input.insert(input.begin(), {0, 0});
    /*
    repa(p, input)
    {
        err(p);
    }
    */

    // mindiff, maxdiffの前計算
    // mindiff[T][sv][tv] := Tターンかけてsvからtvに移動するときの最小のdiff
    rep(T, MAX_TURN + 1)
    {
        rep(sv, 2 * V + 1) rep(tv, 2 * V + 1)
        {
            mindiff[T][sv][tv] = INF;
            maxdiff[T][sv][tv] = -INF;
        }
    }
    repe(v, -V, V + 1)
    {
        mindiff[0][v + V][v + V] = 0;
        maxdiff[0][v + V][v + V] = 0;
    }
    repe(T, 1, MAX_TURN + 1)
    {
        repe(sv, -V, V + 1) repe(tv, -V, V + 1)
        {
            if (abs(sv - tv) > T)
                continue;
            const int d = abs(sv - tv);
            const int rest = T - d;

            const int maxv = max(sv, tv) + rest / 2;
            int maxsum = maxv * (rest % 2);
            if (sv < maxv)
                maxsum += (maxv - sv) * (sv + 1 + maxv) / 2;
            if (tv < maxv)
                maxsum += (maxv - tv) * (tv + maxv - 1) / 2;
            maxdiff[T][sv + V][tv + V] = maxsum;

            const int minv = min(sv, tv) - rest / 2;
            int minsum = minv * (rest % 2);
            if (minv < sv)
                minsum += (sv - minv) * (sv + minv - 1) / 2;
            if (minv < tv)
                minsum += (tv - minv) * (tv + 1 + minv) / 2;
            mindiff[T][sv + V][tv + V] = minsum;

            // err("turn", T, sv, tv, "max", maxsum, "min", minsum);
        }
    }

    rep(i, N + 1)
    {
        rep(j, 2 * V + 1)
        {
            rep(k, 2 * V + 1)
            {
                dp[i][j][k] = dpinf;
            }
        }
    }

    dp[0][V][V] = 0;
    from[0][V][V] = {-1, -1};
    rep(i, N)
    {

        // if (i % 10 == 0)
        // cerr << "turn:" << i << " " << get_time(false) << endl;
        // if(i % 10 == 0) err("dp", i, "/", N);
        // err("dp", i, "/", N);
        int lb = dpinf;
        rep(sv, 2 * V + 1) rep(tv, 2 * V + 1)
        {
            if (dp[i][sv][tv] == dpinf)
                continue;
            chmin(lb, dp[i][sv][tv]);
        }

        int count = 0;
        repe(svx, -V, V + 1) repe(svy, -V, V + 1)
        {
            if (dp[i][svx + V][svy + V] == dpinf)
                continue;
            if (dp[i][svx + V][svy + V] > lb + LB_MARGIN)
                continue;

            repe(tvx, max(-V, svx - K), min(V, svx + K) + 1) repe(tvy, max(-V, svy - K), min(V, svy + K) + 1)
            {
                if (i < N - 1 && i > 0)
                {
                    double angle1 = atan2(tvy, tvx);
                    double angle2 = atan2(input[i + 1].second - input[i - 1].second, input[i + 1].first - input[i - 1].first);
                    double diff = min(fabs(angle1 - angle2), 2 * M_PI - fabs(angle1 - angle2));
                    // if (fabs(diff) > 0.1)
                    //    continue;
                }
                count++;

                const pair<int, int> diffs = sub(input[i + 1], input[i]);

                auto check = [&](int turn, int sv, int tv, int diff) -> bool
                {
                    return mindiff[turn][sv + V][tv + V] <= diff && diff <= maxdiff[turn][sv + V][tv + V];
                };
                rep(t, MAX_TURN + 1)
                {
                    if (check(t, svx, tvx, diffs.first) && check(t, svy, tvy, diffs.second))
                    {
                        if (chmin(dp[i + 1][tvx + V][tvy + V], dp[i][svx + V][svy + V] + t))
                        {
                            from[i + 1][tvx + V][tvy + V] = {svx + V, svy + V};
                        }
                        break;
                    }
                }
            }
        }
        if (count == 0)
            break;
    }

    int sc = dpinf, nvx = -1, nvy = -1;
    rep(i, 2 * V + 1) rep(j, 2 * V + 1)
    {
        if (chmin(sc, dp[N][i][j]))
        {
            nvx = i;
            nvy = j;
        }
    }
    assert(nvx != -1 and nvy != -1);

    vc<int> ans;
    repr(i, N)
    {
        auto [fvx, fvy] = from[i + 1][nvx][nvy];
        auto t = dp[i + 1][nvx][nvy] - dp[i][fvx][fvy];

        auto diffs = sub(input[i + 1], input[i]);
        assert(mindiff[t][fvx][nvx] <= diffs.first && diffs.first <= maxdiff[t][fvx][nvx]);
        assert(mindiff[t][fvy][nvy] <= diffs.second && diffs.second <= maxdiff[t][fvy][nvy]);

        auto route = [&](int sv, int tv, int diff) -> vector<int>
        {
            vc<int> ret;

            vc<int> order;
            {
                int u = tv - sv == 0 ? 0 : (tv - sv) / abs(tv - sv);
                rep(k, abs(tv - sv) + 1) order.eb(sv + k * u);
                rep(k, t - abs(tv - sv)) order.eb(tv);
            }
            int M = order.size();
            int now = accumulate(order.begin() + 1, order.end(), 0);
            int rest = diff - now;

            while (rest != 0)
            {
                repe(i, 1, M - 1)
                {
                    if (rest > 0)
                    {
                        if (order[i - 1] >= order[i] and order[i] <= order[i + 1])
                        {
                            order[i]++;
                            rest--;
                        }
                    }
                    else if (rest < 0)
                    {
                        if (order[i - 1] <= order[i] and order[i] >= order[i + 1])
                        {
                            order[i]--;
                            rest++;
                        }
                    }
                    if (rest == 0)
                        break;
                }
                if (rest == 0)
                    break;
            }

            rep(i, M - 1)
            {
                ret.eb(order[i + 1] - order[i]);
            }

            return ret;
        };

        auto xs = route(fvx - V, nvx - V, diffs.first);
        auto ys = route(fvy - V, nvy - V, diffs.second);
        assert(xs.size() == ys.size());

        vc<int> a;
        repr(j, xs.size())
        {
            a.eb(get_diff_idx({xs[j], ys[j]}));
            ans.eb(get_diff_idx({xs[j], ys[j]}));
        }
        // err("fvx", fvx, "nvx", nvx, "fvy", fvy, "nvy", nvy, "diffs", diffs, "t", t);

        nvx = fvx;
        nvy = fvy;
    }

    reverse(all(ans));
    string res;
    pair<int, int> p = {0, 0}, v = {0, 0};
    rep(i, ans.size())
    {
        res += to_string(ans[i] + 1);
        v = add(v, get_differential(ans[i]));
        p = add(p, v);
    }
    return res;
}

int N;
vec_int xpos, ypos;

double calc_score_full(vector<P> &route)
{
    double result = 0;
    rep(i, N - 1)
    {
        result += max(abs(route[i].first - route[i + 1].first), abs(route[i].second - route[i + 1].second));
    }
    double average = result / (N - 1);

    for (int i = 1; i < N - 1; i++)
    {
        // 速度ベクトルの変更に対してペナルティを与える
        double dx0 = route[i].first - route[i - 1].first;
        double dy0 = route[i].second - route[i - 1].second;
        double dx1 = route[i + 1].first - route[i].first;
        double dy1 = route[i + 1].second - route[i].second;
        double theta0 = atan2(dy0, dx0);
        double theta1 = atan2(dy1, dx1);
        double diff_angle = min(fabs(theta1 - theta0), 2 * M_PI - fabs(theta1 - theta0));
        result += diff_angle * average * 30;
    }
    return result;
}

vector<P> sa(vector<P> initial_route)
{
    double THRESHOLD = 0;
    rep(i, initial_route.size() - 1)
    {
        THRESHOLD += abs(initial_route[i].first - initial_route[i + 1].first) + abs(initial_route[i].second - initial_route[i + 1].second);
    }
    THRESHOLD /= initial_route.size();

    // ルートを焼きなましてより進みやすいルートを探す
    // 具体的には方向転換に対してペナルティをつけたスコアを返す
    double current_score = calc_score_full(initial_route);
    double best_score = current_score;
    vector<P> best_state = initial_route;
    vector<P> state = initial_route;

    double T0 = THRESHOLD * 12;
    double T1 = THRESHOLD * 1;

    cerr << "threshold:" << THRESHOLD << endl;
    cerr << initial_route[0].first << " " << initial_route[0].second << endl;

    while (true)
    {
        float ct = get_time(false);
        if (ct >= TIME_LIMIT)
            break;

        int ind1 = ro.get_rand(1, N - 1);
        int ind2 = ro.get_rand(1, N - 1);
        if (ind1 == ind2 || abs(ind1 - ind2) <= 2)
            continue;

        if (ind1 > ind2)
        {
            swap(ind1, ind2);
        }
        if (ind2 == ind1 + 1)
        {
            continue;
        }

        int x1 = state[ind1].first;
        int y1 = state[ind1].second;
        int x2 = state[ind2].first;
        int y2 = state[ind2].second;
        if (abs(x1 - x2) + abs(y1 - y2) > THRESHOLD * 3.3)
        {
            continue;
        }
        reverse(state.begin() + ind1, state.begin() + ind2 + 1);

        double new_score = calc_score_full(state);
        double diff = new_score - current_score;

        if (is_valid_transition(-diff, ct, T0, T1))
        {
            current_score = new_score;
            if (new_score < best_score)
            {
                cerr << "current_score:" << current_score << endl;
                best_score = new_score;
                best_state = state;
            }
        }
        else
        {
            reverse(state.begin() + ind1, state.begin() + ind2 + 1);
        }
    }
    cerr << "initial_score:" << calc_score_full(initial_route) << endl;
    cerr << "best_score: " << best_score << endl;
    cerr << "best_state: " << best_state[0].first << " " << best_state[0].second << endl;
    return best_state;
}

string run(vector<P> input)
{
    double THRESHOLD = 0;
    rep(i, input.size() - 1)
    {
        THRESHOLD += abs(input[i].first - input[i + 1].first) + abs(input[i].second - input[i + 1].second);
    }
    THRESHOLD /= input.size();

    // sort(input.begin() + 20, input.end(), [](const pair<ll, ll> &a, const pair<ll, ll> &b) {
    //     return (a.first + a.second == b.first + b.second ? a.first < b.first : a.first + a.second < b.first + b.second);
    // });
    // cout << N << endl;
    // repa(p, input) {
    //     cout << p << endl;
    // }
    // return;

    // solve_greedy(input);
    string initial_ans = solve_dp(input);
    cerr << "initial_ans: " << initial_ans << endl;
    cerr << "initial_score:" << initial_ans.size() << endl;

    int initial_score = initial_ans.size();
    auto initial_input = input;

    int cnt = 0;
    int best_score = initial_score;
    string best_ans = initial_ans;

    set<pair<int, int>> used;
    int fail_count = 0;
    double T0 = 0.2;
    double T1 = 0;
    int tot = 1000;
    int current_score = best_score;
    while (cnt < tot)
    {
        double progress = (double)cnt / tot;
        double temp = T0 + (T1 - T0) * progress;

        // 2-optの要領で交換をする
        // ただし交換できる点の距離はマンハッタン距離で5以下とする

        // int ind1 = get_randint(input.size());
        // int ind2 = get_randint(input.size());
        int ind1, ind2;
        // int ind1 = ro.get_rand(54, 67);
        // int ind2 = ro.get_rand(54, 67);
        while (true)
        {
            ind1 = ro.get_rand(1, N - 1);
            ind2 = ro.get_rand(1, N - 1);
            if (ind1 == ind2 || abs(ind1 - ind2) <= 2)
                continue;

            if (ind1 > ind2)
            {
                swap(ind1, ind2);
            }
            if (ind2 == ind1 + 1)
            {
                continue;
            }

            int x1 = input[ind1].first;
            int y1 = input[ind1].second;
            int x2 = input[ind2].first;
            int y2 = input[ind2].second;
            if (abs(x1 - x2) + abs(y1 - y2) > 10)
            {
                continue;
            }
            break;
        }

        // inputのind1+1 ~ ind2-1の間を逆順にする
        reverse(input.begin() + ind1 + 1, input.begin() + ind2);

        string tmp_ans;
        try
        {
            tmp_ans = solve_dp(input);
        }
        catch (...)
        {
            reverse(input.begin() + ind1 + 1, input.begin() + ind2);
            continue;
        }
        double diff = tmp_ans.size() - current_score;

        if (tmp_ans.size() <= current_score || exp(-diff / temp) > ro.get_float())
        {
            current_score = tmp_ans.size();
            if (tmp_ans.size() < best_score)
            {
                best_score = tmp_ans.size();
                best_ans = tmp_ans;
            }
        }
        else
        {
            reverse(input.begin() + ind1 + 1, input.begin() + ind2);
        }

        cerr << "trial: " << cnt << " initial_score:" << initial_score << " current_score" << tmp_ans.size() << " best_score:" << best_score << " " << ind1 << "  " << ind2 << endl;
        cnt++;
    }
    // auto ans = get_route(0, 0, 0, 0, 0, 0, 0);
    // err(ans);
    return best_ans;
}

int main(int argc, char *argv[])
{
#ifdef OPTUNA_STUDY
    cerr << "optuna study, override parameters" << endl;
    T0 = stod(argv[1]);
    T1 = stod(argv[2]);
#endif
    get_time(true);
    cin >> N;
    xpos.resize(N);
    ypos.resize(N);
    rep(i, N)
    {
        cin >> xpos[i] >> ypos[i];
    }

    vector<P> input;
    rep(i, N)
    {
        input.eb(xpos[i], ypos[i]);
    }

    auto input2 = sa(input);
    auto result2 = solve_dp(input2);
    cerr << "result2:" << result2.size() << endl;
    cout << result2 << endl;

    return 0;
}
