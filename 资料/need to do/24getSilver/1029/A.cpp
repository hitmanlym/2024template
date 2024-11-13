#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::vector<int> > e(n + 1);
	for (int i = 1; i <= n; i ++) {
		int p;
		std::cin >> p;
		e[p].push_back(i);
	} 
	std::vector<int> dp(n + 1, 0);
	auto dfs = [&](auto self, int u) -> void {
		std::array<int, 2> max = {-1, -1};
		for (int i = 0; i < e[u].size(); i ++) {
			int v = e[u][i];
			self(self, v);
			if (dp[v] > max[0]) {
				max[1] = max[0];
				max[0] = dp[v];
			} else if (dp[v] > max[1]) {
				max[1] = dp[v];
			}
		}
		if (max[0] == 0 && max[1] == -1) {
			dp[u] = 0;
		} else {
			if (max[0] == max[1]) {
				dp[u] = max[0] + 1;
			} else {
				dp[u] = max[0];
			}	
		}
	};
	dfs(dfs, 0);
	std::cout << dp[0] + 1 << '\n';
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