#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	std::string s;
	std::cin >> s;
	int l = 0;
	int y = 0, n = 0;
	while (l < 5 && s[l] != '-') {
		if (s[l] == 'Y') y ++;
		else n ++;
		l ++;
	}
	int o = 5 - y - n;
	if (y >= 4) {
		std::cout << 1 << '\n';
		return ;
	}
	if (y + o >= 4) {
		std::cout << 0 << '\n';
		return ;
	}
	std::cout << -1 << '\n';
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