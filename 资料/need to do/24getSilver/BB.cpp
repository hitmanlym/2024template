#include<bits/stdc++.h>
using i64 = long long;
// #define int i64
const i64 inf = 1e18;
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	int B = std::sqrt(n);
	i64 ans = -inf;
	if (k <= B) {
		std::vector<std::vector<i64> > dp(n + 1, std::vector<i64>(k + 1));
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j < k; j ++) {
				dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][(j + k - 1) % k]);
			}
			if (i >= k) dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][k - 1]) + a[i];
		}
		for (int i = 0; i < k; i ++) {
			ans = std::max(ans, dp[n][i]);
		}
	} else {
	// // 	// 我是第几段的
		std::vector<std::vector<i64> > dp(n + 1, std::vector<i64>(B + 1, -inf));
		std::vector<i64> premax(B + 1, -inf);
		dp[0][0] = 0;
		premax[0] = 0;
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= std::min(i / (k - 1) + 1, B); j ++) {
				dp[i][j] = std::max(dp[i - 1][j] + a[i], dp[i][j]);
				if (i - k >= 0) {
					premax[j] = std::max(premax[j], dp[i - k][j]);
					dp[i][j] = std::max({dp[i][j], premax[j - 1] + a[i], 0ll});
				}
				ans = std::max(ans, dp[i][j]);
			}
		}
	}
	if (k > 1) {
		ans = std::max(ans, 0ll);
	}
	std::cout << ans << '\n';
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