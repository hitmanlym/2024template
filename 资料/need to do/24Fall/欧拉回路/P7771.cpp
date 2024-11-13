#include<bits/stdc++.h>
using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int> > e(n + 1);
    std::vector<int> in(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back(v);
        in[v] ++;
    } 
    bool flag = 1;
    int st = 0;
    for (int i = 1; i <= n; i ++) {
        std::sort(e[i].begin(), e[i].end());
        if (std::abs((int)e[i].size() - in[i]) > 1) {
            flag = 0;
        }
        if (e[i].size() > in[i]) {
            if (st) flag = 0;
            st = i;
        }
    }
    if (! st) st = 1;
    std::vector<int> cur(n + 1);
    std::vector<int> res;
    auto dfs = [&](auto self, int u) -> void {
        for (int &i = cur[u]; i < e[u].size(); ) {
            self(self, e[u][i ++]); // attention please.
        }
        res.push_back(u);
    };
    dfs(dfs, st);
    if (res.size() != m + 1) {
        flag = 0;
    }
    if (! flag) {
        std::cout << "No\n";
    } else {
        std::reverse(res.begin(), res.end());
        for (auto it : res) {
            std::cout << it << ' ';
        }
        std::cout << '\n';
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