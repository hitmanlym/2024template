#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
const int inf = 1e17;
void solve() {
	int n;
	std::cin >> n;
	std::string s;
	std::cin >> s;
	std::vector<pii> dp(n, {inf, inf});
	dp[0][0] = 0;
	dp[0][1] = 1;
	for (int i = 1; i < n; i ++) {
		if (s[i - 1] == '1') {
			dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][1]) + 1;
			dp[i][0] = dp[i - 1][1];
		} else {
			dp[i][0] = std::min(dp[i - 1][0], dp[i - 1][1]);
			dp[i][1] = dp[i - 1][1] + 1;
		}
	}
	std::cout << std::min(dp[n - 1][0], dp[n - 1][1]) << '\n';
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