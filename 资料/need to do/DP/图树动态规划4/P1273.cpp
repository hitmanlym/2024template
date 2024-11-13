#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<std::array<int, 2> > > e(n + 1);
	for (int i = 1; i <= n - m; i ++) {
		int x;
		std::cin >> x;
		while (x --) {
			int a, c;
			std::cin >> a >> c;
			e[i].push_back({a, c});
		}
	}
	std::vector<int> pay(n + 1);
	for (int i = n - m + 1; i <= n; i ++) {
		std::cin >> pay[i];
	}
	const int N = n * 10;
	std::vector<std::vector<int> > dp(n + 1, std::vector<int>(n + 1, -1e18));
	for (int i = 1; i <= n; i ++) {
		dp[i][0] = 0;
	}
	auto dfs = [&](auto self, int u) -> int {
		if (pay[u]) {
			dp[u][1] = pay[u];
			return 1;
		}
		int siz = 0;
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			int op = self(self, v);
			siz += op;
			for (int i = siz; i > 0; i --) {
				for (int j = 1; j <= std::min(i, op); j ++) {
					dp[u][i] = std::max({
						dp[u][i],
						dp[u][i - j] + dp[v][j] - w
					});
				}
			}
		}
		return siz;
	};
	dfs(dfs, 1);
	int ans = 0;
	for (int i = 1; i <= n; i ++) {
		if (dp[1][i] >= 0) {
			ans = i;
		}
	}
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