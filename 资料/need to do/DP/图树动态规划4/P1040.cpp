#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 2);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	std::vector<std::vector<int> > dp(n + 2, std::vector<int>(n + 2, 0));
	for (int i = 1; i <= n; i ++) {
		dp[i][i] = a[i];
	}
	for (int i = 1; i <= n + 1; i ++) {
		for (int j = 1; j <= n + 1; j ++) {
			if (i > j) dp[i][j] = 1;
		}
	}
	for (int len = 2; len <= n; len ++) {
		for (int l = 1, r; r = l + len - 1, r <= n; l ++) {
			for (int k = l; k <= r; k ++) {
				dp[l][r] = std::max(dp[l][r], dp[l][k - 1] * dp[k + 1][r] + a[k]);
			}

		}
	}
	int ans = dp[1][n];
	std::cout << ans << '\n';
	auto dfs = [&](auto self, int l, int r) {
		if (l > r) return ;
		if (l == r) {
			std::cout << l << ' ';
			return ;
		}
		for (int i = l; i <= r; i ++) {
			if (dp[l][r] == dp[l][i - 1] * dp[i + 1][r] + a[i]) {
				std::cout << i << ' ';
				self(self, l, i - 1);
				self(self, i + 1, r);
				break;
			}
		}
	};
	dfs(dfs, 1, n);
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