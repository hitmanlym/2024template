#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	int total = 0;
	std::vector<std::vector<std::array<int, 2>> > e(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		total += a[i];
	}

	for (int i = 1; i < n; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}

	std::vector<int> sz(n + 1);
	std::vector<int> dp(n + 1);
	auto pre = [&](auto self, int u, int p) -> void {
		sz[u] = a[u];
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			if (v == p) continue;
			self(self, v, u);
			sz[u] += sz[v];
			dp[u] += dp[v] + sz[v] * w;
		}
	};
	pre(pre, 1, 0);
	std::vector<int> ans(n + 1);
	ans[1] = dp[1];

	auto dfs = [&](auto self, int u, int p) -> void {
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			if (v == p) continue;
			ans[v] = ans[u] - sz[v] * w + (total - sz[v]) * w;
			self(self, v, u);
		}
	};
	dfs(dfs, 1, 0);

	int res = 1e18;
	for (int i = 1; i <= n; i ++) {
		res = std::min(res, ans[i]);
	}
	std::cout << res << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}