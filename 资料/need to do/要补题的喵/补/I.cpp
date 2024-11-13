#include<bits/stdc++.h>
using i64 = long long;
using db = long double;
using pii = std::array<int, 2>;
void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<pii> > e(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }
    std::vector<db> dp(n + 1), fix(n + 1);
    auto dfs = [&](auto self, int u, int p, int num, int len, int player) -> void {
        bool s = 0;
        if (u == 1) {
            fix[u] = 1e18;
        } else {
            fix[u] = 1.0 * num / len;
        }
        if (player) {
            dp[u] = 1e18;
        } else {
            dp[u] = 0;
        }
        for (auto it : e[u]) {
            int v = it[0], w = it[1];
            if (v == p) continue;
            s = 1;
            self(self, v, u, num + w, len + 1, player ^ 1);
            if (player) {
                dp[u] = std::min(dp[u], dp[v]);
            } else {
                dp[u] = std::max(dp[u], dp[v]);
            }
        }
        if (! s) {
            dp[u] = fix[u];
        } else {
            dp[u] = std::min(dp[u], fix[u]);
        }
    };
    dfs(dfs, 1, 0, 0, 0, 0);
    std::cout << std::fixed << std::setprecision(15) << dp[1] << '\n';
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