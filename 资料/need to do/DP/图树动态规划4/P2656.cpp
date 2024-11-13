#include<bits/stdc++.h>
using i64 = long long;

struct SCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low, bel;
    int cur, cnt;
    
    SCC() {}
    SCC(int n) {
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
    }
    
    void dfs(int x) {
        dfn[x] = low[x] = ++ cur;
        stk.push_back(x);
        
        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                dfs(y);
                low[x] = std::min(low[x], low[y]);
            } else if (bel[y] == -1) {
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
            cnt ++;
        }
    }
    
    std::vector<int> work() {
        for (int i = 1; i <= n; i ++) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }
        return bel;
    }
};

void solve() {
	int n, m;
    std::cin >> n >> m;
    SCC t(n);
    std::vector<std::array<int, 4> > g(m);
    for (int i = 0; i < m; i ++) {
        int u, v, b;
        double w;
        std::cin >> u >> v >> b >> w;
        int W = (int)(w * 10);
        g[i] = {u, v, b, W};
        t.addEdge(u, v);
    }
    auto it = t.work();
    int siz = t.cnt;
    std::vector<int> W(siz);
    std::vector<std::vector<std::array<int, 2> > > e(siz);
    std::map<std::array<int, 2>, int> mp;
    for (int i = 0; i < m; i ++) {
        int u = it[g[i][0]], v = it[g[i][1]], b = g[i][2], w = g[i][3];
        if (u == v) {
            while (b) {
                W[u] += b;
                b = b * w / 10; 
            }
        } else {
            mp[{u, v}] = std::max(mp[{u, v}], b);
        }
    }
    for (auto it : mp) {
        int u = it.first[0], v = it.first[1], b = it.second;
        e[u].push_back({v, b})
;    }
    int s;
    std::cin >> s;
    s = it[s];

    int ans = 0;
    auto dfs = [&](auto self, int u, int res) -> void {
        if (! e[u].size()) {
            ans = std::max(ans, res);
            return ;
        }
        for (auto it : e[u]) {
            int v = it[0], b = it[1];
            self(self, v, res + b + W[v]);
        }
    };
    dfs(dfs, s, W[s]);  
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