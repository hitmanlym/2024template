#include<bits/stdc++.h>
using i64 = long long;
using pii = std::array<int, 2>;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<bool> vis_U(n + 1), vis_E(m + 1);
	std::vector<pii> ans(m + 1); // 0/1, 0/1
	std::vector<std::vector<pii> > e(n + 1);
	std::vector<int> fornow(n + 1);
	std::vector<pii> E(m + 1);
	for (int i = 1; i <= m; i ++) {
		int u, v;
		std::cin >> u >> v;
		E[i] = {u, v};
		e[u].push_back({v, i});
		e[v].push_back({u, i});
	}
	auto check = [&](int y, int id1, int id2) {
		ans[id1] = {(E[id1][0] == y ? 0 : 1), (id1 > id2)};
		ans[id2] = {(E[id2][0] == y ? 0 : 1), (id1 < id2)};
	};
	auto dfs = [&](auto&& self, int u) -> pii { // I konw i konw...
		vis_U[u] = 1;
		pii now = {0, 0};
		// for (int i = fornow[u]; i < e[u].size(); i = fornow[u] +) {
			// int v = e[u][i][0], id = e[u][i][1];
		// for (auto it ; e[u]) {
		// 	int v = it[0], id = it[1];
		while (fornow[u] < e[u].size()) {
			int v = e[u][fornow[u]][0], id = e[u][fornow[u]][1];
			fornow[u] ++;
			if (vis_E[id]) continue;
			vis_E[id] = 1;
			pii down = self(self, v); // w, id
			if (down[0]) {
				// u, v, w
				check(v, id, down[1]);
			} else {
				if (now[0]) {
					check(u, now[1], id);
					now = {0, 0};
				} else {
					now = {v, id};
				}
			}
		}
		return now;
	};
	for (int i = 1; i <= n; i ++) {
		if (! vis_U[i]) {
			pii it = dfs(dfs, i); // 不需要去特判它的，
		}
	}
	for (int i = 1; i <= m; i ++) {
		std::cout << (ans[i][0] ? 'y' : 'x') << (ans[i][1] ? '-' : '+') << '\n';
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