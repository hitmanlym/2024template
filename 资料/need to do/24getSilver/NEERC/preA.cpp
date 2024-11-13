#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int o = 9;
	auto count = [&](int x) -> int {
		int num = 0;
		while (x) {
			num += x % 10;
			x /= 10;
		}
		return num;
	};
	for (int i = 1; ; i ++) {
		if (count(i * o) == 89) {
			std::cout << i * o << '\n';
			return ;
		}
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