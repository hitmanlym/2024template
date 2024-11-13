#include<bits/stdc++.h>
using i64 = long long;

const int inf = 1e9 + 7;

struct Diameter {
	int n;
	std::vector<std::vector<std::array<int, 2>>> adj;
	std::vector<int> dis, pre, nxt, fa, diam; 
	std::vector<bool> vis;
	int c, cnt;
	Diameter() {}
	Diameter(int n) {
		init(n);
	}
	void init(int n) {
		this -> n = n;
		adj.assign(n + 1, {});
		dis.assign(n + 1, 0);
		fa.assign(n + 1, 0);
		vis.assign(n + 1, false);
		diam.assign({});
		pre.assign({});//pre 到 0 端距离 
		nxt.assign({});//nxt 到 cnt - 1 端距离
		c = cnt = 0;
	}
	void addEdge(int u, int v, int w = 1) {
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	void dfs(int u, int p) {
		fa[u] = p;
		for (auto it : adj[u]) {
			int v = it[0], w = it[1];
			if (v == p || vis[v]) continue;
			dis[v] = dis[u] + w;
			if (dis[v] > dis[c]) {
				c = v;
			}
			dfs(v, u);
		}
	}

	std::vector<int> get_diameter() {
		dfs(1, 0);
		dis[c] = 0;
		dfs(c, 0);
		for (int i = c; i; i = fa[i]) {
			diam.push_back(i);
			pre.push_back(dis[i]);
			nxt.push_back(0);
		}
		std::reverse(diam.begin(), diam.end());
		std::reverse(pre.begin(), pre.end());
		cnt = diam.size();
		for (int i = cnt - 1; i >= 0; i --) {
			nxt[i] = pre[cnt - 1] - pre[i];
		}
		return diam;
	}
	std::vector<int> getPre() {
		return pre;
	}
	std::vector<int> getNxt() {
		return nxt;
	}
};

void solve() {
	int n, m;
	std::cin >> n >> m;
	Diameter o(n);
	for (int i = 1; i < n; i ++) {
		int x, y, z;
		std::cin >> x >> y >> z;
		o.addEdge(x, y, z);
	}
	auto d = o.get_diameter();
	auto pre = o.getPre();
	auto nxt = o.getNxt();
	int cnt = o.cnt;
	
	for (int i = 0; i < cnt; i ++) {
        o.vis[d[i]] = true;
    }
    int maxd = 0;
    for (int i = 0; i < cnt; i ++) {
        o.dis[d[i]] = 0, o.c = 0;
        o.dfs(d[i], 0);
        maxd = std::max(maxd, o.dis[o.c]);  //节外之枝
    }
    int l = 0, r = 0, ans = inf;
    for (; l < cnt; l ++) {
        while (r + 1 < cnt && pre[r + 1] - pre[l] <= m) r ++;
        ans = std::min(ans, std::max(std::max(pre[l], nxt[r]), maxd));
    } 
    std::cout << ans << '\n';
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