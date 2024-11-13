#include<bits/stdc++.h>
using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::array<int, 2> > E(m + 1);
    std::vector<std::vector<int> > e(n + 1);

    std::vector<int> d(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
        E[i] = {u, v};
        d[u] ++;
        d[v] ++;
    }
    std::vector<std::vector<int> > p(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u = E[i][0], v = E[i][1];
        if ((d[u] == d[v] && u > v) || d[u] < d[v]) {
            std::swap(u, v);
        }
        p[u].push_back(v);
    }

    i64 num = 0;
    std::vector<bool> vis(n + 1);
    for (int u = 1; u <= n; u ++) {
        for (auto v : p[u]) {
            vis[v] = 1;
        }

        for (auto v : p[u]) {
            for (auto w : p[v]) {
                if (vis[w]) num ++;
            }
        }

        for (auto v : p[u]) {
            vis[v] = 0;
        }
    }
    std::cout << num << '\n';
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