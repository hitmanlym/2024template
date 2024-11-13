#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
const int inf = 1e18;
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> ta(n + 1), tb(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> ta[i];
	}
	int ma;
	std::cin >> ma;
	std::vector<std::vector<int> > a(n + 1);
	for (int i = 1; i <= ma; i ++) {
		int u, v;
		std::cin >> u >> v;
		a[u].push_back(v);
	}
	for (int i = 1; i <= n; i ++) {
		std::cin >> tb[i];
	}
	int mb;
	std::cin >> mb;
	std::vector<std::vector<int> > b(n + 1);
	for (int i = 1; i <= mb; i ++) {
		int u, v;
		std::cin >> u >> v;
		b[u].push_back(v);
	}
	int num0 = 0, num1 = 0;
	for (int i = 1; i <= n; i ++) {
		if (ta[i] == 0) num0 ++;
		if (tb[i] == 1) num1 ++;
	}
	if (num0 != num1) {
		std::cout << "NO\n";
		return ;
	}
	if (num0 == n || num0 == 0) {
		std::cout << "YES\n";
		return ;
	}
	if (k > 2) {
		std::cout << "NO\n";
		return ;
	}
	std::set<int> st;
	std::vector<int> cnt(2);
	std::vector<bool> vis(n + 1);
	std::vector<int> d(n + 1, inf);
	std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
	q.push({0, 1});
	d[1] = 0;
	while (! q.empty()) {
		auto it = q.top();
		q.pop();
		int u = it[1];
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto v : a[u]) {
			if (d[v] > d[u] + 1) {
				d[v] = d[u] + 1;
				q.push({d[v], v});
			}
		}
	}
	for (int i = 1; i <= n; i ++) {
		// std::cout << d[i] << ' ';
		if (i != 1 && (ta[i] ^ ta[1])) {
			cnt[d[i] % 2] ++;
		}
	}
	// std::cout << '\n';

	int id = 1;
	for (int i = 1; i <= n; i ++) {
		if (tb[i] != ta[1]) {
			id = i;
			break;
		}
	}
	q.push({0, id});
	d.assign(n + 1, inf);
	d[id] = 0;
	vis.assign(n + 1, 0);
	while (! q.empty()) {
		auto it = q.top();
		q.pop();
		int u = it[1];
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto v : a[u]) {
			if (d[v] > d[u] + 1) {
				d[v] = d[u] + 1;
				q.push({d[v], v});
			}
		}
	}

	// std::cout << cnt[0] << ' ' << cnt[1] << '\n';
	for (int i = 1; i <= n; i ++) {
		if (i != id && (tb[i] ^ tb[id])) {
			cnt[d[i] % 2] --;
		}
	}

	// std::cout << cnt[0] << ' ' << cnt[1] << '\n';

	if (cnt[0] || cnt[1]) {
		std::cout << "NO\n";
	} else {
		std::cout << "YES\n";
	}
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