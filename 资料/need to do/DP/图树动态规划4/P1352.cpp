#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), in(n + 1);
	std::vector<std::vector<int> > e(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		in[u] ++;
		e[v].push_back(u);
	}
	int rt;
	for (int i = 1; i <= n; i ++) {
		if (in[i] == 0) rt = i;
	}
	std::vector<std::array<int, 2> > dp(n + 1); 
	auto dfs = [&](auto self, int u) -> void {
		dp[u][1] = a[u];
		for (auto v : e[u]) {
			self(self, v);
			dp[u][0] += std::max(dp[v][0], dp[v][1]);
			dp[u][1] += dp[v][0];
		}
	};
	dfs(dfs, rt);
	int ans = std::max(dp[rt][0], dp[rt][1]);
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