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
    std::vector<int> w(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> w[i];
    }
    SCC t(n);
    std::vector<std::array<int, 2> > g(m);
    for (int i = 0; i < m; i ++) {
        int u, v;
        std::cin >> u >> v;
        t.addEdge(u, v);
        g[i][0] = u, g[i][1] = v;
    }
    auto it = t.work();
    int siz = t.cnt;
    std::vector<int> W(siz);
    std::vector<std::vector<int> > e(siz);
    for (int i = 1; i <= n; i ++) {
        W[it[i]] += w[i];
    }
    std::map<std::pair<int, int>, bool> mp;
    std::vector<int> in(siz);
    for (int i = 0; i < m; i ++) {
        int u = it[g[i][0]], v = it[g[i][1]];
        if (u == v || mp[{u, v}]) continue; // fuck
        mp[{u, v}] = 1;
        e[u].push_back(v);
        in[v] ++;
    }
    std::queue<int> q;
    std::vector<i64> dp(siz);
    for (int i = 0; i < siz; i ++) {
        if (! in[i]) {
            dp[i] = W[i];
            q.push(i);
        }
    }

    while (! q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : e[u]) {
            dp[v] = std::max(dp[v], dp[u] + W[v]);
            in[v] --;
            if (! in[v]) {
                q.push(v);
            }
        }
    }
    i64 ans = 0;
    for (int i = 0; i < siz; i ++) {
        ans = std::max(ans, dp[i]);
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