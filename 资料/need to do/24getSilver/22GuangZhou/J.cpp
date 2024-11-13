#include<bits/stdc++.h>
using i64 = long long;
#define int i64

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
	int n, m;
	std::cin >> n >> m;
	int lim = (m + 1) / 2;
	std::vector<std::vector<int> > dp(n + 1, std::vector<int>(lim + 1));
	dp[0][0] = 1;
	for (int i = 1; i <= n; i ++) {
		for (int j = 0; j <= lim; j ++) {
			if (j != lim) {
				dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % mod;
			}
			if (j != 0) {
				dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % mod;
			}
		}
	} 
	int ans = 0;
	for (int i = 0; i <= lim; i ++) {
		std::cout << i << ' ' << dp[n][i] << '\n';
		ans = (ans + dp[n][i]) % mod;
	}
	std::cout << ans << '\n';



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