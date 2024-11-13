#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
void solve() {
	int n, m;
	std::cin >> n >> m;
	if (m & 1) {
		std::cout << "No solution\n";
		return ;
	}
	std::vector<std::vector<std::array<int, 2> > > e(n + 1);
	for (int i = 1; i <= m; i ++) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back({v, i});
		e[v].push_back({u, i});
	}
	std::vector<int> vis_U(n + 1), vis_E(m + 1);
	std::vector<std::array<int, 3> > ans;
	auto dfs = [&](auto self, int u) -> int {
		std::vector<int> st;
		for (auto it : e[u]) {
			int v = it[0], id = it[1];
			if (vis_E[id]) continue;
			vis_E[id] = 1;
			int down = self(self, v);
			if (down) {
				ans.push_back({u, v, down});
			} else {
				st.push_back(v);
			}
		}
		while (st.size() > 1) {
			int x = st.back(); st.pop_back();
			int y = st.back(); st.pop_back();
			ans.push_back({x, u, y});
		}
		if (st.size()) {
			return st.back();
		} else {
			return 0;
		}
	};
	dfs(dfs, 1);
	for (auto it : ans) {
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