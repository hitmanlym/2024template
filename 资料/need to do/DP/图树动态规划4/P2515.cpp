#include<bits/stdc++.h>
using i64 = long long;
#define int i64

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

	std::vector<int> A(n + 1), B(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> A[i];
	}
	for (int i = 1; i <= n; i ++) {
		std::cin >> B[i];
	}
	std::vector<std::array<int, 2> > e;
	for (int i = 0; i < n; i ++) {
		int x;
		std::cin >> x;
		if (x) {
			e.push_back({x, i + 1});
			t.addEdge(x, i + 1);
		}
	}
	auto it = t.work();
	int siz = t.cnt;
	std::vector<int> W(siz + 1), V(siz + 1);
	std::vector<bool> in(siz);
	std::vector<std::set<int> > ww(siz), vv(siz);
	std::vector<std::vector<int> > E(siz + 1);
	for (int i = 0; i < e.size(); i ++) {
		int u = it[e[i][0]], v = it[e[i][1]];
		if (u == v) {
			ww[u].insert(A[e[i][0]]);
			ww[u].insert(A[e[i][1]]);
			vv[u].insert(B[e[i][0]]);
			vv[u].insert(B[e[i][1]]);
		} else {
			E[u].push_back(v);
			in[v] = 1;
			ww[u].insert(A[e[i][0]]);
			vv[u].insert(B[e[i][0]]);
			ww[v].insert(A[e[i][1]]);
			vv[v].insert(B[e[i][1]]);
		}	
	}
	for (int i = 0; i < siz; i ++) {
		for (auto it : ww[i]) W[i] += it;
		for (auto it : vv[i]) V[i] += it;
	}
	
	for (int i = 0; i < siz; i ++) {
		if (! in[i]) {
			E[siz].push_back(i);
		}
	}
	int rt = siz;
	std::vector<std::vector<int> > dp(siz + 1, std::vector<int>(m + 1));

	auto dfs = [&](auto self, int u) -> void {
		for (auto v : E[u]) {
			self(self, v);
			// dp[u][]
			for (int i = m; i >= W[v]; i --) {
				for (int j = i - W[v]; j >= 0; j --) {
					dp[u][i] = std::max({
						dp[u][i],
						dp[u][i - W[v] - j] + dp[v][j] + V[v]
					});
				}
			}
			//std::cout << v << ' ' << V[v] << '\n';
		}
	};
	dfs(dfs, rt);
	int ans = dp[rt][m];
	std::cout << ans << '\n';
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