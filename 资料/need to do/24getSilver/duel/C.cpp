#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	std::string s;
	std::cin >> s;
	if (s[0] == '1' || s[n - 1] == '1') {
		std::cout << "YES\n";
	} else {
		bool f = 0;
		for (int i = 0; i < n - 1; i ++) {
			if (s[i] == '1' && s[i + 1] == '1') {
				f = 1;
			}
		}
		if (f) {
			std::cout << "YES\n";
		} else {
			std::cout << "NO\n";
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