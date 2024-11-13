#include <bits/stdc++.h>
using i64 = long long;
#define int i64
const double inf = 1e15;
using pii = std::pair<int, double>;
using pll = std::pair<double, int>;
// 非严格的次短路，考虑删掉最短路上的一条边再进行查找， O(最短路边数 * nlogn)
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> x(n + 1), y(n + 1);
	std::vector<std::vector<pii> > e(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> x[i] >> y[i];
	}
	auto get = [&](int a, int b) -> double {
		double res = std::sqrt((double)(x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
		return res;
	};
	for (int i = 1; i <= m; i ++) {
		int u, v;
		std::cin >> u >> v;
		double dis = get(u, v);
		e[u].push_back(std::make_pair(v, dis));
		e[v].push_back(std::make_pair(u, dis));
	}
	std::vector<int> pre(n + 1);
	std::vector<double> d(n + 1);
	int s = 1, t = n;

	auto DJ = [&](int U, int V) -> void {
		d.assign(n + 1, inf);
		std::vector<bool> vis(n + 1, 0);
		std::priority_queue<pll, std::vector<pll>, std::greater<pll> > q;
		q.push(std::make_pair(0.0, s));
		d[s] = 0;
		while (! q.empty()) {
			auto it = q.top();
			q.pop();
			int u = it.second;
			if (vis[u]) continue;
			for (auto op : e[u]) {
				int v = op.first;
				double w = op.second;
				if (u == U && v == V || u == V && v == U) continue;
				if (d[v] > d[u] + w) {
					d[v] = d[u] + w;
					if (U == -1 && V == -1) {
						pre[v] = u;
					}
					q.push(std::make_pair(d[v], v));
				}
			}
		}
	};
	double ans = inf;
	DJ(-1, -1);
	for (int i = t; i != s; i = pre[i]) {
		DJ(i, pre[i]);
		ans = std::min(ans, d[t]);
	}
	if (ans == inf) {
		printf("-1\n");
	} else {
		printf("%.2lf\n", ans);
	}
} 
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}
