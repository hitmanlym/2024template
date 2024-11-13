#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	std::string s, t;
	std::cin >> s >> t;
	int num = s.size() + t.size(), op = 0;
	while (op < s.size() && op < t.size() && s[op] == t[op]) {
		op ++;
	}
	if (op) op --;
	std::cout << num - op << '\n';
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