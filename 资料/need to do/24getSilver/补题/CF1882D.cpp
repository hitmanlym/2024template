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
	std::vector<int> dp(n + 1), ans(n + 1), siz(n + 1);
	auto dfs1 = [&](auto self, int u, int p) -> void {
		siz[u] = 1;
		for (auto v : e[u]) {
			if (v == p) continue;
			self(self, v, u);
			siz[u] += siz[v];
			dp[u] += dp[v] + siz[v] * (a[u] ^ a[v]);
		}
		ans[u] = dp[u];
	};
	auto dfs2 = [&](auto self, int u, int p) -> void {
		for (auto v : e[u]) {
			if (v == p) continue;
			ans[v] += ans[u] - dp[v] + (n - 2 * siz[v]) * (a[u] ^ a[v]);
			self(self, v, u);
		}
	};
	dfs1(dfs1, 1, 0);
	dfs2(dfs2, 1, 0);
	for (int i = 1; i <= n; i ++) {
		std::cout << ans[i] << ' ';
	}
	std::cout << '\n';
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