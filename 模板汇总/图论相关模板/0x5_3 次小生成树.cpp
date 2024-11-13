#include<bits/stdc++.h>
using i64 = long long;

struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n + 1);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};
const int N = 2e6 + 10;
struct LCA {  // 倍增
    int n, rt = 1, deep[N], ff[21][N], max[21][N];
    std::vector<std::array<int, 2> > e[N];
    LCA(int n) : n(n) {}
    void dfs(int u, int p) {
        for (auto it : e[u]) {
        	int v = it[0], w = it[1];
            if (v == p) continue;
            deep[v] = deep[u] + 1;

            ff[0][v] = u;
            max[0][v] = w;
            
            dfs(v, u);
        }
    }
    void work() {
    	max[0][rt] = 0;
    	ff[0][rt] = 0;
        dfs(rt, 0);

        for (int i = 1; i <= 20; i ++) {
            for (int j = 1; j <= n; j ++) {
            	int p = ff[i - 1][j];
                ff[i][j] = ff[i - 1][p];
                max[i][j] = max[i - 1][max[i - 1][j] > max[i - 1][p] ? j : p];
            }
        }
    }
    int lca(int u, int v, int w) { // 处理取小于其的最大值，即为第二大值. '=' 为非严格次小生成树
            // if 非严格， 不需要 if 语句，if 语句仅用于处理 != w
    	int res = 0;
        if (deep[u] < deep[v]) std::swap(u, v);
        for (int i = 20; i >= 0; i --) {
            if (deep[u] - deep[v] >= (1 << i)) {
                
                if (max[i][u] < w) res = std::max(res, max[i][u]);
                u = ff[i][u];
            }
        }
        if (u == v) {
            return w - res;
        }
        for (int i = 20; i >= 0; i --) {
            if (ff[i][u] != ff[i][v]) {
            	if (max[i][u] < w) res = std::max(res, max[i][u]);
            	if (max[i][v] < w) res = std::max(res, max[i][v]);
                u = ff[i][u], v = ff[i][v];
            }
        }
        if (max[0][u] < w) res = std::max(res, max[0][u]);
        if (max[0][v] < w) res = std::max(res, max[0][v]);
        u = ff[0][u];
        return w - res;
    }
};

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::array<int, 3> > e(m);
	std::vector<bool> used(m);

	for (int i = 0; i < m; i ++) {
		std::cin >> e[i][0] >> e[i][1] >> e[i][2];
	}
	std::sort(e.begin(), e.end(), [&](auto a, auto b) {
		return a[2] < b[2];
	});
	
	DSU dsu(n);
	LCA lca(n);

	i64 sum = 0;
	for (int i = 0, num = 1; num < n && i < m; i ++) {
		int u = e[i][0], v = e[i][1], w = e[i][2];
		if (dsu.same(u, v)) continue;
		sum += w;
		//
		lca.e[u].push_back({v, w});
		lca.e[v].push_back({u, w});

		dsu.merge(u, v);
		num ++;
		used[i] = 1;
	}

	lca.work();
	i64 ans = 1e18;
	for (int i = 0; i < m; i ++) {
		if (used[i] || e[i][0] == e[i][1]) continue;
		ans = std::min(ans, sum + lca.lca(e[i][0], e[i][1], e[i][2]));
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