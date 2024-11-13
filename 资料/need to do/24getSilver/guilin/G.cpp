#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	std::vector<std::vector<int> > e(n + 1);
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	std::vector<std::vector<pii> > max(n + 1, std::vector<pii>(4)), MAX(n + 1, std::vector<pii>(3));
	auto add = [&](int id, int u, int val) { // val 除自己  
		for (int i = 0; i < 4; i ++) {
			if (val > max[id][i][0]) {
				for (int j = 3; j > i; j --) {
					max[id][j] = max[id][j - 1];
				}
				max[id][i] = {val, u};
				break;
			}
		}
	};
	auto ADD = [&](int id, int u, int val) { // 除自己
		for (int i = 0; i < 3; i ++) {
			if (val > MAX[id][i][0]) {
				for (int j = 2; j > i; j --) {
					MAX[id][j] = MAX[id][j - 1];
				}
				MAX[id][i] = {val, u};
				break;
			}
		}
	};
	auto dfs = [&](auto self, int u, int p) -> void {
		for (auto v : e[u]) {
			if (v == p) continue;
			self(self, v, u);
			add(u, v, max[v][0][0] + a[v]); // max链
			ADD(u, v, std::max(max[v][0][0] + max[v][1][0] + a[v], MAX[v][0][0]));
			// ADD(u, v, MAX[v][0][0]);
		}
	};
	dfs(dfs, 1, 0);
	int ans = 0;
	auto dfs1 = [&](auto self, int u, int p) -> void {
		ans = std::max({
			ans, max[u][0][0] + max[u][1][0] + max[u][2][0] + max[u][3][0],
			MAX[u][0][0] + MAX[u][1][0]
		});
		int res1 = MAX[u][0][0], res2 = MAX[u][1][0], res3 = MAX[u][2][0];
		int num1 = 0, num2 = 0, num3 = 0;
		if (res1) {
			res1 += a[u];
			for (int i = 0; i < 4; i ++) {
				if (max[u][i][1] != MAX[u][0][1]) {
					num1 ++;
					res1 += max[u][i][0];
				}
				if (num1 == 2) break;
			}
		}
		if (res2) {
			res2 += a[u];
			for (int i = 0; i < 4; i ++) {
				if (max[u][i][1] != MAX[u][1][1]) {
					num2 ++;
					res2 += max[u][i][0];
				}
				if (num2 == 2) break;
			}
		}
		if (res3) {
			res3 += a[u];
			for (int i = 0; i < 4; i ++) {
				if (max[u][i][1] != MAX[u][2][1]) {
					num3 ++;
					res3 += max[u][i][0];
				}
				if (num3 == 2) break;
			}
		}
		ans = std::max({
			ans, res1, res2, res3
		});

		// std::cout << u << ' ' << ans << '\n';
		for (auto v : e[u]) {
			if (v == p) continue;
			
			int op;
			for (int i = 0; i < 4; i ++) {
				// if (u == 2) {
				// 	std::cout << "!!! " << max[u][i][0] << ' ' << max[u][i][1] << '\n';
				// }
				if (max[u][i][1] != v) {
					op = i;
					add(v, u, max[u][i][0] + a[u]);
					break;
				}
			}
			// if (u == 2 && v == 4) {
			// 	std::cout << op << ' ' << a[u] << ' ' << max[u][op][0] << '\n';
			// }
			int maX = 0;
			for (int i = 0; i < 3; i ++) {
				if (MAX[u][i][1] != v) {
					maX = std::max(maX, MAX[u][i][0]);
					break;
				}
			}
			int num = 0, res = a[u];
			for (int i = 0; i <= 4; i ++) {
				if (max[u][i][1] != v) {
					num ++;
					res += max[u][i][0];
				}
				if (num == 2) break;
			}
			ADD(v, u, std::max(maX, res));

			self(self, v, u);
		}
	};
	dfs1(dfs1, 1, 0);
	// for (int i = 1; i <= n; i ++) {
	// 	for (int j = 0; j < 4; j ++) {
	// 		std::cout << max[i][j][0] << ' ' << max[i][j][1] << "    ";
	// 	}
	// 	std::cout << '\n';
	// }
	// std::cout << "\n";
	// for (int i = 1; i <= n; i ++) {
	// 	for (int j = 0; j < 3; j ++) {
	// 		std::cout << MAX[i][j][0] << ' ' << MAX[i][j][1] << "    ";
	// 	}
	// 	std::cout << '\n';
	// }
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