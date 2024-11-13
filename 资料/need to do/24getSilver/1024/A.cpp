#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	std::string s;
	std::cin >> s;
	// int n = s.size();
	// int f = -1;
	// for (int i = 0; i < n; i ++) {
	// 	if (s[i] != '9') {
	// 		f = i;
	// 	}
	// }
	// if (f == -1) {
	// 	std::cout << s << 0 << '\n';
	// } else {
	// 	for (int i = 0; i < f; i ++) {
	// 		std::cout << s[i];
	// 	}
	// 	std::cout << (char)(s[f] + 1);
	// 	for (int i = f + 1; i < n; i ++) {
	// 		std::cout << s[i];
	// 	}
	// 	std::cout << '\n';
	// }
	std::cout << s << 0 << '\n';
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