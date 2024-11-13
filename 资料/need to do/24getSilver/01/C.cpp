#include<bits/stdc++.h>
using i64 = long long;
// #define int i64
const int mod = 998244353;
int inv(int a) {
	int res = 1, b = mod - 2;
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
	int n;
	std::cin >> n;
	std::vector<int> fac(n + 1);
	fac[0] = 1;
	for (int i = 1; i <= n; i ++) {
		fac[i] = 1ll * fac[i - 1] * i % mod;
	}
	std::vector<std::vector<int> > e(n + 1);
	e[1].push_back(0);
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	std::vector<int> siz(n + 1), inner(n + 1, 1), pick(n + 1);
	auto dfs1 = [&](auto self, int u, int p) -> void {
		siz[u] = 1;
		for (auto v : e[u]) {
			if (v == p) continue;
			self(self, v, u);
			siz[u] += siz[v];
			inner[u] = 1ll * inner[u] * inner[v] % mod;
		}
		pick[u] = inner[u];
		inner[u] = 1ll * inner[u] * fac[e[u].size() - 1] % mod;
	};
	dfs1(dfs1, 1, 0);
	std::vector<std::vector<int> > ans(n + 1, std::vector<int>(n + 1));
	std::vector<std::vector<int> > dp(n + 2, std::vector<int>(n + 2));
	dp[0][1] = 1;
	std::vector<int> invv(n + 1);
	for (int i = 1; i <= n; i ++) {
		invv[i] = inv(inner[i]);
	}
	auto dfs = [&](auto self, int u, int p) -> void {
		auto roback = dp;
		for (int i = 0; i <= n; i ++) {
			for (int j = n; j >= 1; j --) {
				dp[i][j] = dp[i][j - 1];
			}
		}
		int o = pick[u];
		std::vector<int> son;
		for (auto v : e[u]) {
			if (v == p) continue;
			for (int i = n; i >= 1; i --) {
				for (int j = n; j >= siz[v]; j --) {
					if (dp[i - 1][j - siz[v]]) {
						dp[i][j] += dp[i - 1][j - siz[v]];
						if (dp[i][j] >= mod) {
							dp[i][j] -= mod;
						}
					}
				}
			}
		}
		for (auto v : e[u]) {
			if (v == p) continue;
			for (int i = 1; i <= n; i ++) {
				for (int j = n; j >= siz[v]; j --) {
					if (dp[i - 1][j - siz[v]]) {
						dp[i][j] -= dp[i - 1][j - siz[v]];
						if (dp[i][j] < 0) dp[i][j] += mod;
					}
				}
			}
			for (int i = 0; i <= n; i ++) {
				for (int j = 0; j <= n; j ++) {
					if (dp[j][i]) {
						int oop = (int)e[u].size() - 1 - 1 - j;
						if (oop < 0) oop = 0;
						ans[v][i] = (ans[v][i] + 1ll * dp[j][i] * o % mod * fac[j] % mod * fac[oop] % mod) % mod;
					}
				}
			}
			auto op = dp;
			for (int j = 0; j <= n; j ++) {
				int oop = (int)e[u].size() - 1 - 1;
				if (oop < 0) oop = 0;
				dp[0][j] = 1ll * dp[0][j] * o % mod * invv[v] % mod * fac[oop] % mod;
			}
			for (int i = 1; i <= n; i ++) {
				for (int j = 0; j <= n; j ++) {
					int oop = (int)e[u].size() - 1 - 1 - i;
					if (oop < 0) oop = 0;
					dp[0][j] = (1ll * dp[i][j] * o % mod * invv[v] % mod * fac[i] % mod * fac[oop] % mod + dp[0][j]) % mod;
					dp[i][j] = 0;
				}
			}
			self(self, v, u);
			dp = op;
			for (int i = n; i >= 1; i --) {
				for (int j = n; j >= siz[v]; j --) {
					if (dp[i - 1][j - siz[v]]) {
						dp[i][j] += dp[i - 1][j - siz[v]];
						if (dp[i][j] >= mod) {
							dp[i][j] -= mod;
						}
					}
				}
			}
		}
		dp = roback;
	};
	dfs(dfs, 1, 0);
	ans[1][1] = inner[1];
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			std::cout << (ans[i][j] + mod) % mod << ' ';
		}
		std::cout << '\n';
	}
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