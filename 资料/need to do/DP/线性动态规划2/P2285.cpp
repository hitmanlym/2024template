#include<bits/stdc++.h>
using i64 = long long;

const int mod = 1e6 + 7;

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::array<int, 3> > a(m + 1);
	for (int i = 1; i <= m; i ++) {
		std::cin >> a[i][2] >> a[i][0] >> a[i][1];
	}
	std::vector<int> dp(m + 1);
	auto dist = [&](int x, int y) -> int {
		return std::abs(a[x][0] - a[y][0]) + std::abs(a[x][1] - a[y][1]);
	};
	for (int i = 1; i <= m; i ++) {
		dp[i] = 1;
		for (int j = 1; j < i; j ++) {
			if (dist(i, j) <= a[i][2] - a[j][2]) {
				dp[i] = std::max(dp[i], dp[j] + 1);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= m; i ++) {
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