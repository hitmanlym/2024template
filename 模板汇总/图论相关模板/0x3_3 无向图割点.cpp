#include<bits/stdc++.h>
using i64 = long long;



struct GeDian {
    int n, root;
    std::vector<std::vector<int>> adj;
    std::vector<int> dfn, low;
    std::vector<bool> bel;
    int cur;
    
    GeDian() {}
    GeDian(int n) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, -1);
        low.resize(n + 1);
        bel.assign(n + 1, 0);
        cur = 0;
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    void dfs(int x) {
        dfn[x] = low[x] = ++ cur;
        int ch = 0;
        
        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                ch ++;
                dfs(y);
                low[x] = std::min(low[x], low[y]);
                if (x != root && low[y] >= dfn[x] ) {
                    bel[x] = 1;
                }
            } else {
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        
        if (x == root && ch >= 2) {
            bel[x] = 1;
        }
    }
    
    std::vector<bool> work() {
        for (int i = 1; i <= n; i ++) {
            if (dfn[i] == -1) {
                root = i;
                dfs(i);
            }
        }
        return bel;
    }
};


void solve() {
	int n, m;
    std::cin >> n >> m;
    GeDian t(n);
    for (int i = 0; i < m; i ++) {
        int u, v;
        std::cin >> u >> v;
        t.addEdge(u, v);
    }
    auto it = t.work();
    std::vector<int> ans;
    for (int i = 1; i <= n; i ++) {
        if (it[i]) {
            ans.push_back(i);
        }
    }
    std::cout << ans.size() << '\n';
    for (auto x : ans) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
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