#include<bits/stdc++.h>
using i64 = long long;

const int mod = 1e6 + 7;
void solve() {
	int m, n;
	std::cin >> m >> n;
	std::vector<std::vector<int> > e(n + 1);
	std::vector<std::array<int, 2> > a(n + 1);
	std::vector<bool> vis(n + 1);
	for (int i = 1; i <= n; i ++) {
		int z;
		std::cin >> a[i][0] >> a[i][1] >> z;
		if (z) {
			e[z].push_back(i);
			vis[i] = 1;
		}
	}
	std::vector<int> dp(m + 1);
	for (int i = 1; i <= n; i ++) {
		if (vis[i]) continue;
		int u = e[i].size();
		std::vector<std::array<int, 2> > f;
		f.push_back({a[i][0], a[i][0] * a[i][1]});
		if (u == 1) {
			int v = e[i][0];
			f.push_back({a[i][0] + a[v][0], a[i][0] * a[i][1] + a[v][0] * a[v][1]});
		}
		if (u == 2) {
			int x = e[i][0], y = e[i][1];
			f.push_back({a[i][0] + a[x][0], a[i][0] * a[i][1] + a[x][0] * a[x][1]});
			f.push_back({a[i][0] + a[y][0], a[i][0] * a[i][1] + a[y][0] * a[y][1]});
			f.push_back({a[i][0] + a[x][0] + a[y][0], 
				a[i][0] * a[i][1] + a[x][0] * a[x][1] + a[y][0] * a[y][1]});
		}
		for (int j = m; j >= 0; j --) {
			for (auto it : f) {
				int g = it[0], w = it[1];
				if (g > j) continue; 
				dp[j] = std::max(dp[j], dp[j - g] + w);
			}
		}
	}
	std::cout << dp[m] << '\n';
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