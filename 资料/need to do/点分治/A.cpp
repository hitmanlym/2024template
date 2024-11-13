#include<bits/stdc++.h>
using i64 = long long;
const int N = 1e7 + 1;
void solve() {
	int n, m; 
	std::cin >> n >> m;
	std::vector<std::vector<std::array<int, 2 > > > e(n + 1);
	for (int i = 1; i < n; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	} 
	std::vector<int> ans(m + 1), qs(m + 1);
	std::vector<bool> have(N);
	for (int i = 1; i <= m; i ++) {
		std::cin >> qs[i];
	}

	std::vector<int> siz(n + 1), maxp(n + 1); // son.max
	int rt, sum = n;
	maxp[rt = 0] = n;
	std::vector<bool> vis(n + 1);


	auto getRoot = [&](auto self, int u, int p) -> void {
		siz[u] = 1;
		maxp[u] = 0;
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			if (v == p || vis[v]) continue;
			self(self, v, u);
			siz[u] += siz[v];
			maxp[u] = std::max(maxp[u], siz[v]);
		}
		maxp[u] = std::max(maxp[u], sum - siz[u]);
		if (maxp[u] < maxp[rt]) rt = u;
	};
	std::vector<int> dis(n + 1);
	std::vector<int> qdis(n + 1), qremove(n + 1);
	auto getDis = [&](auto self, int u, int p) -> void {
		qdis[++ qdis[0]] = dis[u];
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			if (v == p || vis[v]) continue;
			dis[v] = dis[u] + w;
			self(self, v, u);
		}
	};
	auto calc = [&](int u) -> void {
		qremove[0] = 0;
		int p = 0;
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			if (vis[v]) continue;
			dis[v] = w;
			qdis[0] = 0;
			getDis(getDis, v, u);
			for (int i = 1; i <= qdis[0]; i ++) {
				for (int j = 1; j <= m; j ++) {
					if (qdis[i] <= qs[j]) {
						ans[j] |= have[qs[j] - qdis[i]];
					}
				}
			}
			for (int i = 1; i <= qdis[0]; i ++) { // out of last loop ! will affect
				if (qdis[i] < N) {
					have[qdis[i]] = 1;
					qremove[++ qremove[0]] = qdis[i];
				}
			}
		}
		for (int i = 1; i <= qremove[0]; i ++) {
			have[qremove[i]] = 0;
		}
	};
	auto dfz = [&](auto self, int u) -> void {
		vis[u] = 1;
		have[0] = 1;
		calc(u);
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			if (vis[v]) continue;
			sum = siz[v];
			maxp[rt = 0] = siz[v];
			getRoot(getRoot, v, 0);
			self(self, rt);        // !!! rt
		}
	};
	getRoot(getRoot, 1, 0);
	dfz(dfz, rt);
	for (int i = 1; i <= m; i ++) {
		if (ans[i]) {
			std::cout << "AYE\n";
		} else {
			std::cout << "NAY\n";
		}
	}
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