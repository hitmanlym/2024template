#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int l, r, b, k;
	std::cin >> l >> r >> b >> k;
	// std::cout << k * std::max(l, b) << '\n';
	// b >= l  ---> k * b
	// b < l   ---> 
	if (b >= l) {
		std::cout << k * b << '\n';
	} else {
		int u = (l + b - 1) / b;
		// std::cout << u << '\n';
		std::cout << k * u * b << '\n';
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