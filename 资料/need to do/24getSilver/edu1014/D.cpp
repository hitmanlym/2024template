#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int> > a;
	std::vector<std::vector<int> > c;
	std::vector<std::vector<int> > dp(m + 1, std::vector<int>(m + 1));
	std::vector<int> b(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> b[i];
	}
	for (int i = 1; i <= n; i ++) {
		if (b[i] == 0) {
			int j = i + 1;
			std::vector<int> va, vc;
			while (j <= n && b[j] != 0) {
				if (b[j] > 0) va.push_back(b[j]);
				else vc.push_back(-b[j]);
				j ++;
			}
			i = j - 1;
			std::sort(va.begin(), va.end());
			std::sort(vc.begin(), vc.end());
			a.push_back(va);
			c.push_back(vc);
		}
	}
	int ans = 0;
	for (int i = 1; i <= m; i ++) {
		for (int j = 0; j <= i; j ++) { // i plus positive
			int A = j, B = (i - j);
			int x = std::upper_bound(a[i - 1].begin(), a[i - 1].end(), A) - a[i - 1].begin();
			int y = std::upper_bound(c[i - 1].begin(), c[i - 1].end(), B) - c[i - 1].begin();
			
			// if (i == m) {
			// 	std::cout << x << ' ' << a[i - 1].size() << '\n';
			// std::cout << y << ' ' << c[i - 1].size() << '\n';
			// std::cout << '\n';
			// }
			if (j > 0) {
				dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1] + x + y);
			}
			if (j < i) {
				dp[i][j] = std::max(dp[i][j], dp[i - 1][j] + x + y);
			}
		}
		// for (int j = 0; j <= m; j ++) {
		// 	std::cout << dp[i][j] << ' ';
		// }
		// std::cout << '\n';
	}
	for (int i = 0; i <= m; i ++) {
		ans = std::max(ans, dp[m][i]);
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