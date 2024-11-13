#include<bits/stdc++.h>
using i64 = long long;



struct VBCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low;
    int cur, cnt;
    std::vector<std::vector<int>> ans;
    VBCC() {}
    VBCC(int n) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, -1);
        low.resize(n + 1);
        stk.clear();
        cur = 0;
        cnt = 0;
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    void dfs(int x) {
        dfn[x] = low[x] = ++ cur;
        stk.push_back(x);

        if (! adj[x].size()) {
            ans.push_back({});
            ans[cnt].push_back(x);
            cnt ++;
            return ;
        } 
        
        for (auto y : adj[x]) {
            if (dfn[y] != -1) {
                low[x] = std::min(low[x], dfn[y]);
            } else {
                dfs(y);
                if (low[y] >= dfn[x]) {
                    ans.push_back({});
                    ans[cnt].push_back(x);
                    int z;
                    do {
                        z = stk.back();
                        ans[cnt].push_back(z);
                        stk.pop_back();
                    } while (z != y);
                    ++ cnt;
                 } else {
                    low[x] = std::min(low[x], low[y]);
                }
            }
        }
    }
    
    std::vector<std::vector<int>> work() {
        for (int i = 1; i <= n; i ++) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }
        return ans;
    }
};


void solve() {
	int n, m;
    std::cin >> n >> m;
    VBCC t(n);
    for (int i = 0; i < m; i ++) {
        int u, v;
        std::cin >> u >> v;
        if (u == v) continue;
        t.addEdge(u, v);
    }
    auto it = t.work();
    int cnt = t.cnt;
    std::cout << cnt << '\n';
    for (int i = 0; i < cnt; i ++) {
        std::cout << it[i].size() << ' ';
        for (auto x : it[i]) {
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