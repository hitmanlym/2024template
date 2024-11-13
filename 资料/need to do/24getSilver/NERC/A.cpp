#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n, a, b;
	std::cin >> a >> b >> n;
	int num = 0;
	int x = a, y = b;
	while (x < n || y < n) {
		if (x < y) {
			num ++;
			x = y;
		} else {
			num ++;
			y += b - a;
			y = std::min(y, n);
		}
		// std::cout << x << ' ' << y << '\n';
	}
	std::cout << num << '\n';
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