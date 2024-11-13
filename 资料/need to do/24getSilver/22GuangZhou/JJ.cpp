#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
// #define int i64
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
	int ans = 0;
	int l = 1, r = lim + 1;
	for (int i = (n + 1) / 2; i <= (n + lim) / 2; i ++) {
		int j = n - i;
		int now = comb.binom(n, j);

		if (j >= l) {
			now = ((now - comb.binom(n, j - l)) % mod + mod) % mod;
            int idx = 1 + r, idy = -1 - r;
            if (idx <= i) {
                now = (now + comb.binom(std::abs(i - idx) + std::abs(j - idy), i - idx)) % mod;
            }
		}
		if (i >= r) {
			now = ((now - comb.binom(n, i - r)) % mod + mod) % mod;
            int idx = -r - 1, idy = r + 1;
            if (idy <= j) { // 减一遍就好
                // now = (now + comb.binom(std::abs(i - idx) + std::abs(j - idy), j - idy)) % mod;
            }
		}
        // if (i >= op) {
        //     now = ((now + comb.binom(n, i - op)) % mod + mod) % mod;
        // }
        // int op = i - r;
        // if (op >= l) { // -1 1 
        //     int y = i - r, x = j + r;
        //     std::cout << "??? " << n << ' ' << std::abs(x + 1) << ' ' << std::abs(y - 1) << '\n';
        //     std::cout << op << ' ' << l << ' ' << comb.binom(n, op - l) << '\n';
        //     now = ((now + comb.binom(n, op - l)) % mod + mod) % mod;
        // }
		std::cout << i << ' ' << i - j << ' ' << now << '\n';
		ans = (ans + now) % mod;
	}
	std::cout << ans << '\n';

    // std::cout << comb.binom(8, 4) - comb.binom(8, 2)
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