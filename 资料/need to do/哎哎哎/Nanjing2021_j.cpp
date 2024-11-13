#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int a, b;
	std::cin >> a >> b;
	if (a > b) std::swap(a, b);
	int x = b - a;
	std::vector<int> p;
	auto check = [&](int x) -> bool {
		if (x == 1) return false;
		for (int i = 2; i * i <= x; i ++) {
			if (x % i == 0) return false;
		}
		return true;
	};
	for (int i = 1; i * i <= x; i ++) {
		if (x % i == 0) {
			if (check(i)) p.push_back(i);
			if (check(x / i)) p.push_back(x / i);
		}
	}
	std::map<int, int> mp;
	auto dfs = [&](auto self, int a, int b) -> int {
		if (a == 1 && b == 1) return 0;
		int op = a * 1e9 + b;
		if (mp.count(op)) return mp[op];
		int res = a - 1;
		for (auto v : p) {
			if (b % v) continue;
			res = std::min({
				res,
				self(self, a / v, b / v) + a % v + 1,
				self(self, (a + v - 1) / v, b / v) + v - a % v + 1
			});
		}
		mp[op] = res;
		return res;
	};
	std::cout << dfs(dfs, a, x) << '\n';
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