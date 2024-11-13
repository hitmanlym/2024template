#include<bits/stdc++.h>
using i64 = long long;
using pii = std::array<int, 2>;
const int inf = 1e9 + 7;
void solve() {
    int n, m;
    std::cin >> n >> m;
    int s = 0, t = (n - 1) * (m - 1) * 2 + 1;
    std::vector<std::vector<pii> > e(t + 1);
    {
        for (int i = 1; i < m; i ++) {
            int x;
            std::cin >> x;
            int u = i * 2;
            e[u].push_back({t, x});
        }
        for (int i = 2; i < n; i ++) {
            for (int j = 1; j < m; j ++) {
                int x;
                std::cin >> x;
                int u = (i - 1) * (m - 1) * 2 + 2 * j, v = (i - 2) * (m - 1) * 2 + 2 * j - 1;
                e[u].push_back({v, x});
                e[v].push_back({u, x});
            }
        }
        for (int i = 1; i < m; i ++) {
            int x;
            std::cin >> x;
            int u = (n - 2) * (m - 1) * 2 + 2 * i - 1;
            e[s].push_back({u, x});
        }
    }
    {
        for (int i = 1; i < n; i ++) {
            for (int j = 1; j <= m; j ++) {
                int x;
                std::cin >> x;
                int u = (i - 1) * (m - 1) * 2 + 2 * (j - 1);
                int v = u + 1;
                if (j == 1) {
                    e[s].push_back({v, x});
                } else if (j == m) {
                    e[u].push_back({t, x});
                } else {
                    e[u].push_back({v, x});
                    e[v].push_back({u, x});
                }
            }
        }
    }
    {
        for (int i = 1; i < n; i ++) {
            for (int j = 1; j < m; j ++) {
                int x;
                std::cin >> x;
                int u = (i - 1) * (m - 1) * 2 + 2 * j - 1;
                int v = u + 1;
                e[u].push_back({v, x});
                e[v].push_back({u, x});
            }   
        }
    }

    std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
    std::vector<int> d(t + 1, inf);
    std::vector<bool> vis(t + 1);
    d[s] = 0;
    q.push({d[s], s});
    while (q.size()) {
        auto it = q.top();
        q.pop();
        int u = it[1];
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto op : e[u]) {
            int v = op[0], w = op[1];
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                q.push({d[v], v});
            }
        }
    }
    std::cout << d[t] << '\n';
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