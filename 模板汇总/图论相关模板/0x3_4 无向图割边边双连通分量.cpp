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

void solve() {
	int n, m;
    std::cin >> n >> m;
    EBCC t(n);
    for (int i = 0; i < m; i ++) {
        int u, v;
        std::cin >> u >> v;
        t.addEdge(u, v);
    }
    auto it = t.work();
    int cnt = t.cnt;
    std::cout << cnt << '\n';
    std::vector<std::vector<int> >  v(cnt);
    for (int i = 1; i <= n; i ++) {
        v[it[i]].push_back(i);
        //std::cout << it[i] << ' ';
    }
    for (int i = 0; i < cnt; i ++) {
        std::cout << v[i].size() << ' ';
        for (auto x : v[i]) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
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