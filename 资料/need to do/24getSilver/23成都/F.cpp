#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	if (n <= 3) {
		std::cout << -1 << '\n';
		return ;
	} 
	std::cout << n + 1 << '\n';
	std::cout << 1 << ' ' << 2 << '\n';
	std::cout << 1 << ' ' << 3 << '\n';
	std::cout << 1 << ' ' << 4 << '\n';
	std::cout << 2 << ' ' << 4 << '\n';
	std::cout << 3 << ' ' << 4 << '\n';
	for (int i = 5; i <= n; i ++) {
		std::cout << 1 << ' ' << i << '\n';
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}