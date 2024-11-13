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
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), num(n + 1), cnt(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		cnt[a[i]] ++;
	}
	num[0] = cnt[0];
	for (int i = 1; i <= n; i ++) {
		num[i] = std::min(cnt[i], num[i - 1]);
	}
	std::set<int> st;
	for (int i = 0; i < n; i ++) {
		st.insert(cnt[i]);
	}
	std::vector<int> ddp(n + 2, 1) , pw(n + 1), pre(n + 1);
	// 想出了一种很妙的，时间不够了艹，等会儿交
	std::vector<int> rev(n + 1);
	std::vector<std::vector<int> > hav(st.size());
	int op = 0;
	for (auto it : st) {
		rev[it] = op;
		hav[op].assign(it + 2, 0);
		for (int i = it; i >= 1; i --) {
			hav[op][i] = (hav[op][i + 1] + comb.binom(it, i)) % mod;
		}
		op ++;
	}
	pw[0] = 1;
	for (int i = 1; i <= n; i ++) {
		pw[i] = pw[i - 1] * 2 % mod;
	}
	int ans = 0;
	for (int i = 1; i <= n; i ++) { // mex = i;
		pre[i] = pre[i - 1] + cnt[i - 1];
		// num[i] 组
		// std::cout << "!!! " << num[i - 1] << '\n';
		ddp[num[i - 1] + 1] = 0;
		for (int j = num[i - 1]; j >= 1; j --) { // 恰好 j 组的数量
			// ....
			// .... C(cnt[0], j) * C(cnt[1], j) ... * C(cnt[i - 1], j)
			ddp[j] = ddp[j] * hav[rev[cnt[i - 1]]][j] % mod;
			int it = (ddp[j] - ddp[j + 1] + mod) % mod;
			// std::cout << it << ' ' << "??? " << ddp[j] << ' ' << ddp[j + 1] << '\n';
			it = it * pw[n - pre[i]] % mod;
			ans = (ans + it * j % mod) % mod;

			// std::cout << j << ' ' << ddp[j] << ' ' << it << '\n'; 
		}
		// std::cout << ans << '\n';
	}
	std::cout << ans << '\n';
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