#include<bits/stdc++.h>
using i64 = long long;
#define int i64
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

const int N = 1e4 + 10;

struct LCA {
    int n, rt = 1, dfn[N], ff[20][N], dn;
    struct {
        int to, nxt;
    } e[N * 2];
    int h[N], num = 0;

    LCA(int n) : n(n) {}
    void addEdge(int a, int b) {
        e[++ num] = {b, h[a]}; h[a] = num;
        e[++ num] = {a, h[b]}; h[b] = num;
    }

    void dfs(int u, int p) {
        ff[0][dfn[u] = ++ dn] = p;
        for (int  i = h[u]; i; i = e[i].nxt) {
            if (e[i].to == p) continue;
            dfs(e[i].to, u);
        }
    }
    int get(int x, int y) {
        if (dfn[x] < dfn[y]) return x;
        else return y;
    }
    void work() {
        dfs(rt, 0);
        for (int i = 1; i <= std::__lg(n); i ++) { //RMQ deep less
            for (int j = 1; j + (1 << i) - 1 <= n; j ++) {
                ff[i][j] = get(ff[i - 1][j], ff[i - 1][j + (1 << i - 1)]);
            }
        }
    }
    int lca(int u, int v) {
        if (u == v) {
            return u;
        } 
        if ((u = dfn[u]) > (v = dfn[v])) std::swap(u, v);
        int d = std::__lg(v - u);
        return get(ff[d][++ u], ff[d][v - (1 << d) + 1]);
    }
};

void solve() { // Kruskal 重构树，类似于哈夫曼树，原树任两点lca 的点为其路径上最大值所代表的点
	int n, m;
	std::cin >> n >> m;
	std::vector<std::array<int, 4> > e(m);
	for (int i = 0; i < m; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		e[i] = {w, u, v, i + 1};
	}
	std::sort(e.begin(), e.end());

	int sum = 0;
	DSU dsu(2 * n - 1);
	LCA t(2 * n - 1);
	int cnt = n;
	std::vector<int> ans(m + 1);
	std::vector<int> wt(2 * n);

	for (auto it : e) {
		int w = it[0], u = it[1], v = it[2], id = it[3];

		if (! dsu.same(u, v)) {
			++ cnt;
			t.addEdge(cnt, dsu.find(u));
			t.addEdge(cnt, dsu.find(v));
			dsu.merge(cnt, u);
			dsu.merge(cnt, v);

			wt[cnt] = w;
			sum += w;
		}
	}
	t.rt = 2 * n - 1;
	t.work();

	for (auto it : e) {
		int w = it[0], u = it[1], v = it[2], id = it[3];

		ans[id] = sum - wt[t.lca(u, v)] + w;
	}
	for (int i = 1; i <= m; i ++) {
		std::cout << ans[i] << '\n';
	}
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}