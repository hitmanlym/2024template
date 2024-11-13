#include <bits/stdc++.h> //dfn -- >lca !!!
using i64 = long long;

const int N = 1e4 + 10;

struct LCA {  // 倍增
    int n, rt = 1, deep[N], ff[16][N];
    std::vector<int> e[N];
    LCA(int n) : n(n) {}
    void dfs(int u, int p) {
        ff[0][u] = p;
        for (auto v : e[u]) {
            if (v == p) continue;
            deep[v] = deep[u] + 1;
            dfs(v, u);
        }
    }
    void work() {
        dfs(rt, 0);
        for (int i = 1; i <= 15; i ++) {
            for (int j = 1; j <= n; j ++) {
                ff[i][j] = ff[i - 1][ff[i - 1][j]];
            }
        }
    }
    int lca(int u, int v) {
        if (deep[u] < deep[v]) std::swap(u, v);
        for (int i = 15; i >= 0; i --) {
            if (deep[u] - deep[v] >= (1 << i)) {
                u = ff[i][u];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = 15; i >= 0; i --) {
            if (ff[i][u] != ff[i][v]) {
                u = ff[i][u], v = ff[i][v];
            }
        }
        u = ff[0][u];
        return u;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, rt;
    std::cin >> n >> m >> rt;
    LCA t(n);
    t.rt = rt;
    for (int i = 1; i < n; i ++) {
        int u, v;
        std::cin >> u >> v;
        t.e[u].push_back(v);
        t.e[v].push_back(u);
    }
    t.work();
    for (int i = 1; i <= m; i ++) {
        int u, v;
        std::cin >> u >> v;
        std::cout << t.lca(u, v) << "\n";
    }
	return 0;
}
