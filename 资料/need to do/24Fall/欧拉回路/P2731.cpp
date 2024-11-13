#include<bits/stdc++.h>
using i64 = long long;
using pii = std::array<int, 2>;
const int N = 500;
void solve() {
    int m;
    std::cin >> m;
    std::vector<std::vector<pii> > e(N + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back({v, i});
        e[v].push_back({u, i});
    } 
    int st = 0;
    for (int i = 1; i <= N; i ++) {
        std::sort(e[i].begin(), e[i].end());
        if (e[i].size() && ! st) st = i;
    }
    for (int i = 1; i <= N; i ++) {
        if (e[i].size() & 1) {
            st = i;
            break;
        }
    }
    std::vector<int> cur(N + 1);
    std::vector<bool> vis(m + 1);
    std::vector<int> res;
    auto dfs = [&](auto self, int u) -> void {
        for (int &i = cur[u]; i < e[u].size(); ) {
            auto nt = e[u][i ++];
            if (! vis[nt[1]]) {
                vis[nt[1]] = 1;
                self(self, nt[0]);
            }
        }
        res.push_back(u);
    };
    dfs(dfs, st);
    std::reverse(res.begin(), res.end());
    for (auto it : res) {
        std::cout << it << '\n';
    }
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