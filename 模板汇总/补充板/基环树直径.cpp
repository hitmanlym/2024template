#include<bits/stdc++.h>
// 基环树森林直径和
using i64 = long long;
using pii = std::array<i64, 2>;
void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<pii> > e(n + 1);
    for (int i = 1; i <= n; i ++) {
        int x = i, y, w;
        std::cin >> y >> w;
        e[x].push_back({y, w});
        e[y].push_back({x, w});
    } 
    i64 ans = 0;
    i64 max_intree, max_cir;
    std::vector<i64> sum(n * 2 + 1), f(n + 1), g(n + 1);
    std::vector<int> dfn(n + 1), onloop(n + 1), loop(n * 2 + 1), val(n * 2 + 1), len(n + 1), fa(n + 1); 
    int timer = 0, cnt;
    auto dfs = [&](auto self, int u, int p) -> void {
        dfn[u] = ++ timer;
        for (auto it : e[u]) {
            int v = it[0], w = it[1];
            if (v == p) continue;
            if (dfn[v]) {
                if (dfn[v] < dfn[u]) continue;
                loop[++ cnt] = v;
                val[cnt] = w;
                onloop[v] = 1;
                while (v != u) {
                    loop[++ cnt] = fa[v];
                    val[cnt] = len[v];
                    onloop[fa[v]] = 1;
                    v = fa[v];
                }
            } else {
                fa[v] = u;
                len[v] = w;
                self(self, v, u);
            }
        }
    };
    auto getsubTree = [&](auto self, int u, int p) -> void {
        for (auto it : e[u]) {
            int v = it[0], w = it[1];
            if (v == p || onloop[v]) continue;
            self(self, v, u);
            if (f[v] + w > f[u]) {
                g[u] = f[u];
                f[u] = f[v] + w;
            } else if (f[v] + w > g[u]) {
                g[u] = f[v] + w;
            }
        }
        max_intree = std::max(max_intree, f[u] + g[u]);
    };
    auto work = [&](int rt) -> i64 {
        max_cir = max_intree = 0;
        cnt = 0;
        dfs(dfs, rt, 0);
        for (int i = 1; i <= cnt; i ++) {
            getsubTree(getsubTree, loop[i], 0);
            loop[i + cnt] = loop[i];
            val[i + cnt] = val[i];
        }
        for (int i = 1; i <= cnt * 2; i ++) {
            sum[i] = sum[i - 1] + val[i];
        }
        std::deque<pii> q;
        for (int i = 1; i <= cnt * 2; i ++) {
            while (q.size() && q.back()[0] <= i - cnt) {
                q.pop_back();
            }
            if (q.size()) {
                max_cir = std::max(max_cir, q.back()[1] + f[loop[i]] + sum[i]);
            }
            while (q.size() && q.front()[1] < f[loop[i]] - sum[i]) {
                q.pop_front();
            }
            q.push_front({i, f[loop[i]] - sum[i]});
        }
        return std::max(max_cir, max_intree);
    };
    for (int i = 1; i <= n; i ++) {
        if (! dfn[i]) {
            ans += work(i);
        }
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