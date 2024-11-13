#include<bits/stdc++.h>
using i64 = long long;
const int inf = 1e9;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int> > e(n + 1);
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	std::queue<int> q;
	std::vector<int> d(n + 1, inf), cnt(n + 1);
	for (int i = 1; i <= m; i ++) {
		int o;
		std::cin >> o;
		q.push(o);
		d[o] = 0;
		cnt[o] = 1;
	}
	while (! q.empty()) {
		int u = q.front();
		q.pop();
		for (auto v : e[u]) {
			if (d[v] == d[u] + 1) {
				cnt[v] += cnt[u];
			} else if (d[v] > d[u] + 1) {
				d[v] = d[u] + 1;
				cnt[v] = cnt[u];
				q.push(v);
			}
		}
	}
	for (int i = 1; i <= n; i ++) {
		if (cnt[i] == m) {
			std::cout << "YES\n" << i << '\n';
			return ;
		}
	}
	std::cout << "NO\n";
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