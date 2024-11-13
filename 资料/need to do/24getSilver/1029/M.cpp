#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
const int inf = 1e18;
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::vector<int> > e(n + 1);
	for (int i = 2; i <= n; i ++) {
		int p;
		std::cin >> p;
		e[p].push_back(i);
	}
	std::vector<int> a(n + 1), siz(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	std::vector<std::vector<pii> > dp(n + 1, std::vector<pii>(n + 1, (pii){inf, inf}));
	std::vector<pii> g(n + 1);
	auto dfs = [&](auto self, int u) -> void {
		dp[u][0][0] = a[u];
		dp[u][1][1] = 0;
		siz[u] = 1;
		for (auto v : e[u]) {
			self(self, v);
			for (int i = 0; i <= siz[u] + siz[v]; i ++) {
				g[i] = {inf, inf};
			}
			for (int i = 0; i <= siz[u]; i ++) {
				for (int j = 0; j <= siz[v]; j ++) {
					g[i + j][0] = std::min({g[i + j][0], dp[u][i][0] + dp[v][j][0] + a[v], dp[u][i][0] + dp[v][j][1]});
					g[i + j][1] = std::min({g[i + j][1], dp[u][i][1] + dp[v][j][0], dp[u][i][1] + dp[v][j][1]});
				}
			}
			for (int i = 0; i <= siz[u] + siz[v]; i ++) {
				dp[u][i] = g[i];
			}
			siz[u] += siz[v];
		}
	};
	dfs(dfs, 1);
	for (int i = 0; i <= n; i ++) {
		std::cout << std::min(dp[1][i][0], dp[1][i][1]) << ' ';
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