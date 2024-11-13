#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int m, n;
	std::cin >> n >> m;
	std::vector<i64> dp(m + 1);
	std::vector<std::array<int, 3> > e(n);
	i64 sum = 0;
	for (int i = 0; i < n; i ++) {
		std::cin >> e[i][0] >> e[i][1] >> e[i][2];
		sum += e[i][0];
		e[i][1] -= e[i][0];
		for (int j = m; j >= e[i][2]; j --) {
			dp[j] = std::max(dp[j], dp[j - e[i][2]] + e[i][1]);
		}
	}
	i64 ans = dp[m] + sum;
	std::cout << ans * 5 << '\n';
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