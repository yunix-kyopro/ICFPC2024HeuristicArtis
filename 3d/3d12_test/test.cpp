#include <iostream>
#include <algorithm>
#include <bitset>
#include <map>
#include <queue>
#include <deque>
#include <set>
#include <stack>
#include <string>
#include <cstring>
#include <utility>
#include <vector>
#include <complex>
#include <valarray>
#include <fstream>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <time.h>
#include <atcoder/dsu.hpp>

#define InfL 2000000000
#define InfLL 4000000000000000000LL
#define mod 1000000007
#define rep(i,n) for(int i=0;i<n;i++)
#define rrep(i,n) for(int i=(n-1);i>=0;i--)
using namespace std;
typedef long long ll;
typedef double db;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<db> vd;

bool debug = true; // false : 提出, true : fin - fout
double time_ratio = 1.0;
string file_No = "0000";
ifstream fin;
ofstream fout;
ofstream fout_debug;
ofstream fout_score;
int Gaussian_size = 1000000;
vector<double> Gaussian_(Gaussian_size);
struct timespec timeini;

const vi dx = { -1, 1, 0, 0 };
const vi dy = { 0, 0, -1, 1 };

const vector<vi> dxy_to_d = { {1,4,7},{2,5,8},{3,6,9} };


// turnでdiffだけ変化して始端速度(svx,svy)から終端速度(tvx,tvy)に変化するときの経路
// 経路が必ず存在すると仮定
string get_route(int turn, int svx, int svy, int tvx, int tvy, int diffx, int diffy) {
	auto route = [&](int sv, int tv, int diff) -> vector<int> {
		cout << "a" << endl;
		vector<int> ret;

		vector<int> order;
		{
			int u = (tv > sv) ? 1 : -1;
			for (int k = 0; k < abs(tv - sv) + 1; k++) order.emplace_back(sv + k * u);
			for (int k = 0; k < turn - abs(tv - sv); k++) order.emplace_back(tv);
		}
		cout << "A" << endl;
		int M = order.size();
		cout << "B" << endl;
		int now = accumulate(order.begin() + 1, order.end(), 0);
		cout << "C" << endl;
		int rest = diff - now;
		cout << "D" << endl;
		while (rest != 0) {
			for (int i = 1; i < M - 1; i++) {
				cout << i << endl;
				if (rest > 0) {
					if (order[i - 1] >= order[i] && order[i] <= order[i + 1]) {
						order[i]++;
						rest--;
					}
				}
				else if (rest < 0) {
					if (order[i - 1] <= order[i] && order[i] >= order[i + 1]) {
						order[i]--;
						rest++;
					}
				}
				if (rest == 0) break;
			}
			if (rest == 0) break;
		}
		cout << "B" << endl;

		for (int i = 0; i < M - 1; i++) {
			ret.emplace_back(order[i + 1] - order[i]);
		}

		return ret;
		};

	auto xs = route(svx, tvx, diffx);
	auto ys = route(svy, tvy, diffy);
	assert(xs.size() == ys.size());

	string ret;
	for (int j = (int)xs.size() - 1; j >= 0; j--) {
		ret += to_string((xs[j] + 1) + 1 + (ys[j] + 1) * 3);
	}

	return ret;
}


ll N = 1047;
ll M = 1000;
ll K = 1000000;

ll f(ll v) {
	ll ans = v;
	for (int k = 10; k >= 1; k--) {
		ans *= N;
		ans *= N;
		ans /= M;
		ans /= M;
		ans /= (ll)(k * 2);
		ans /= (ll)(k * 2 + 1);
		ans = K - ans;
		cout << ans << endl;
	}
	ans *= N;
	ans /= K;
	return ans;
}

int main(int argc, char* argv[]) {
	cout << f(K) << endl;


	return 0;
}
