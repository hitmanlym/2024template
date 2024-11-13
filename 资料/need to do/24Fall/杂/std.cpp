#include <bits/stdc++.h>
using i64 = long long;
struct data {
    int u, cnt;
    friend bool operator < (data a, data b) {
        return (a.cnt == b.cnt) ? a.u > b.u : a.cnt < b.cnt;
    }
    friend data operator + (data a, data b) {
        return (data){a.u, a.cnt + b.cnt};
    }
};
const int N = 1e5;
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int> > e(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    std::vector<std::vector<data> > on(n + 1);
    int cnt = n; // 已经有 n 个节点
    std::vector<std::array<int, 2> > c(n * 128 + 1);
    std::vector<data> t(n * 128 + 1);
    auto insert = [&](auto self, int u, int l, int r, data x) -> void {
        if (l == r) { t[u] = x + t[u]; return ; }
        int mid = l + r >> 1;
        if (x.u <= mid) self(self, c[u][0] = c[u][0] ? c[u][0] : ++ cnt, l, mid, x);
        else self(self, c[u][1] = c[u][1] ? c[u][1] : ++ cnt, mid + 1, r, x);
        t[u] = std::max(t[c[u][0]], t[c[u][1]]);
    };
    auto merge = [&](auto self, int u1, int u2, int l, int r) -> void {
        if (l == r) { t[u1] = t[u1] + t[u2]; return ; }
        int mid = l + r >> 1;
        if (c[u1][0] && c[u2][0]) { self(self, c[u1][0], c[u2][0], l, mid); } 
        else if (c[u2][0]) { c[u1][0] = c[u2][0]; }
        if (c[u1][1] && c[u2][1]) { self(self, c[u1][1], c[u2][1], mid + 1, r); } 
        else if (c[u2][1]) { c[u1][1] = c[u2][1]; }
        t[u1] = std::max(t[c[u1][0]], t[c[u1][1]]);
    };

    std::vector<std::vector<int> > fa(19, std::vector<int>(n + 1));
    std::vector<int> dep(n + 1);
    auto dfs1 = [&](auto self, int u, int p) -> void {
        fa[0][u] = p;
        dep[u] = dep[p] + 1;
        for (auto v : e[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
    };
    dfs1(dfs1, 1, 0); 
    for (int j = 1; j <= 18; j ++) {
        for (int i = 1; i <= n; i ++) {
            fa[j][i] = fa[j - 1][fa[j - 1][i]];
        }
    }
    auto lca = [&](int u, int v) -> int {
        if (dep[u] < dep[v]) std::swap(u, v);
        for (int d = dep[u] - dep[v], i = 18; i >= 0; i --) {
            if (d >> i & 1) u = fa[i][u];
        }
        if (u == v) return u;
        for (int i = 18; i >= 0; i --) {
            if (fa[i][u] != fa[i][v]) {
                u = fa[i][u], v = fa[i][v];
            }
        }
        return fa[0][u];
    };
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        int o = lca(u, v);
        on[u].push_back((data){w, 1});
        on[v].push_back((data){w, 1});
        on[o].push_back((data){w, -1});
        on[fa[0][o]].push_back((data){w, -1});
    }
    std::vector<int> ans(n + 1);
    auto dfs2 = [&](auto self, int u) -> void {
        for (auto v : e[u]) {
            if (v == fa[0][u]) continue;
            self(self, v);
            merge(merge, u, v, 0, N);
        }
        for (auto it : on[u]) {
            insert(insert, u, 0, N, it);
        }
        ans[u] = t[u].u;
    };
    dfs2(dfs2, 1);
    for (int i = 1; i <= n; i ++) {
        std::cout << ans[i] << '\n';
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t--) {
        solve();
    }
}