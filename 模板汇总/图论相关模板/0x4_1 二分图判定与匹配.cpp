#include<bits/stdc++.h>
using i64 = long long;

struct BipartGraph {
	int n, cnt, ans, nx, ny;
	std::vector<std::vector<int>> adj;
	std::vector<int> col;
	//------------------------------------
	std::vector<int> link;
	std::vector<bool> vis;
	
	BipartGraph() {}

	void init1(int n) {
		this -> n = n;
		adj.assign(n + 1, {});
		col.assign(n + 1, 0);
		cnt = 0;
	}

	void addEdge1(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	bool bipart(int u) {
		for (auto v : adj[u]) {
			if (col[v] == col[u]) {
				return false;
			}
			if (col[v] == 0) {
				col[v] = 3 - col[u];
				if (! bipart(v)) return false;
			}
		}
		return true;
	}

	bool check_bipart() {
		bool f = 1;
		for (int i = 1; i <= n; i ++) {
			if (col[i] == 0) {
				cnt ++;
				col[i] = 1;
				if (! bipart(i)) {
					f = 0;
				}
			}
		}
		return f;
	}

	//----------------------------------------------------

	void init2(int nx, int ny) {
		this -> nx = nx;
		this -> ny = ny;
		adj.assign(nx + 1, {});
		link.assign(ny + 1, -1);
		vis.assign(nx + 1, false);
		ans = 0;
	}
	void addEdge2(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	bool dfs(int u) {
		for (auto v : adj[u]) {
			if (vis[v]) continue;
			vis[v] = true;
			if (link[v] == 0 || dfs(link[v])) {
				link[v] = u;
				return true;
			}
		}
		return false;
	}
	int Maxans() {
		for (int i = 1; i <= nx; i ++) {
			std::fill(vis.begin(), vis.end(), false);
			if (dfs(i)) ans ++;
		}
		return ans;
	}
};
void solve(int o) {
	int n, m, s;
	std::cin >> n >> m >> s;
	std::vector<int> f(n + 1);
	auto find = [&](auto self, int x) -> int {
        return x == f[x] ? x : f[x] = self(self, f[x]);
    };
    for (int i = 1; i <= n; i ++) {
    	f[i] = i;
    }
	s ++;
	BipartGraph g;
	g.init1(n);

	for (int i = 0; i < m; i ++) {
		int u, v;
		std::cin >> u >> v;
		u ++, v ++;
		g.addEdge1(u, v);
		int x = find(find, u), y = find(find, v);
		if (x != y) {
			f[x] = y;
		}
	}
	g.col[s] = 1;
	bool fa = g.bipart(s);

	g.check_bipart();
	int cnt = 0;
	for (int i = 1; i <= n; i ++) {
		if (find(find, i) == i) cnt ++;
	}

	std::cout << "Case " << o << ": ";
	if (cnt == 1 && fa == 0) {
		std::cout << "YES\n";
	} else {
		std::cout << "NO\n";
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1, o = 0;
	std::cin >> t;
	while (t --) {
		o ++;
		solve(o);
	}
	return 0;
}