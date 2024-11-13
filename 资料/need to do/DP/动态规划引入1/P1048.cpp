#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int m, n;
	std::cin >> m >> n;
	std::vector<int> dp(m + 1);
	for (int i = 1; i <= n; i ++) {
		int u, v;
		std::cin >> u >> v;
		for (int j = m; j >= u; j --) {
			dp[j] = std::max(dp[j], dp[j - u] + v);
		}
	}
	std::cout << dp[m] << '\n';
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