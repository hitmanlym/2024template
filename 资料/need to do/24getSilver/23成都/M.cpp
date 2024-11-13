#include<bits/stdc++.h>
using i64 = long long;
#define int i64
#define double long double
const double inf = std::numeric_limits<double>::max();
using pii = std::pair<int, double>;
using ipp = std::pair<double, int>;
void solve() {
	int n, m, t;
	std::cin >> n >> m >> t;
	std::vector<std::vector<std::pair<int, double> > > e(n + 1);
	for (int i = 1; i <= m; i ++) {
		int u, v, a, b;
		std::cin >> u >> v >> a >> b;
		double it = (double)std::sqrt((double)a) * (double)std::sqrt((double)b);
		e[u].push_back({v, it});
		e[v].push_back({u, it});
	}
	std::vector<double> d(n + 1, inf);
	std::vector<bool> vis(n + 1);
	d[1] = 0.0;
	std::priority_queue<ipp, std::vector<ipp>, std::greater<ipp> > q;
	q.push({0.0, 1});
	while (! q.empty()) {
		auto it = q.top();
		q.pop();
		int u = it.second;
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto it : e[u]) {
			int v = it.first;
			double w = it.second;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				q.push(std::make_pair(d[v], v));
			}
		}
	}
	double ans = d[n] / t * d[n];
	printf("%.10Lf\n", ans);
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