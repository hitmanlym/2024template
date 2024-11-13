#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n, q;
	std::cin >> n >> q;
	n ++;
	std::vector<std::vector<std::array<int, 2> > > e(n + 1);
	for (int i = 1; i < n; i ++) {
		int u, w;
		std::cin >> u >> w;
		u ++;
		e[u].push_back({i + 1, w});
	}
	std::vector<std::vector<int> > dp(n + 1, std::vector<int>(q + 1));
	auto dfs = [&](auto self, int u, int p) -> void {
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			if (v == p) continue;

			self(self, v, u);
			for (int i = q; i >= 1; i --) {
				dp[u][i] = std::max(dp[u][i], dp[v][i - 1] + w);
				for (int j = i - 1; j >= 0; j --) {
					dp[u][i] = std::max(dp[u][i], dp[u][i - 1 - j] + dp[v][j] + w);
				}
			}
		}
	};
	dfs(dfs, 1, 0);
	int ans = dp[1][q];
	std::cout << ans << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}