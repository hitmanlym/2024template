#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
const int inf = 1e18;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), b(n + 1), sum(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	for (int i = 1; i <= n; i ++) {
		std::cin >> b[i];
	}
	std::vector<std::vector<pii> > e(n + 1);
	std::vector<int> d(n + 1, inf);
	for (int i = 1; i <= n; i ++) {
		e[i].push_back({b[i], a[i]});
	}
	for (int i = n - 1; i >= 1; i --) {
		e[i + 1].push_back({i, 0});
	}
	std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
	q.push({0, 1});
	d[1] = 0;
	std::vector<bool> vis(n + 1);
	while (! q.empty()) {
		auto it = q.top();
		q.pop();
		int u = it[1];
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto op : e[u]) {
			int v = op[0], w = op[1];
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				q.push({d[v], v});
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i ++) {
		// std::cout << sum[i] << ' ' << d[i] << '\n';
		ans = std::max(ans, sum[i] - d[i]);
	}
	std::cout << ans << '\n';
} 
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}