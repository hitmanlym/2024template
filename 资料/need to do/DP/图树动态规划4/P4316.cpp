#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<std::array<int, 2> > > e(n + 1);
	for (int i = 1; i <= m; i ++) {
		int u, v, d;
		std::cin >> u >> v >> d;
		e[u].push_back({v, d});
	}
	std::vector<double> dp(n + 1);
	auto dfs = [&](auto self, int u) -> int {
		double res = 0;
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			self(self, v);
			res += dp[v] + w;
		}
		if (! e[u].size()) {
			return 0;
		}
		dp[u] = res / e[u].size();
		return dp[u];
	};
	dfs(dfs, 1);
	printf("%.2lf\n", dp[1]);
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