#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
using pi3 = std::array<int, 3>;
using pi4 = std::array<int, 4>;
const int inf = 1e16;
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<pi4> > seg(n + 1);
    std::vector<std::vector<pi3> > p(n + 1);
    for (int i = 1; i <= m; i ++) {
        int x, y, l, v;
        std::cin >> x >> y >> l >> v;
        seg[x].push_back({y, y + l - 1, v, i}); // id
    }
    std::vector<pii> link(m + 1);
    std::vector<std::vector<pii> > e(n + m + 1);
    int cnt = 0;
    for (int i = 1; i <= n; i ++) {
        std::sort(seg[i].begin(), seg[i].end());
        int r = 0;
        for (auto it : seg[i]) {
            p[i].push_back({r, it[0], ++ cnt});
            r = it[1];
        }
        p[i].push_back({r, inf, ++ cnt});
        for (int j = 0; j + 1 < p[i].size(); j ++) {
            int u = p[i][j][2], v = p[i][j + 1][2], w = seg[i][j][2];
            e[u].push_back({v, w});
            e[v].push_back({u, w});
            link[seg[i][j][3]] = {p[i][j][2], p[i][j + 1][2]};
        }
        if (i != 1) {
            int x = 0, y = 0;
            while (x < p[i - 1].size() && y < p[i].size()) {
                if (p[i - 1][x][1] < p[i][y][1]) {
                    if (p[i - 1][x][1] > p[i][y][0]) {
                        int u = p[i - 1][x][2], v = p[i][y][2], w = 0;
                        e[u].push_back({v, w});
                        e[v].push_back({u, w});
                    }
                    x ++;
                } else {
                    if (p[i - 1][x][0] < p[i][y][1]) {
                        int u = p[i - 1][x][2], v = p[i][y][2], w = 0;
                        e[u].push_back({v, w});
                        e[v].push_back({u, w});
                    }
                    y ++;
                }
            }
        }
    }
    int s = 1, t = cnt;
    auto dijik = [&](int s) -> std::vector<int> {
        std::vector<int> d(cnt + 1, inf);
        d[s] = 0;
        std::vector<bool> vis(cnt + 1);
        std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
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
        return d;
    };
    auto pre = dijik(s);
    auto suf = dijik(t);/*
    for (int i = 1; i <= cnt; i ++) {
        std::cout << pre[i] << ' ';
    }
    std::cout << '\n';
    for (int i = 1; i <= cnt; i ++) {
        std::cout << suf[i] << ' ';
    }
    std::cout << '\n';*/
    for (int i = 1; i <= m; i ++) {
        int l = link[i][0], r = link[i][1];
        int ans = std::min({pre[t], pre[l] + suf[r], pre[r] + suf[l]});
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