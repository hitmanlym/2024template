#include<bits/stdc++.h>
using i64 = long long;
using pii = std::array<int, 2>;
void solve() {
	int d, s;
	std::cin >> d >> s;
	std::queue<pii> q;
	std::vector<std::vector<bool> > vis(d + 1, std::vector<bool>(s + 1));
	std::vector<std::vector<pii> > pre(d + 1, std::vector<pii>(s + 1));
	vis[0][0] = 1;
	q.push({0, 0});
	while (! q.empty() && ! vis[0][s]) {
		auto it = q.front();
		q.pop();
		int u = it[0], us = it[1];
		for (int i = 0; i < 10; i ++) {
			int v = (u * 10 + i) % d, vs = us + i;
			if (! vs || vs > s || vis[v][vs]) continue;
			vis[v][vs] = 1;
			q.push({v, vs});
			pre[v][vs] = {u, us};
		}
	}
	if (! vis[0][s]) {
		std::cout << -1 << '\n';
		return ;
	}
	auto print = [&](auto self, int x, int y) -> void {
		if (! y) return ;
		self(self, pre[x][y][0], pre[x][y][1]);
		std::cout << y - pre[x][y][1];
	};
	print(print, 0, s);
	std::cout << '\n';
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