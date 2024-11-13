#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
#include<map>
using i64 = long long;
#define int i64
const int N = 2e5 + 10;
const int lim = 1e9 + 1;
std::vector<int> c(N);
std::vector<std::vector<std::array<int, 2> > > e(N);
bool f = 0;
int k;
int dfs(int u, int r) {
    if (e[u].size() == 0) {
        c[u] *= r;
    }
    for (auto it : e[u]) {
        int v = it[0], s = it[1];
        int ct = dfs(v, std::min(r * s, lim));
        c[u] += ct;
    }
    return c[u];
}
void solve() {
    int n;
    std::cin >> n >> k;
    f = 1;
    for (int i = 1; i <= n; i ++) {
        e[i].clear();
        int op;
        std::cin >> op;
        if (op & 1) {
            int num;
            std::cin >> num;
            while (num --) {
                int x, a;
                std::cin >> x >> a;
                e[i].push_back({a, x});
            }
            c[i] = 0;
        } else {
            std::cin >> c[i];
        }
    }
    int ans = dfs(k, 1);
    for (auto it : e[k]) {
        int u = it[0];
        ans = std::min(ans, c[k] - c[u]);
    }
    if (ans >= lim) {
        std::cout << "Impossible\n";
    } else {
        std::cout << ans << '\n';
    }
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