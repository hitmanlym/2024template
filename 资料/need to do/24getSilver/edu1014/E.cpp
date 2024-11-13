#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 998244353;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int> > a(m + 1, std::vector<int>(m + 1)); // a 选了多少个,少于等于一半
	a[0][0] = 1;
	for (int i = 1; i <= m; i ++) {
		for (int j = 0; j + j <= i; j ++) {
			a[i][j] = (a[i][j] + a[i - 1][j]) % mod;
			if (j > 0) {
				a[i][j] = (a[i][j] + a[i - 1][j - 1]) % mod;
			}
		}
	}
	// for (int i = 1; i <= m; i ++) {
	// 	for (int j = 0; j <= m / 2; j ++) {
	// 		std::cout << a[i][j] << ' ';
	// 	}
	// 	std::cout << '\n';
	// }
	// std::cout << a[m][m / 2] << '\n';
	std::vector<std::vector<int> > dp(n, std::vector<int>(m + 1)); // 背包 
	// for (int i = 0; i < n; i ++) {
	// 	dp[i][0] = 1;
	// }
	// for (int i = 0; i <= m; i ++) {
	// 	dp[0][i] = 1;
	// }
	dp[0][0] = 1;
	for (int i = 1; i < n; i ++) { // n 遍
		for (int j = 0; j <= m / 2; j ++) { // A 选了这些
			int d = m - 2 * j;
			for (int k = m; k >= d; k --) {
				dp[i][k] = (dp[i][k] + dp[i - 1][k - d] * a[m][j] % mod) % mod;
			}
		}
	}

	// for (int i = 1; i < n; i ++) {
	// 	for (int j = 0; j <= m; j ++) {
	// 		std::cout << dp[i][j] << ' ';
	// 	}
	// 	std::cout << '\n';
	// }


	std::vector<std::vector<int> > b(m + 1, std::vector<int>(m + 1));
	b[0][0] = 1;
	for (int i = 1; i <= m; i ++) {
		for (int j = (i + 1) / 2; j <= i; j ++) { // A have
			b[i][j] = (b[i][j] + b[i - 1][j]) % mod;
			b[i][j] = (b[i][j] + b[i - 1][j - 1]) % mod;
		}
	}
	// for (int i = 1; i <= m; i ++) {
	// 	for (int j = 0; j <= m; j ++) {
	// 		std::cout << b[i][j] << ' ';
	// 	}
	// 	std::cout << '\n';
	// }
	// for (int i = 0; i <= m; i ++) {
	// 	std::cout << dp[n - 1][i] << ' ';
	// }
	// std::cout << '\n';
	int ans = 0;
	for (int i = 0; i <= m; i ++) { // 差额
		// x - y = i
		// x + y = m
		// x = (m + i) / 2
		if ((m + i) & 1) continue;
		ans = (ans + dp[n - 1][i] * b[m][(m + i) / 2]) % mod;
	}
	std::cout << ans << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}