#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<std::array<int, 2> > > e(n + 1);
	for (int i = 1; i <= m; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	i64 ans = n;
	// std::cout << "!!! " << 1 << ' ' << ans << '\n';
	i64 res;
	res = 0;
	std::set<std::array<int, 2> > have;
	for (int i = 1; i <= n; i ++) {
		std::map<std::array<int, 2>, bool> mp;
		for (auto it : e[i]) {
			int v = it[0], w = it[1];
			if (mp.count({v, w ^ 1})) {
				res ++;
				have.insert({std::min(i, v), std::max(i, v)});
			} 
			mp[{v, w}] = 1;
		}
	}
	ans += res / 2;
	// std::cout << "!!! " << 2 << ' ' << ans << '\n';
	res = 0;
	for (auto it : have) {
		int x = it[0], y = it[1];
		std::map<std::array<int, 2>, bool> mp;
		for (auto it : e[x]) {
			int v = it[0], w = it[1];
			mp[{v, w}] = 1;
		}
		for (auto it : e[y]) {
			int v = it[0], w = it[1];
			if (mp.count({v, w ^ 1})) {
				res ++;
			}
		}
	}
	ans += res;
	// std::cout << "!!! " << 3 << ' ' << ans << '\n';
	res = 0;
	// int siz = have.size();
	// std::vector<std::vector<std::array<int, 2> > > E(siz + 1);
	// std::map<int, int> rev;
	// int cnt = 0;
	// for (auto it : have) {
	// 	rev[it[0]] = rev[it[1]] = ++ cnt;
	// } 
	// for (auto it : have) {
	// 	int U1 = rev[it[0]], U2 = rev[it[1]];
	// 	for (auto op : e[it[0]]) {
	// 		int v = op[0], w = op[1];
	// 		if (v == it[1] || ! rev.count(v)) continue;
	// 		E[U1].push_back({rev[v], w});
	// 		// E[rev[v]].push_back({U1, w});
	// 	}
	// 	for (auto op : e[it[1]]) {
	// 		int v = op[0], w = op[1];
	// 		if (v == it[0] || ! rev.count(v)) continue;
	// 		E[U2].push_back({rev[v], w});
	// 		// E[rev[v]].push_back({U2, w});
	// 	}
	// }
	// for (int i = 1; i <= cnt; i ++) {
	// 	std::map<std::array<int, 2>, bool> mp;
	// 	for (auto it : E[i]) {
	// 		int v = it[0], w = it[1];
	// 		if (mp.count({v, w ^ 1})) {
	// 			res ++;
	// 		}
	// 		mp[{v, w}] = 1;
	// 	}
	// }
	// std::cout << "?? " << res << '\n';
	// ans += res / 2;

	std::vector<bool> vis(n + 1);
	std::vector<int> stk;
	auto dfs = [&](auto self, int u) -> void {
		vis[u] = 1;
		stk.push_back(u);
		for (auto it : e[u]) {
			if (! vis[it[0]]) {
				self(self, it[0]);
			}
		}
	};
	std::vector<bool> ck(n + 1);
	auto dfs2 = [&](auto self, int u, int col) -> void {
		ck[u] = 1;
		for (auto it : e[u]) {
			if (! ck[it[0]] && it[1] == col) {
				self(self,it[0], col);
			}
		}
	};
	auto check = [&]() -> bool {
		for (auto it : stk) {
			ck[it] = 0;
		}
		dfs2(dfs2, stk[0], 0);
		for (auto it : stk) {
			if (! ck[it]) {
				return false;
			}
		}

		for (auto it : stk) {
			ck[it] = 0;
		}
		dfs2(dfs2, stk[0], 1);
		for (auto it : stk) {
			if (! ck[it]) {
				return false;
			}
		}
		return true;
	};
	for (int i = 1; i <= n; i ++) {
		if (! vis[i]) {
			stk.clear();
			dfs(dfs, i);
			if (stk.size() == 4) {
				if (check()) {
					ans ++;
				}
			}
		}
	}
	std::cout << ans % mod << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}
/*
4 6
1 2 0
1 3 0
3 4 0
3 4 1
2 4 1
1 2 1
7
*/