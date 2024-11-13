#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 998244353;
void solve() {
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    std::vector<std::vector<std::array<int, 2> > > e(n + 1);
    std::vector<std::vector<std::array<int, 2> > > E(n + 1);
    std::vector<std::set<std::array<int, 2> > > st(n + 1);
    std::vector<std::array<int, 3> > b(m);
    std::vector<int> d(n + 1), dp(n + 1);
    for (int i = 0; i < m; i ++) {
        std::cin >> b[i][0] >> b[i][1] >> b[i][2];
        d[b[i][0]] ++;
        d[b[i][1]] ++;
    }
    const int B = std::sqrt(n);

    for (int i = 0; i < m; i ++) {
        int u = b[i][0], v = b[i][1], w = b[i][2];
        E[u].push_back({v, w});
        E[v].push_back({u, w});
        if (d[v] > B) {
            e[u].push_back({v, w});
        } else {
            st[u].insert({dp[v] + w, v});
        }
        if (d[u] > B) {
            e[v].push_back({u, w});
        } else {
            st[v].insert({dp[u] + w, u});
        }
    }
    std::vector<int> z(q + 1);
    for (int i = 1; i <= q; i ++) {
        std::cin >> z[i];
    }
    for (int i = q; i >= 1; i --) {
        int u = z[i];
        int min = 1e16;
        if (st[u].size()) {
            min = (*st[u].begin())[0];
        }
        for (auto it : e[u]) {
            int v = it[0], w = it[1];
            min = std::min(min, dp[v] + w);
        }
        if (d[u] <= B) {
            for (auto it : E[u]) {
                int v = it[0], w = it[1];
                st[v].erase({dp[u] + w, u});
                st[v].insert({min + w, u});
            }
        }
        dp[u] = min;
        // update the set U in.
        // and U's degree must <= B
    }
    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        ans = (ans + 1ll * dp[i] % mod * a[i] % mod) % mod;
    }
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