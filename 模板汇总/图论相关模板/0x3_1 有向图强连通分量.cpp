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
	for (int i = 0; i < m; i ++) {
		int u, v;
		std::cin >> u >> v;
		t.addEdge(u, v);
	}
	auto it = t.work();
	int max = t.cnt - 1;
	std::vector<std::vector<int> > v(max + 1);
	for (int i = 1; i <= n; i ++) {
		v[it[i]].push_back(i);
	}
	std::cout << max + 1 << '\n';
	for (int i = 1; i <= n; i ++) {
		if (v[it[i]].size()) {
			for (auto x : v[it[i]]) {
				std::cout << x << ' ';
			}
			std::cout << '\n';
			v[it[i]].resize(0);
		}
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