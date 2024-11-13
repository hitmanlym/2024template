#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n = 2000;
	for (int i = 1; i <= n; i ++) {
		std::cout << (i + 12346848) % 45168 << ' ';
	}
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