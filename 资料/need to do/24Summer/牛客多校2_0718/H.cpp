#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, x, y;
	std::cin >> n >> x >> y;
	std::map<std::array<int, 2>, int> mp;
	std::vector<std::array<int, 2> > t(n + 1);
	std::string s;
	std::cin >> s;
	int a = 0, b = 0;
	t[0] = {0, 0};
	for (int i = 1; i <= n; i ++) {
		if (s[i - 1] == 'A') a --;
		if (s[i - 1] == 'D') a ++;
		if (s[i - 1] == 'W') b ++;
		if (s[i - 1] == 'S') b --;
		t[i] = {a, b};
	}
	int ans = 0;
	if (x == 0 && y == 0) {
		std::cout << n * (n + 1) / 2 << '\n';
		return ;
	}
	mp[{0, 0}] ++;
	for (int i = 1; i <= n; i ++) {
		mp[t[i]] ++;
		int u = t[i][0] - x, v = t[i][1] - y;
		//std::cout << mp[t[i]] << '\n';
		if (mp.count({u, v})) {
			ans += mp[{u, v}] * (n - i + 1);
			mp.erase({u, v});/*
			if (u == 0 && v == 0) {
				mp[{0, 0}] = 1;
			}*/
		}
	}
	std::cout << ans << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}