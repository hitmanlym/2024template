#include<bits/stdc++.h>
using i64 = long long;
// 狗日的构造pro

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

void solve() {
	// 2 * i - 1, 2 * i so, the link not get odd circle
	int n;
	std::cin >> n;
	BipartGraph g;
	g.init1(2 * n);
	for (int i = 1; i <= n * 2; i += 2) {
		g.addEdge1(i, i + 1);
	}
	std::vector<std::array<int, 2> > a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i][0] >> a[i][1];
		g.addEdge1(a[i][0], a[i][1]);
	}
	g.check_bipart();
	for (int i = 1; i <= n; i ++) {
		std::cout << g.col[a[i][0]] << ' ' << g.col[a[i][1]] << '\n';
	}
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