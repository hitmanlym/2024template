#include<bits/stdc++.h>
using i64 = long long;
#define u64 unsigned long long
#define int u64
const u64 b = 1331;
u64 h(u64 x) {
    return x * x * x * 1237123 + 19260817;
}
u64 f(u64 x) {
    u64 cur = h(x & ((1ll << 31) - 1)) + h(x >> 31);
    return cur;
}
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int> > e(n + 1);
    for (int i = 1; i <= m; i ++) {
        int x, y;
        std::cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    } 

    if (m == n - 1) {
        std::cout << "YES\n";
        return ;
    }
    if (m > n) {
        std::cout << "NO\n";
        return ;
    }

    i64 ans = 0;
    std::vector<int> dfn(n + 1), onloop(n + 1), loop(n * 2 + 1), fa(n + 1); 
    int timer = 0, cnt;

    auto dfs = [&](auto self, int u, int p) -> void {
        dfn[u] = ++ timer;
        for (auto v : e[u]) {
            if (v == p) continue;
            if (dfn[v]) {
                if (dfn[v] < dfn[u]) continue;
                loop[++ cnt] = v;
                onloop[v] = 1;
                while (v != u) {
                    loop[++ cnt] = fa[v];
                    onloop[fa[v]] = 1;
                    v = fa[v];
                }
            } else {
                fa[v] = u;
                self(self, v, u);
            }
        }
    };
    std::vector<u64> ff(n + 1);
    auto getsubTree = [&](auto self, int u, int p) -> void {
        ff[u] = 1;
        for (auto v : e[u]) {
            if (v == p || onloop[v]) continue;
            self(self, v, u);
            ff[u] = ff[u] + f(ff[v]);
        }
    };
    cnt = 0;
    dfs(dfs, 1, 0);
    std::vector<u64> LOOP(cnt * 2 + 1);
    for (int i = 1; i <= cnt; i ++) {
        getsubTree(getsubTree, loop[i], 0);
        LOOP[i] = ff[loop[i]];
        LOOP[i + cnt] = LOOP[i];
    }
    for (int i = 1; i <= cnt; i ++) {
        if (LOOP[i] != LOOP[i + 2]) {
            std::cout << "NO\n";
            return ;
        }
    }
    std::cout << "YES\n";
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}