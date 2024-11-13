#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int> > dp(1 << n, std::vector<int>(n));
	std::vector<std::vector<int> > e(n);
	for (int i = 0; i < m; i ++) {
		int u, v;
		std::cin >> u >> v;
		u --, v --;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 0; i < n; i ++) {
		dp[1 << i][i] = 1; // st; endpoint
	}
	int ans = 0;
	for (int i = 1; i < (1 << n); i ++) {
		for (int j = 0; j < n; j ++) {
			if (! dp[i][j]) continue;
			// j-v
			for (auto v : e[j]) {
				if ((1 << v) < (i & -i)) continue;
				if (i >> v & 1) {
					// only this
					if ((1 << v) == (i & -i)) {
						ans += dp[i][j];
					}
				} else {
					dp[i | (1 << v)][v] += dp[i][j];
				}
			}
		}
	}
	int res = (ans - m) / 2; // a - b - a repeat
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