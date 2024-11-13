#include<bits/stdc++.h>
using i64 = long long;

const int mod = 1e6 + 7;
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::array<int, 2> > e(n + 1), dp(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> e[i][0] >> e[i][1];
	}

	dp[1][0] = e[1][1] - 1 + e[1][1] - e[1][0];
	dp[1][1] = e[1][1] - 1;
	for (int i = 2; i <= n; i ++) {
		dp[i][0] = std::min(dp[i - 1][0] + std::abs(e[i][1] - e[i - 1][0]) + e[i][1] - e[i][0],
			dp[i - 1][1] + std::abs(e[i][1] - e[i - 1][1]) + e[i][1] - e[i][0]) + 1;
		dp[i][1] = std::min(dp[i - 1][0] + std::abs(e[i][0] - e[i - 1][0]) + e[i][1] - e[i][0],
			dp[i - 1][1] + std::abs(e[i][0] - e[i - 1][1]) + e[i][1] - e[i][0]) + 1;
	}
	int ans = std::min(dp[n][0] + n - e[n][0], dp[n][1] + n - e[n][1]);
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