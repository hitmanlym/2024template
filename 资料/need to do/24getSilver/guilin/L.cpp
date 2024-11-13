#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, m;
	std::cin >> n >> m;
	if (n < 2 * m) {
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j < m - (i - 1) / 2; j ++) {
				std::cout << 0 << ' ';
			}
			std::cout << 1 << ' ';
			for (int j = m - (i - 1) / 2 + 1; j <= m; j ++) {
				std::cout << 0 << ' ';
			}
			std::cout << '\n';
		}
	} else {
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j < m - (i - 1) / 2; j ++) {
				std::cout << 0 << ' ';
			}
			std::cout << 1 << ' ';
			for (int j = std::max(2ll, m - (i - 1) / 2 + 1); j <= m; j ++) {
				std::cout << 0 << ' ';
			}
			std::cout << '\n';	
		}
	}
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