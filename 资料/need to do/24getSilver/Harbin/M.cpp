#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> d;
	for (int i = 1; i * i <= n; i ++) {
		if (n % i == 0) {
			d.push_back(i);
			if (n / i != i) {
				d.push_back(n / i);
			}
		}
	}
	std::sort(d.begin(), d.end());
	int ans = 0;
	int now = 0;
	for (int i = 1; i < d.size(); i ++) {
		ans += (d[i] - d[i - 1]) * n / d[i - 1];
	}
	std::cout << ans + 1 << '\n';
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