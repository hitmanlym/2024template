#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
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
struct Comb {
    int n;
    std::vector<int> _fac, _invfac, _inv;
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    void init(int m) {
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i ++) {
            _fac[i] = 1ll * _fac[i - 1] * i % mod;
        }
        _invfac[m] = qmi(_fac[m], mod - 2);
        for (int i = m; i > n; i --) {
            _invfac[i - 1] = 1ll * _invfac[i] * i % mod;
            _inv[i] = 1ll * _invfac[i] * _fac[i - 1] % mod;
        }
        n = m;
    }
    int fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    int invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    int inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    int binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return 1ll * fac(n) * invfac(m) % mod * invfac(n - m) % mod;
    }
} comb;
void solve() {
	// i -- []
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	// std::set<std::vector<int> > st;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	// n ++;
	// a[n] = 1;
	// i64 res = 0;
	// for (int i = 1; i <= n; i ++) {
	// 	if (a[i] <= 0) continue;
	// 	std::vector<std::array<int, 2> > dp;
	// 	std::vector<int> ans(n + 1);

	// 	dp.push_back({i, 1}); 
	// 	// if (i + a[i] <= n) {
	// 	// 	ans[i + a[i]] = (ans[i + a[i]] + 1) % mod;
	// 	// }

	// 	for (int j = i + 1; j <= n; j ++) {
	// 		if (a[j] <= 0) continue;
	// 		int val = 0;
	// 		for (auto it : dp) {
	// 			int id = it[0], v = it[1];
	// 			if (id + a[id] < j) {
	// 				// std::cout << "!!! :  " << j << ' ' << id << ' ' << v << ' ' << comb.binom(j - id - 1, a[id]) << '\n';
	// 				val = (val + 1ll * v * comb.binom(j - id - 1, a[id]) % mod) % mod;
	// 			} else {
	// 				break;
	// 			}
	// 		}
	// 		std::cout << j - 1 << ' ' << val << '\n';
	// 		if (j == n) res += val;
	// 		// if (val) {
	// 		// 	dp.push_back({j, val});
	// 		// 	if (j + a[j] <= n) {
	// 		// 		ans[j + a[j]] = (ans[j + a[j]] + val) % mod;
	// 		// 	}
	// 		// }
	// 	}
	// 	// std::cout << '\n';
	// 	// for (int j = i + 1; j <= n; j ++) {
	// 	// 	// std::cout << ans[j] << ' ';
	// 	// 	res = (res + ans[j]) % mod;
	// 	// }
	// 	std::cout << '\n';
	// 	// std::cout << res << '\n';
	// }
	// std::cout << res << '\n';

	std::vector<std::vector<int> > dp(n + 1, std::vector<int>(n + 1));
	for (int i = 1; i <= n; i ++) {
		if (a[i] > 0 && a[i] < n) {
			dp[i][a[i]] = (dp[i][a[i]] + dp[i - 1][0] + 1) % mod;
		}
		for (int j = 0; j <= n; j ++) {
			dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % mod;
			dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
		}
	}
	std::cout << dp[n][0] << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}