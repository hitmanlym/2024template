#include<bits/stdc++.h>
using i64 = long long;
const int N = 2e4 + 100; // 
#define int i64
struct Basis {
    std::vector<i64> a;
    int n;
    int basecnt;
    Basis() {
        this -> n = 61;
        a.assign(61, 0);
    }
    void insert(i64 x) {
        for (int i = n - 1; i >= 0; i --) {
            if (! (x >> i & 1)) continue;
            if (a[i]) x ^= a[i];
            else {
                for (int j = 0; j < i; j ++) {
                    if (a[j] && (x >> j & 1)) {
                        x ^= a[j];
                    }
                }
                for (int j = i + 1; j < n; j ++) {
                    if (a[j] >> i & 1) {
                        a[j] ^= x;
                    }
                }
                a[i] = x;
                basecnt ++;
                break;
            }
        }
    }
    i64 query_max() {
        i64 res = 0;
        for (int i = 0; i < n; i ++) {
            res ^= a[i];
        }
        return res;
    }
    void mergeFrom(const Basis &other) {
        for (int i = 0; i < n; i ++) {
            int it = other.a[i];
            if (it) insert(it);
        }
    }
    friend Basis operator +(const Basis &a, const Basis &b) {
        Basis res = a;
        int X = res.n;
        for (int i = 0; i < X; i ++) {
            int it = b.a[i];
            if (it) res.insert(it);
        }
        return res;
    } // 用于线段树维护线性基
}b[16][N]; // 结构体内尽量不要定义结构体，内存对齐很危险

i64 a[N];
struct LCA {  // 倍增
    int n, rt = 1, deep[N], ff[16][N], dn = 0;
    std::vector<int> e[N];
    LCA(int n) : n(n) {}
    void dfs(int u, int p) {
        ff[0][u] = p;
        b[0][u].insert(a[u]);
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
                b[i][j] = b[i - 1][j] + b[i - 1][ff[i - 1][j]];
            }
        }
    }
    int lca(int u, int v) {
        if (deep[u] < deep[v]) std::swap(u, v);
        Basis res;
        for (int i = 15; i >= 0; i --) {
            if (deep[u] - deep[v] >= (1 << i)) {
                res.mergeFrom(b[i][u]);
                u = ff[i][u];
            }
        }
        if (u == v) {
            res.mergeFrom(b[0][u]);
            return res.query_max();
        }
        for (int i = 15; i >= 0; i --) {
            if (ff[i][u] != ff[i][v]) {
                res.mergeFrom(b[i][u]);
                res.mergeFrom(b[i][v]);
                u = ff[i][u], v = ff[i][v];
            }
        }
        res.mergeFrom(b[0][u]);
        res.mergeFrom(b[0][v]);
        u = ff[0][u];
        res.mergeFrom(b[0][u]);
        return res.query_max();
    }
};
void solve() {
    int n, q;
    //std::cin >> n >> q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i ++) {
        scanf("%lld", &a[i]);
        //std::cin >> a[i];
    }
    LCA t(n);
    for (int i = 1; i < n; i ++) {
        int u, v;
        scanf("%d%d", &u, &v);
        t.e[u].push_back(v);
        t.e[v].push_back(u);
    }
    t.work();
    while (q --) {
        int u, v;
        scanf("%d%d", &u, &v);
        i64 ans = t.lca(u, v);
        std::cout << ans << '\n';
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