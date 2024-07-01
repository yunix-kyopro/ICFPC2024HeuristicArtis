#pragma region MACRO
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
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
#define rep(i, n) for (int i = 0; i < (n); i++)
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
        cerr << fixed << setprecision(15);
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
    rep(i, n) cerr << a[i] << " ";
    cerr << endl;
}
template <class T, class N, size_t AN>
void verr(const array<T, AN> &a, const N &n)
{
    rep(i, n) cerr << a[i] << " ";
    cerr << endl;
}
ll dbgt = 1;
void err() { cerr << "passed " << dbgt++ << endl; }
template <class H, class... T>
void err(H &&h, T &&...t)
{
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
double TIME_LIMIT = 1850; // ms

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

// パラメータ --------------------------------------
constexpr int V = 70;
// 負側の速さ（正側の速さの最大は(2V-MX, 2V-MY)になる）
constexpr int MX = 70, MY = 70;
constexpr int MAX_N = 8192;
constexpr int MAX_TURN = 40;
// 始端速度(svx, svy)に対して取りうる終端速度の範囲(svx±K, svy±K)
constexpr int K = 40;
// dpの最小がvのとき、v+marginより大きいdp値を持つ速度は遷移しない
constexpr int LB_MARGIN = 2000;
// -------------------------------------------------

constexpr int MINV = min(-MX, -MY), MAXV = 2 * V - min(MX, MY);

using TP = int32_t;
const TP dpinf = numeric_limits<TP>::max();
pair<TP, TP> from[MAX_N + 1][2 * V + 1][2 * V + 1];
// dp[i][vx][vy] := i番目の移動を終えたときに座標(vx, vy)にいるときの最小の経過ターン数
TP dp[MAX_N + 1][2 * V + 1][2 * V + 1];
int mindiff[MAX_TURN + 1][MAXV - MINV + 1][MAXV - MINV + 1], maxdiff[MAX_TURN + 1][MAXV - MINV + 1][MAXV - MINV + 1];

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

void solve_dp(vc<pair<int, int>> input)
{
    int N = input.size();
    input.insert(input.begin(), {0, 0});

    // mindiff, maxdiffの前計算
    // mindiff[T][sv][tv] := Tターンかけてsvからtvに移動するときの最小のdiff
    rep(T, MAX_TURN + 1)
    {
        rep(sv, MAXV - MINV + 1) rep(tv, MAXV - MINV + 1)
        {
            mindiff[T][sv][tv] = INF;
            maxdiff[T][sv][tv] = -INF;
        }
    }
    rep(v, MAXV - MINV + 1)
    {
        mindiff[0][v][v] = 0;
        maxdiff[0][v][v] = 0;
    }
    repe(T, 1, MAX_TURN + 1)
    {
        repe(sv, MINV, MAXV + 1) repe(tv, MINV, MAXV + 1)
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
            maxdiff[T][sv - MINV][tv - MINV] = maxsum;

            const int minv = min(sv, tv) - rest / 2;
            int minsum = minv * (rest % 2);
            if (minv < sv)
                minsum += (sv - minv) * (sv + minv - 1) / 2;
            if (minv < tv)
                minsum += (tv - minv) * (tv + 1 + minv) / 2;
            mindiff[T][sv - MINV][tv - MINV] = minsum;
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

    dp[0][MX][MY] = 0;
    from[0][MX][MY] = {-1, -1};
    rep(i, N)
    {
        if (i % 10 == 0)
            err("dp", i, "/", N);

        int lb = dpinf;
        rep(sv, 2 * V + 1) rep(tv, 2 * V + 1)
        {
            if (dp[i][sv][tv] == dpinf)
                continue;
            chmin(lb, dp[i][sv][tv]);
        }
        if (lb == dpinf)
        {
            err("no route: ", i, "/", N);
            return;
        }

        repe(svx, -MX, 2 * V - MX + 1) repe(svy, -MY, 2 * V - MY + 1)
        {
            if (dp[i][svx + MX][svy + MY] == dpinf)
                continue;
            if (dp[i][svx + MX][svy + MY] > lb + LB_MARGIN)
                continue;

            repe(tvx, max(-MX, svx - K), min(2 * V - MX, svx + K) + 1) repe(tvy, max(-MY, svy - K), min(2 * V - MY, svy + K) + 1)
            {

                const pair<int, int> diffs = sub(input[i + 1], input[i]);

                auto check = [&](int turn, int sv, int tv, int diff) -> bool
                {
                    return mindiff[turn][sv - MINV][tv - MINV] <= diff && diff <= maxdiff[turn][sv - MINV][tv - MINV];
                };
                rep(t, MAX_TURN + 1)
                {
                    if (check(t, svx, tvx, diffs.first) && check(t, svy, tvy, diffs.second))
                    {
                        if (chmin(dp[i + 1][tvx + MX][tvy + MY], dp[i][svx + MX][svy + MY] + t))
                        {
                            from[i + 1][tvx + MX][tvy + MY] = {svx, svy};
                        }
                        break;
                    }
                }
            }
        }
    }

    int sc = dpinf, nvx = INF, nvy = INF;
    rep(i, 2 * V + 1) rep(j, 2 * V + 1)
    {
        if (chmin(sc, dp[N][i][j]))
        {
            nvx = i - MX;
            nvy = j - MY;
        }
    }
    assert(nvx != INF and nvy != INF);

    vc<int> ans;
    repr(i, N)
    {
        if (i % 10 == 0)
            err("restore", i, "/", N);
        auto [fvx, fvy] = from[i + 1][nvx + MX][nvy + MY];
        auto t = dp[i + 1][nvx + MX][nvy + MY] - dp[i][fvx + MX][fvy + MY];

        auto diffs = sub(input[i + 1], input[i]);
        assert(mindiff[t][fvx - MINV][nvx - MINV] <= diffs.first && diffs.first <= maxdiff[t][fvx - MINV][nvx - MINV]);
        assert(mindiff[t][fvy - MINV][nvy - MINV] <= diffs.second && diffs.second <= maxdiff[t][fvy - MINV][nvy - MINV]);

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

        auto xs = route(fvx, nvx, diffs.first);
        auto ys = route(fvy, nvy, diffs.second);
        assert(xs.size() == ys.size());

        vc<int> a;
        repr(j, xs.size())
        {
            a.eb(get_diff_idx({xs[j], ys[j]}));
            ans.eb(get_diff_idx({xs[j], ys[j]}));
        }
        err("ip", input[i], input[i + 1]);
        err(a);
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
    cout << res << endl;

    err("route length:", res.size());
}

void run()
{
    vc<pair<int, int>> input;
    int N;
    cin >> N;
    int a, b;
    rep(i, N)
    {
        cin >> a >> b;
        input.eb(a, b);
    }

    // sort(input.begin() + 20, input.end(), [](const pair<ll, ll> &a, const pair<ll, ll> &b) {
    //     return (a.first + a.second == b.first + b.second ? a.first < b.first : a.first + a.second < b.first + b.second);
    // });
    // cout << N << endl;
    // repa(p, input) {
    //     cout << p << endl;
    // }
    // return;

    // solve_greedy(input);
    solve_dp(input);
    // auto ans = get_route(0, 0, 0, 0, 0, 0, 0);
    // err(ans);
}

int main()
{
    startTime = chrono::system_clock::now();
#ifdef TUNE
    // params
#endif
    run();
}