#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, m, q;
	std::cin >> n >> m >> q;
	std::vector<int> a(n + n);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	int cnt = n;
	std::vector<std::array<int, 3> > e(m);
	for (int i = 0; i < m; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		e[i] = {w, u, v};
	}
	std::sort(e.begin(), e.end());
	std::vector<int> f(n + n);
	for (int i = 1; i < n + n; i ++) {
		f[i] = i;
	}
	auto find = [&](int x) -> int {
		while (x != f[x]) {
			x = f[x] = f[f[x]];
		}
		return x;
	};
	std::vector<std::vector<int> > fa(n + n, std::vector<int>(20)), c(n + n, std::vector<int>(20));
	for (int i = 0; i < m; i ++) {
		int w = e[i][0], u = e[i][1], v = e[i][2];
		u = find(u);
		v = find(v);
		if (u == v) {
			continue;
		}
		a[++ cnt] = a[u] + a[v];
		assert(cnt < n + n);
		fa[u][0] = cnt;
		fa[v][0] = cnt;
		c[u][0] = w - a[u];
		c[v][0] = w - a[v];
		f[u] = cnt;
		f[v] = cnt;
	}
	a[0] = a[cnt];
	for (int j = 1; j < 20; j ++) {
		for (int i = 1; i < n + n; i ++) {
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
			c[i][j] = std::max(c[i][j - 1], c[fa[i][j - 1]][j - 1]);
		}
	}
	while (q --) {
		int x, k;
		std::cin >> x >> k;
		for (int i = 19; i >= 0; i --) {
			if (c[x][i] <= k) x = fa[x][i];
		}
		std::cout << a[x] + k << '\n';
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