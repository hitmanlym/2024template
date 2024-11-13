#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int h, n, m;
	std::cin >> h >> n;
	std::vector<std::array<int, 3> > p(n);
	for (int i = 0; i < n; i ++) {
		std::cin >> p[i][0] >> p[i][1]; // 0
	}
	std::cin >> m;
	p.resize(n + m);
	for (int i = n; i < n + m; i ++) {
		std::cin >> p[i][0] >> p[i][1];
		p[i][2] = 1; // 
	}
	std::sort(p.begin(), p.end(), [&](auto x, auto y) {
		return x[0] > y[0] || x[0] == y[0] && x[1] > y[1];
	});
	std::map<int, int> dp;
	for (auto it : p) {
		int x = it[0], y = it[1], op = it[2];
		int i = (x + y) % (2 * h);
		int j = (2 * h + (x - y) % (2 * h)) % (2 * h);
		if (op) {
			dp[i] ++;
			dp[j] ++;
		} else {
			int max = std::max(dp[i], dp[j]);
			dp[i] = dp[j] = max;
		}
	}
	std::cout << dp[0] << '\n';
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