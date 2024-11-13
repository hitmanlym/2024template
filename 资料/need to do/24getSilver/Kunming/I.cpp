#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	std::string s;
	std::cin >> s;
	int n = s.size();
	char c = s[0];
	int id = -1;
	for (int i = 1; i < n; i ++) {
		if (s[i] != c) {
			id = i;
			break;
		}
	}
	if (id == -1) {
		std::cout << n / 2 << '\n';
		return ;
	}
	std::string t = "";
	for (int i = id; i < n; i ++) {
		t += s[i];
	}
	for (int i = 0; i < id; i ++) {
		t += s[i];
	}

	int num = 0, f = 0;
	for (int i = 0; i < n; i ++) {
		int j = i;
		while (j < n && t[j] == t[i]) {
			j ++;
		}
		int len = j - i;
		if (len > 0 && len % 2 == 0) {
			f = 1;
		}
		num += len / 2;
		i = j - 1;
	}
	std::cout << num - f << '\n';
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