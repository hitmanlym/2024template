#include <bits/stdc++.h> //dfn -- >lca !!!
using i64 = long long;

const int N = 1e4 + 10;

struct LCA {
    int n, rt = 1, dfn[N], ff[20][N], dn;
    struct {
        int to, nxt;
    } e[N * 2];
    int h[N], num = 0;

    LCA(int n) : n(n + 1) {}
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
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    LCA t(n);
    for (int i = 1; i < n; i ++) {
        int u, v;
        std::cin >> u >> v;
        t.addEdge(u, v);
    }
    t.work();

	return 0;
}
