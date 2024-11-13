#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::vector<int> > a(n + 1, std::vector<int>(n + 1));
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			std::cin >> a[i][j];
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			if (a[i][j] < 0) {
				int min = a[i][j], k = 1;
				for (; ; k ++) {
					if (i + k > n || j + k > n) break;
					min = std::min(min, a[i + k][j + k]);
				}
				while (-- k) {
					a[i + k][j + k] -= min;
				}
				ans -= min;
			}
		}
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