#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int> > e(n + 1);
    std::vector<int> d(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
        d[u] ++;
        d[v] ++;
    }
    int num = 0;
    for (int i = 1; i <= n; i ++) {
        if (d[i] == 1) num ++;
    }
    for (int i = 1; i <= n; i ++) {
        if (d[i] != 2) continue;
        int num = 0;
        for (auto u : e[i]) {
            if (d[u] - 1 == 1) {
                for (auto v : e[u]) {
                    if (v == i) continue;
                    num += e[v].size();
                }
            } 
            if (d[u] - 1 > 1) {
                num += e[u].size() - 1;
            }
        }
        if (num == n - 3) {
            std::cout << "Yes\n";
            return ;
        }
    }
    std::cout << "No\n";
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}