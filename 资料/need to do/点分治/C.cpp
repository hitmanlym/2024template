#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n; 
	std::cin >> n;
	std::vector<std::vector<std::array<int, 2 > > > e(n + 1);
	for (int i = 1; i < n; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	} 
	int ans = n;
	
	std::vector<int> r(3);

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
		qdis[++ qdis[0]] = dis[u] % 3;
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
				int op = qdis[i];
				int need = (3 - op) % 3;
				ans += 2 * r[need];
			}
			for (int i = 1; i <= qdis[0]; i ++) { // out of last loop ! will affect
				r[qdis[i]] ++;
				qremove[++ qremove[0]] = qdis[i];
			}
		}
		for (int i = 1; i <= qremove[0]; i ++) {
			r[qremove[i]] --;
		}
	};
	auto dfz = [&](auto self, int u) -> void {
		vis[u] = 1;
		r[0] = 1;
		r[1] = r[2] = 0;
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

	int total = n * n;
	
	int gcd = std::__gcd(total, ans);
	std::cout << ans / gcd << "/" << total / gcd << '\n';
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