#include<bits/stdc++.h>
using i64 = long long;
const int inf = 1e9 + 7;
void solve() {
	int n, m, k;
	std::cin >> n >> m >> k;
	std::vector<std::vector<char> > mp(n + 1, std::vector<char>(m + 1));
	std::vector<std::vector<int> > dp(n + 1, std::vector<int>(m + 1, inf));
	dp[1][0] = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			std::cin >> mp[i][j];
		}
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			dp[i][j] = std::min({dp[i][j - 1], dp[i - 1][j]}) + (mp[i][j] == '#');
		}
	}
	std::cout << (dp[n][m] <= k ? "Yes\n" : "No\n");
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	while (t --) {
		solve();
	}
	return 0;
}