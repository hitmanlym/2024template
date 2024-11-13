#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
#define int i64
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= m; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		a[u] += w;
		a[v] -= w;
	}
	int ans = 0;
	// for (int i = 1; i <= n; i ++) {
	// 	if (a[i] > 0) ans += a[i];
	// }
	// std::cout << ans << '\n';
	std::vector<std::array<int, 3> > e;
	std::vector<std::array<int, 2> > x, y;
	for (int i = 1; i <= n; i ++) {
		if (a[i] > 0) {
			x.push_back({i, a[i]});
		} 
		if (a[i] < 0) {
			y.push_back({i, -a[i]});
		}
	}
	int j = 0;
	for (int i = 0; i < x.size(); i ++) {
		int u = x[i][0], w = x[i][1];
		while (j < y.size()) {
			int op = std::min(w, y[j][1]);
			w -= op;
			y[j][1] -= op;
			e.push_back({u, y[j][0], op});
			if (! y[j][1]) {
				j ++;
			}
			if (! w) {
				break;
			}
		}
	}
	std::cout << e.size() << '\n';
	for (auto it : e) {
		std::cout << it[0] << ' ' << it[1] << ' ' << it[2] << '\n';
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