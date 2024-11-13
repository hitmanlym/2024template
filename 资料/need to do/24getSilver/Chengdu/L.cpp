#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int a, b, c;
	std::cin >> a >> b >> c;
	std::cout << 100 << '\n';
	for (int i = 1; i <= 50; i ++) {
		std::cout << a << ' ';
	}
	for (int i = 1; i <= 45; i ++) {
		std::cout << b << ' ';
	}
	for (int i = 1; i <= 4; i ++) {
		std::cout << c << ' ';
	}
	std::cout << c + 1 << '\n';
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