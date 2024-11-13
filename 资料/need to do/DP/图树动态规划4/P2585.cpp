#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	std::string s;
	std::cin >> s;
	int n = s.size();
	std::vector<std::vector<int> > e(n + 1);
	int rt = 1;
	s = " " + s;
	int now = 0;
	auto dfs = [&](auto self, int p) -> void {
		now ++;
		e[p].push_back(now);
		if (s[now] == '0') {
			return ;
		}
		if (s[now] == '1') {
			self(self, now);
			return ;
		}
		if (s[now] == '2') {
			int o = now;
			self(self, o);
			self(self, o);
		}
	};
	dfs(dfs, 0);
	std::vector<std::array<int, 2> > max(n + 1), min(n + 1);
	auto DFS = [&](auto self, int u) -> void {
		max[u][1] = 1;
		min[u][1] = 1;
		for (auto v : e[u]) {
			self(self, v);
		}
		if (e[u].size() == 1) {
			max[u][1] += max[e[u][0]][0];
			max[u][0] += std::max(max[e[u][0]][0], max[e[u][0]][1]);
			min[u][0] += std::min(min[e[u][0]][0], min[e[u][0]][1]);
			min[u][1] += min[e[u][0]][0];
		}
		if (e[u].size() == 2) {
			max[u][1] += max[e[u][0]][0] + max[e[u][1]][0];
			max[u][0] += std::max({max[e[u][0]][1] + max[e[u][1]][0],
							max[e[u][0]][0] + max[e[u][1]][1],
							max[e[u][0]][0] + max[e[u][1]][0]});
			min[u][1] += min[e[u][0]][0] + min[e[u][1]][0];
			min[u][0] += std::min({min[e[u][0]][1] + min[e[u][1]][0],
							min[e[u][0]][0] + min[e[u][1]][1]});
		}
	};
	DFS(DFS, 1);
	std::cout << std::max(max[1][0], max[1][1]) << ' ' << std::min(min[1][0], min[1][1]) << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}