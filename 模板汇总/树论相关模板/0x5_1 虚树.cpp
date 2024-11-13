#include <bits/stdc++.h> //dfn -- >lca !!!
using i64 = long long;
#define int i64
const int N = 1e6 + 10, mod = 998244353, inf = 1e18 + 10;

struct Xushu {
    int n, rt = 1, dn, res = 0, num = 0;
    int ff[20][N];
    struct node {
        int to, nxt, val;
    };
    std::vector<std::vector<int> > H;
    std::vector<int> dp, col, dfn, h;
    std::vector<node> e;

    std::vector<int> min; // flex

    Xushu(int n) {
        H.assign(n + 1, {});
        dn = 0;
        this -> n = n;
        h.assign(n + 1, 0);
        col.assign(n + 1, 0);
        dp.assign(n + 1, 0);
        dfn.assign(n + 1, 0);
        e.assign(2 * (n + 1), (node){0, 0});
        min.assign(n + 1, inf);
    }
    void addEdge(int a, int b, int w = 1) {
        e[++ num] = {b, h[a], w}; h[a] = num;
        e[++ num] = {a, h[b], w}; h[b] = num;
    }

    void dfs(int u, int p) {
        ff[0][dfn[u] = ++ dn] = p;
        for (int  i = h[u]; i; i = e[i].nxt) {
            if (e[i].to == p) continue;

            min[e[i].to] = std::min(min[u], e[i].val); // flex

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

    void build(std::vector<int> a) {
        int nn = a.size();
        std::sort(a.begin(), a.end(), [&](int x, int y) {
            return dfn[x] < dfn[y];
        });

        for (int i = 0; i + 1 < nn; i ++) {
            a.push_back(lca(a[i], a[i + 1]));
        }
        a.push_back(1);

        std::sort(a.begin(), a.end(), [&](int x, int y) {
            return dfn[x] < dfn[y];
        });
        a.erase(std::unique(a.begin(), a.end()), a.end());
        int o = a.size();
        for (int i = 0; i + 1 < o; i ++) {
            H[lca(a[i], a[i + 1])].push_back(a[i + 1]);
        }
    }

    void DFS(int u, int color) {
        int sum = 0;
        for (auto v : H[u]) {
            DFS(v, color);
            sum += dp[v];
        }
        if (col[u] == color) {
            dp[u] = min[u];
        } else {
            dp[u] = std::min(sum, min[u]);
        }
    }
    void solve(int cl) {
        DFS(1, cl);
        auto CLEAR = [&](auto self, int u) -> void {
            for (auto v : H[u]) self(self, v);
            H[u].clear();
        };
        CLEAR(CLEAR, 1);
    }
};
void solve() {
    int n;
    std::cin >> n;
    Xushu t(n);
    for (int i = 1; i < n; i ++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        t.addEdge(u, v, w);
    }
    t.work();
    int m;
    std::cin >> m;
    while (m --) {
        int k;
        std::cin >> k;
        std::vector<int> a(k);  
        for (int i = 0; i < k; i ++) {
            std::cin >> a[i];
            t.col[a[i]] = m + 1;
        }
        t.build(a);
        t.solve(m + 1);
        std::cout << t.dp[1] << '\n';
    }
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
