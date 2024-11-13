#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}

	std::vector<std::vector<int> > e(n + 1);
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	std::vector<int> dp(n + 1);
	int ans = -1e18;
	auto dfs = [&](auto self, int u, int p) -> void {
		dp[u] = a[u];
		for (auto v : e[u]) {
			if (v == p) continue;
			self(self, v, u);
			dp[u] = std::max(dp[u], dp[u] + dp[v]);
		}
		ans = std::max(ans, dp[u]);
	};
	dfs(dfs, 1, 0);
	std::cout << ans << '\n';
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