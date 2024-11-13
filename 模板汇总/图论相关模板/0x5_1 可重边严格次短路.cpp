#include <bits/stdc++.h>
using i64 = long long;
#define int i64
const int inf = 1e18;
using pii = std::array<int, 2>;

// 严格次短路两种：
// 1. 把最短路中有重复过程，给多走了;
// 2. 不是最短路刻意而来的，是正常的求出的，不重复。

// differ : 
// 1. no vis
// 2. d[0], d[1] update; attention neq. "&&"
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<pii> > e(n + 1);
	for (int i = 1; i <= m; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	int s = 1, t = n;
	std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
	std::vector<pii> d(n + 1, {inf, inf});
	d[s][0] = 0;
	q.push({0, s});
	while (! q.empty()) {
		auto it = q.top();
		q.pop();
		int u = it[1], val = it[0];
 		// 不用 vis 是因为可能重复通过。
 		for (auto op : e[u]) {
 			int v = op[0], w = op[1];
 			//std::cerr << "! " << v << ' ' << w << '\n';
 			if (d[v][0] > val + w) {
 				d[v][1] = d[v][0];
 				d[v][0] = val + w;
 				q.push({d[v][0], v});
 				q.push({d[v][1], v});
 			} else if (d[v][1] > val + w && d[v][0] < val + w) {
 				// strictly 不等与最短路相等
 				d[v][1] = val + w;
 				q.push({d[v][1], v});
 			}
 		}
	}
	std::cout << d[t][1] << '\n';
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
