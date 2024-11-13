#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
void solve() {
	int n, m, k;
	std::cin >> n >> m >> k;
	std::vector<std::vector<int> > col(m + 1);
	for (int i = 1; i <= n; i ++) {
		int x;
		std::cin >> x;
		col[x].push_back(i);
	}
	int ans = 1;
	for (auto it : col) {
		int l = 0, r = 0;
		while (l < it.size()) {
			while (r < it.size()) {
				if ((it[r] - it[l] + 1) - (r - l + 1) <= k) {
					r ++;
				} else {
					break;
				}
			}
			int R = r - 1;
			ans = std::max(ans, R - l + 1);
			l ++;
		}
	}
	std::cout << ans << '\n';
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