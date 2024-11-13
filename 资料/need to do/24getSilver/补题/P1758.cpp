#include<bits/stdc++.h>
using i64 = long long;
const int mod = 1024523;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::string s, t;
	std::cin >> s >> t;
	std::reverse(s.begin(), s.end());
	std::reverse(t.begin(), t.end());
	s = " " + s;
	t = " " + t;
	std::vector<std::vector<std::array<int, 2> > >
		dp(n + 1, std::vector<std::array<int, 2> >(n + 1));
	dp[0][0][0] = 1;
	for (int k = 1; k <= n + m; k ++) {
		int u = (k & 1), v = (u ^ 1);
		for (int i = 0; i <= n; i ++) {
			for (int j = 0; j <= n; j ++) {
				dp[i][j][u] = 0;
			}
		}
		// now get k pi
		for (int i = std::max(0, k - m); i <= std::min(n, k); i ++) {
			for (int j = std::max(0, k - m); j <= std::min(n, k); j ++) {
				if (i && j && s[i] == s[j]) {
					dp[i][j][u] += dp[i - 1][j - 1][v];
					dp[i][j][u] %= mod;
				}
				if (i && k - j && s[i] == t[k - j]) {
					dp[i][j][u] += dp[i - 1][j][v];
					dp[i][j][u] %= mod;
				}
				if (k - i && j && t[k - i] == s[j]) {
					dp[i][j][u] += dp[i][j - 1][v];
					dp[i][j][u] %= mod;
				}
				if (k - i && k - j && t[k - i] == t[k - j]) {
					dp[i][j][u] += dp[i][j][v];
					dp[i][j][u] %= mod;
				}
			}
		}
	}
	std::cout << dp[n][n][(n + m) & 1] << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}