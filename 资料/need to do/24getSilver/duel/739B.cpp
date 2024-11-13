#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	std::vector<std::vector<int> > fa(n + 1, std::vector<int>(20));
	std::vector<std::vector<int> > dis(n + 1, std::vector<int>(20));
	std::vector<std::vector<int> > e(n + 1);
	std::vector<int> cnt(n + 1), ans(n + 1);
	for (int i = 2; i <= n; i ++) {
		int p, w;
		std::cin >> p >> w;
		e[p].push_back(i);
		fa[i][0] = p;
		dis[i][0] = w;
	}
	for (int j = 1; j <= 19; j ++) {
		for (int i = 1; i <= n; i ++) {
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
			dis[i][j] = dis[fa[i][j - 1]][j - 1] + dis[i][j - 1];
		}
	}
	for (int i = 1; i <= n; i ++) {
		int k = a[i];
		int u = i;
		for (int j = 19; j >= 0; j --) {
			if (dis[u][j] <= k) {
				k -= dis[u][j];
				u = fa[u][j];
			}
		}
		cnt[fa[i][0]] ++;
		cnt[fa[u][0]] --;
	}
	auto dfs = [&](auto self, int u) -> void {
		for (auto v : e[u]) {
			self(self, v);
			cnt[u] += cnt[v];
		}
		ans[u] = cnt[u];
	};
	dfs(dfs, 1);
	for (int i = 1; i <= n; i ++) {
		std::cout << ans[i] << ' ';
	}
	std::cout << '\n';
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