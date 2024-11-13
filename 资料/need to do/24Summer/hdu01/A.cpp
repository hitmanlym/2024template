#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;
#define int i64
const int inf = 1e18 + 7;
const int mod = 1e9 + 7; //4179340454199820289
int qmi(int a, int b) {
    if (a == 0) return 0;
    int res = 1;
    while (b) {
        if (b & 1) {
            res = 1ll * res * a % mod;
        }
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}
const int p = 133333, q = 13333;
void solve() {
	std::string s, t;
	std::cin >> s >> t;
	int n = s.size(), m = t.size();
	s = " " + s;
	int mn = std::max(n, m);
	std::vector<int> x(mn + 1), y(mn + 1), z(mn + 1), inv(mn + 1), xx(mn + 1), yy(mn + 1), zz(mn + 1), I(mn + 1);
	x[0] = 1;
	for (int i = 1; i <= mn; i ++) {
		x[i] = x[i - 1] * p % mod;
		xx[i] = xx[i - 1] * q % mod;
	}
	inv[mn] = qmi(x[mn], mod - 2);
	//inv[0] = 1;
	I[mn] = qmi(xx[mn], mod - 2);
	//I[0] = 1;
	for (int i = mn - 1; i >= 0; i --) {
		inv[i] = inv[i + 1] * p % mod;
		I[i] = I[i + 1] * p % mod;
	}
	std::set<std::array<int, 2> > st;
	for (int i = 1; i <= n; i ++) {
		y[i] = (y[i - 1] + s[i] * x[i]) % mod;
		yy[i] = (yy[i - 1] + s[i] * xx[i]) % mod;
	}
	st.insert({y[n], yy[n]});
	for (int i = 2; i <= n; i ++) {
		int op = ((y[n] - y[i - 1] + mod) % mod) * inv[i - 1] % mod + y[i - 1] * x[n + 1 - i] % mod;
		op %= mod;

		int opp = ((yy[n] - yy[i - 1] + mod) % mod) * I[i - 1] % mod + yy[i - 1] * xx[n + 1 - i] % mod;
		opp %= mod;
		st.insert({op, opp});
	}
	t = " " + t;
	int num = 0;
	for (int i = 1; i <= m; i ++) {
		z[i] = (z[i - 1] + t[i] * x[i]) % mod;
		zz[i] = (zz[i - 1] + t[i] * xx[i]) % mod;
		if (i >= n) {
			int op = (z[i] - z[i - n] + mod) % mod * inv[i - n] % mod;
			int opp = (zz[i] - zz[i - n] + mod) % mod * I[i - n] % mod;
			//std::cout << "!! " << i << ' ' << op << '\n';
			if (st.count({op, opp})) num ++;
		}
	}
	std::cout << num << '\n';
}
signed main() { 
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}