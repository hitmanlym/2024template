#include<bits/stdc++.h>
using i64 = long long;

const int inf = 1e9;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> dp(n + 1);
	int ans = - inf;
	for (int i = 1; i <= n; i ++) {
		std::cin >> dp[i];
		int u = dp[i - 1] + dp[i];
		if (u >= dp[i]) {
			dp[i] = u;
		}
		ans = std::max(ans, dp[i]);
	}
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