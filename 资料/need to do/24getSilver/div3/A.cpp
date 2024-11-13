#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	if (n & 1) {
		std::cout << "Kosuke\n";
	} else {
		std::cout << "Sakurako\n";
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