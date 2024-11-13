#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> w(n);
	for (int i = 0; i < n; i ++) {
		std::cin >> w[i];
	}
	int ans = 0;
	for (int i = 0; i < (1 << n); i ++) {
		if (__builtin_popcount(i) == n - m) {
			std::bitset<2001> b;
			b[0] = 1;
			for (int j = 0; j < n; j ++) {
				if (i >> j & 1) {
					b |= b << w[j];
				}
			}
			ans = std::max(ans, (int)b.count());
		}
	}
	std::cout << ans - 1 << '\n';
} 
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}