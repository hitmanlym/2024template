#include<bits/stdc++.h>
using i64 = long long;
void solve() {
    int n;
    std::cin >> n;
    std::vector<int> v;
    std::vector<std::array<int, 2> > a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i][0] >> a[i][1];
        a[i][1] ++;
        v.push_back(a[i][0]);
        v.push_back(a[i][1]);
    }
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
    std::vector<std::vector<std::array<int, 3> > > e(v.size() + 2); 
    std::vector<int> deg(v.size() + 2);
    for (int i = 1; i <= n; i ++) {
        a[i][0] = std::lower_bound(v.begin(), v.end(), a[i][0]) - v.begin() + 1;
        a[i][1] = std::lower_bound(v.begin(), v.end(), a[i][1]) - v.begin() + 1;
        e[a[i][0]].push_back({a[i][1], 1, i});
        e[a[i][1]].push_back({a[i][0], 0, i});
        deg[a[i][0]] ++;
        deg[a[i][1]] ++;
    }
    int cnt = n;
    for (int i = 1; i <= v.size(); i ++) {
        if (deg[i] & 1) {
            deg[i] ++;
            deg[i + 1] ++;
            e[i].push_back({i + 1, -1, ++ cnt});
            e[i + 1].push_back({i, -1, cnt});
        }
    }
    std::vector<bool> vis(v.size() + 2);
    std::vector<int> tag(cnt + 1, -1);
    auto dfs = [&](auto self, int u) -> void {
        vis[u] = 1;
        for (auto it : e[u]) {
            if (tag[it[2]] == -1) {
                if (it[1] == 1) {
                    tag[it[2]] = 0;
                } else {
                    tag[it[2]] = 1;
                } 
                self(self, it[0]);
            }
        }
    };
    for (int i = 1; i <= v.size(); i ++) {
        if (! vis[i]) {
            dfs(dfs, i);
        }
    }
    for (int i = 1; i <= n; i ++) {
        std::cout << tag[i] << ' ';
    }
    std::cout << '\n';
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