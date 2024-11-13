#include<bits/stdc++.h>
using i64 = long long;
#define int i64
int a[18], d[1024];
i64 b[1024];
i64 f[18][1024];
const int mod = 1e9 + 7;
int M = 1024;
i64 dfs(int len, bool limit, bool zero, int sum, int mm) {
	// std::cout << len << ' ' << mm << ' ' << sum << '\n'; 
	// if (sum + 9 * len < mm) return 0;
	if (! len) return sum == mm && ! zero;
	if (! limit && ! zero && f[len][sum] != -1) {
		return f[len][sum];
	}
	i64 res = 0;
	int end = limit ? a[len] : 9;
	for (int i = 0; i <= end; i ++) {
		if (i == 1 || i == 2 || i == 4) continue;
		res += dfs(len - 1, limit && i == end, zero && i == 0,
			(i || ! zero) ? (sum * 10 + i) % M : sum,
			mm);
		// if (res >= mod) {
		// 	d[mm] = 1;
		// 	res -= mod;
		// }
		res %= mod;
	}
	if (! limit && ! zero) f[len][sum] = res;
	return res;
}
void dp(i64 n) {
	int len = 0;
	while (n) {
		a[++ len] = n % 10;
		n /= 10;
	}
	for (int i = 0; i < 1024; i ++) {
		memset(f, -1, sizeof f);
		b[i] = dfs(len, 1, 1, 0, i) % mod;
	}
}
int qmi(int a, int b = mod - 2) {
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
void solve() {
	int n, m;
	std::cin >> n >> m;
	dp(n);
	// for (int i = 0; i <= 100; i ++) {
	// 	std::cout << b[i] << ' ';
	// }
	// std::cout << '\n';
	std::map<i64, bool> mp;
	int ans = 0;
	for (int i = 0; i < 1024; i ++) {
		for (int j = 0; j < 1024; j ++) {
			int k = ((m - i - j) % 1024 + 1024) % 1024;
			std::vector<int> c(3);
			c[0] = i, c[1] = j, c[2] = k;
			std::sort(c.begin(), c.end());
			i64 OP = (1ll * c[0] * 100000ll + c[1]) * 100000ll + c[2];
			if (mp.count(OP)) {
				continue;
			}
			// int ori = ans;
			mp[OP] = 1;
			if (c[0] == c[1] && c[0] == c[2]) {
				// if (b[c[0]] < 3 && d[c[0]]) {
				// 	b[c[0]] += mod;
				// }
				// if (b[c[0]] >= 3)
				ans = (ans + 1ll * b[c[0]] * (b[c[0]] - 1) % mod * (b[c[0]] - 2) % mod * qmi(6) % mod) % mod;
			} else if (c[0] == c[1] && c[1] != c[2]) {
				// if (b[c[1]] < 2 && d[c[1]]) {
				// 	b[c[1]] += mod;
				// }
				// if (b[c[1]] >= 2)
				ans = (ans + 1ll * b[c[1]] * (b[c[1]] - 1) % mod * qmi(2) % mod * b[c[2]] % mod) % mod;
			} else if (c[1] == c[2] && c[1] != c[0]) {
				// if (b[c[1]] < 2 && d[c[1]]) {
				// 	b[c[1]] += mod;
				// }
				// if (b[c[1]] >= 2)
				ans = (ans + 1ll * b[c[1]] * (b[c[1]] - 1) % mod * qmi(2) % mod * b[c[0]] % mod) % mod;
			} else {
				// std::cout << "??? " << c[0] << ' ' << c[1] << ' ' << c[2] << '\n';
				ans = (ans + 1ll * b[c[0]] * b[c[1]] % mod * b[c[2]] % mod) % mod;
			}
			// if (ans != ori)
			// std::cout << i << ' ' << j << ' ' << k << ' ' << ans << '\n';
		}
	}
	std::cout << (ans + mod) % mod << '\n';
}
// 15 10 
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