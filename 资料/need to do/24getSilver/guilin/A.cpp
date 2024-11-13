#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	std::string s;
	std::cin >> s;
	std::vector<bool> is(n);
	for (int i = 0; i < n; i ++) {
		if (s[i] == 'L') {
			if (i - 1 >= 0) is[i - 1] = 1;
			if (i + 1 < n) is[i + 1] = 1;
			is[i] = 1;
		}
	}
	for (int i = 0; i < n; i ++) {
		if (is[i] == 1) {
			std::cout << s[i];
		} else {
			std::cout << 'C';
		}
	}
	std::cout << '\n';
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