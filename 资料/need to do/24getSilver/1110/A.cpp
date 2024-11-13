#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, a, b;
	std::cin >> n >> a >> b;
	std::vector<std::vector<int> > vis(n + 1);
	int x = 0, y = 0;
	std::string s;
	std::cin >> s;
	std::map<std::array<int, 2>, bool> mp;
	for (int i = 0; i < n; i ++) {
		if (s[i] == 'N') y ++;
		if (s[i] == 'E') x ++;
		if (s[i] == 'S') y --;
		if (s[i] == 'W') x --;
		mp[{x, y}] = 1;
	}
	int u = 0, v = 0;
	for (int i = 1; i <= 100; i ++) {
		if (mp.count({a - u, b - v})) {
			std::cout << "YES\n";
			return ;
		}
		u += x;
		v += y;
	}
	std::cout << "NO\n";
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