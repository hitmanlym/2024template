#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::vector<std::vector<int> > dp(n + 1, std::vector<int>(n + 1));
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= i; j ++) {
			std::cin >> dp[i][j];
			dp[i][j] += std::max(dp[i - 1][j - 1], dp[i - 1][j]);
		}
	}
	int max = 0;
	for (int i = 1; i <= n; i ++) {
		max = std::max(max, dp[n][i]);
	}
	std::cout << max << '\n';
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