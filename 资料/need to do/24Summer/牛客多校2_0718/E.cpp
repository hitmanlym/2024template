#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	i64 n;
	std::cin >> n;
	i64 x = n & (-n);
	if (n - x > 0) {
		std::cout << n - x << '\n';
	} else {
		std::cout << -1 << '\n';
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}