#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int> > e(n + 1), E(2 * n + 1);
	for (int i = 1; i <= m; i ++) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	int dn = 0, cnt = n;
	std::vector<int> low(n + 1), dfn(n + 1), val(n * 2 + 1), stk;
	auto tarjan = [&](auto self, int u) -> void {
		low[u] = dfn[u] = ++ dn;
		stk.push_back(u);
		for (auto v : e[u]) {
			if (! dfn[v]) {
				self(self, v);
				low[u] = std::min(low[u], low[v]);
				if (low[v] == dfn[u]) {
					++ cnt;
					int x;
					do {
						x = stk.back();
						for (auto w : e[x]) {
							if ((low[w] == dfn[u] || w == u) && dfn[w] < dfn[x]) { // edge
								val[cnt] ++;
							}
						}
						E[cnt].push_back(x);
						E[x].push_back(cnt);
						stk.pop_back();
					} while (x != v);
					E[cnt].push_back(u);
					E[u].push_back(cnt);
					if (val[cnt] == 1) {
						val[cnt] = 0;
					}
				}
			} else {
				low[u] = std::min(low[u], dfn[v]);
			}
		}
	};
	tarjan(tarjan, 1);
	stk.pop_back();

	dn = 0;
	std::vector<std::vector<int> > fa(cnt + 1, std::vector<int>(19));
	std::vector<int> sum(cnt + 1), dep(cnt + 1);
	auto dfs = [&](auto self, int u, int p) -> void {
		sum[u] = sum[p] + val[u];
		dep[u] = dep[p] + 1;
		fa[u][0] = p;
		for (int i = 1; i <= 18; i ++) {
			fa[u][i] = fa[fa[u][i - 1]][i - 1];
		}
		for (auto v : E[u]) {
			if (v == p) continue;
			self(self, v, u);
		}
	};
	dfs(dfs, 1, 0);
	auto lca = [&](int x, int y) -> int {
		if (dep[x] < dep[y]) std::swap(x, y);
		for (int j = 18; j >= 0; j --) {
			if (dep[x] - dep[y] >= (1 << j)) {
				x = fa[x][j];
			}
		}
		if (x == y) return x;
		for (int j = 18; j >= 0; j --) {
			if (fa[x][j] != fa[y][j]) {
				x = fa[x][j];
				y = fa[y][j];
			}
		}
		return fa[x][0];
	};
	int q;
	std::cin >> q;
	while (q --) {
		int a, b;
		std::cin >> a >> b;
		int c = lca(a, b);
		std::cout << sum[a] + sum[b] - sum[c] - sum[fa[c][0]] << '\n';
	}
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