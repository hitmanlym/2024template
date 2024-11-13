#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), v;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		v.push_back(a[i]);
	}
	std::sort(v.begin(), v.end());
	v.erase(std::unique(v.begin(), v.end()), v.end());
	if (v.size() >= 2) {
		if (v[1] >= 2 * v[0]) {
			std::cout << v[0] << '\n';
		} else {
			std::cout << std::max(1ll, v[0] / 2) << '\n';
		}
	} else {
		std::cout << v[0] << '\n';
	}
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