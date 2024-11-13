#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int x, y, k;
	std::cin >> x >> y >> k;
	int o = std::min(x, y);
	std::cout << 0 << ' ' << 0 << ' ' << o << ' ' << o << '\n';
	std::cout << 0 << ' ' << o << ' ' << o << ' ' << 0 << '\n';
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