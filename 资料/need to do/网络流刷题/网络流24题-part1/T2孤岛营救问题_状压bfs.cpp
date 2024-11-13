#include<bits/stdc++.h>
using i64 = long long;

bool vis[11][11][(1 << 12)];

void solve() {
	int n, m, p, k, s;
	std::cin >> n >> m >> p >> k;
	std::map<std::array<int, 4>, int> mp;
	std::map<std::array<int, 2>, std::vector<int> > pas;
	for (int i = 0; i < k; i ++) {
		int a, b, c, d, g;
		std::cin >> a >> b >> c >> d >> g;
		if (g == 0) g --;
		mp[{a, b, c, d}] = mp[{c, d, a, b}] = g;
	}
	std::cin >> s;
	for (int i = 0; i < s; i ++) {
		int x, y, p;
		std::cin >> x >> y >> p;
		pas[{x, y}].push_back(p);
	}

	// bfs
	int dx[4] = {0, 0, 1, -1};
	int dy[4] = {1, -1, 0, 0};

	std::queue<std::array<int, 4>> q;
	int now = 0;
	for (int i = 0; i < pas[{1, 1}].size(); i ++) {
		now |= (1 << (pas[{1, 1}][i]));
	}
	vis[1][1][now] = 1;
	q.push({1, 1, 0, now});
	while (! q.empty()) {
		auto it = q.front(); q.pop();
		if (it[0] == n && it[1] == m) {
			std::cout << it[2] << '\n';
			return ;
		}

		for (int i = 0; i < 4; i ++) {
			int x = it[0] + dx[i], y = it[1] + dy[i];
			if (x <= 0 || x > n || y <= 0 || y > m) continue;
			int t = mp[{it[0], it[1], x, y}];
			if (t == -1) continue;
			if (t != 0 && (it[3] & (1 << t)) == 0) continue;

			int nw = it[3];
			for (int j = 0; j < pas[{x, y}].size(); j ++) {
				nw |= (1 << pas[{x, y}][j]);
			}
			if (vis[x][y][nw]) continue;
			vis[x][y][nw] = 1;
			q.push({x, y, it[2] + 1, nw});
		}
	}
	std::cout << -1 << '\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}