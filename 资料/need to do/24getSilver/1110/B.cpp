#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, b, c;
	std::cin >> n >> b >> c;
	int num = 0;
	if (b >= 1) { // c, c + b, ... c + x * b <= n
		if (c <= n) {
			num = (n - c + b - 1) / b;
		}
		std::cout << n - num << '\n';
	} else {
		// b = 0; all c
		// c c + 1// c c + 2
		if (c + 2 < n) {
			std::cout << -1 << '\n';
			return ;
		}
		// 0 -- c - 1
		if (c >= n) { // 
			std::cout << n << '\n';
		} else {
			std::cout << c + (c != n - 1) << '\n';
		}
	}
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