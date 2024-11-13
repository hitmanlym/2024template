#include<bits/stdc++.h>
using i64 = long long;


std::set<std::pair<int, int>> E;    //割边
struct EBCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low, bel;
    int cur, cnt;
    
    EBCC() {}
    EBCC(int n) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, -1);
        low.resize(n + 1);
        bel.assign(n + 1, -1);
        stk.clear();
        cur = cnt = 0;
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    void dfs(int x, int p) {
        dfn[x] = low[x] = ++ cur;
        stk.push_back(x);
        bool vis = 0;
        for (auto y : adj[x]) {
            if (y == p) {               // 重边
                if (! vis) {
                    vis = 1;
                    continue;
                }
            }
            if (dfn[y] == -1) {
                E.emplace(x, y);
                dfs(y, x);
                low[x] = std::min(low[x], low[y]);
            } else if (bel[y] == -1 && dfn[y] < dfn[x]) {
                E.emplace(x, y);
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        
        if (dfn[x] == low[x]) {
            int y;
            do {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            cnt++;
        }
    }
    
    std::vector<int> work() {
        for (int i = 1; i <=  n; i ++) {
            if (dfn[i] == -1) {
                dfs(i, -1);
            }
        }
        return bel;
    }
    
    struct Graph { // 0 -- (cnt - 1)
        int n;
        std::vector<std::pair<int, int>> edges;
        std::vector<int> siz;   // 点
        std::vector<int> cnte;  // 边
    };
    Graph compress() {
        Graph g;
        g.n = cnt;
        g.siz.resize(cnt);
        g.cnte.resize(cnt);
        for (int i = 1; i <= n; i++) {
            g.siz[bel[i]]++;
            for (auto j : adj[i]) {
                if (bel[i] < bel[j]) {
                    g.edges.emplace_back(bel[i], bel[j]);
                } else if (i < j) {
                    g.cnte[bel[i]]++;
                }
            }
        }
        return g;
    }
};
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

void solve() {
	int n, m;
    std::cin >> n >> m;
    EBCC t(n);
    std::vector<std::array<int, 2> > e, f;
    for (int i = 1; i <= m; i ++) {
        int u, v;
        std::string s;
        std::cin >> u >> v >> s;
        if (s[0] == 'L') {  
            t.addEdge(u, v);
            f.push_back({u, v});
        } else {
            e.push_back({u, v});
        }
    }
    auto bel = t.work();
    int siz = t.cnt; // 0 -- siz - 1
    DSU d(n + 1);
    auto g = t.compress();
    std::vector<std::vector<int> > p(siz);
    for (int i = 1; i <= n; i ++) {
        p[bel[i]].push_back(i);
    }
    int is = n;
    for (int i = 0; i < siz; i ++) {
        for (int j = 1; j < p[i].size(); j ++) {
            if (d.merge(p[i][j - 1], p[i][j])) {
                is --;
            }
        }
    }
    std::vector<std::array<int, 2> > ans;
    for (auto it : e) {
        int u = it[0], v = it[1];
        if (d.merge(u, v)) {
            is --;
            ans.push_back(it);
        }
    }
    for (auto it : f) {
        int u = it[0], v = it[1];
        if (bel[u] == bel[v]) {
            ans.push_back({u, v});
        }
    }
    if (is == 1) {
        std::cout << "YES\n";
        std::cout << ans.size() << '\n';
        for (auto it : ans) {
            std::cout << it[0] << ' ' << it[1] << '\n';
        }
    } else {
        std::cout << "NO\n";
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