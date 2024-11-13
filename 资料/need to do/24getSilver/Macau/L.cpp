#include<bits/stdc++.h>
using i64 = long long;

const int inf = 1e9;
using pii = std::array<int, 2>;
void solve() {
	int n, x;
	std::cin >> n >> x;
	std::vector<int> a(n), min(n * 2, inf);
	min[0] = 0;
	for (int i = 0; i < n; i ++) {
		std::cin >> a[i];
	}
	std::vector<std::vector<pii > > e(n * 2);
	for (int i = 0; i < n; i ++) {
		int u = i, v = (i + a[i]) % n + n;
		e[u].push_back({v, 1});
	}
	for (int i = 0; i < n; i ++) {
		int u = i + n, v = (i + 1) % n + n;
		e[u].push_back({v, 1});
		e[u].push_back({i, 0});
	}
	std::vector<bool> vis(n * 2);
	std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
	q.push({0, 0});
	while (! q.empty()) {
		auto it = q.top();
		q.pop();
		int u = it[1];
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto p : e[u]) {
			int v = p[0], w = p[1];
			if (min[v] > min[u] + w) {
				min[v] = min[u] + w;
				q.push({min[v], v});
			}
		}
	}
	std::cout << min[x] << '\n';
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