#include<iostream>
#include<vector>
#include<array>
using i64 = long long;

const int mod = 1e9 + 7;
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
	int n;
	std::cin >> n;
	std::vector<std::array<int, 2> > a(n + 1), dp(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i][0] >> a[i][1];
	}
	dp[0] = {1, 1};
	int ans = 1;
	for (int i = 1; i <= n; i ++) {
		for (int j = 0; j < 2; j ++) {
			if (! a[i][j]) {
				dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
			} else {
                a[i][j] --;
				int res = comb.binom(a[i][0] + a[i][1] + 2, a[i][j ^ 1] + 1) - 1;
                res = 1ll * res * dp[i - 1][j] % mod;
				ans = (ans + res) % mod;

				for (int k = 0; k < 2; k ++) {
                    dp[i][k] += 1ll * dp[i - 1][j] * comb.binom(a[i][0] + a[i][1] + 1, a[i][k] + 1) % mod;
                    dp[i][k] %= mod;
                }
                a[i][j] ++;
			}
		}
	}
	std::cout << (ans + mod) % mod << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}