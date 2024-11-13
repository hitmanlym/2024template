#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::vector<int> > e(n + 1);
	for (int i = 1; i < n; i ++) {
		int id;
		std::cin >> id;
		id ++;
		int x;
		std::cin >> x;
		while (x --) {
			int y;
			std::cin >> y;
			y ++;
			e[id].push_back(y);
			e[y].push_back(id);
		}
	}
	std::vector<std::array<int, 2> > dp(n + 1);
	int rt = 1;
	auto dfs = [&](auto self, int u, int p) -> void {
		dp[u][1] = 1;
		for (auto v : e[u]) {
			if (v == p) continue;
			self(self, v, u);
			dp[u][1] += std::min(dp[v][0], dp[v][1]);
			dp[u][0] += dp[v][1];
		}
	};
	dfs(dfs, rt, 0);
	std::cout << std::min(dp[rt][0], dp[rt][1]) << '\n';
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