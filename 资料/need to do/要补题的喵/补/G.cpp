#include<bits/stdc++.h>
using i64 = long long;
using db = long double;
#define int i64
using pii = std::array<int, 2>;
const int inf = 1e15;
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int> > a(n + 1, std::vector<int>(m + 1));
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            std::cin >> a[i][j];
        }
    }
    std::vector<std::vector<int> > 
        dp(n + 1, std::vector<int>(m + 1, -inf)),
        pre(n + 1, std::vector<int>(m + 1)),
        suf(n + 1, std::vector<int>(m + 2));
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            pre[i][j] = std::max(pre[i][j], pre[i][j - 1] + a[i][j]);
        }
        for (int j = m; j >= 0; j --) {
            suf[i][j] = std::max(suf[i][j], suf[i][j + 1] + a[i][j]);
        }
    }
    for (int i = 1; i <= m; i ++) {
        dp[0][i] = 0;
    }
    for (int i = 1; i <= n; i ++) {
        
        std::vector<int> f(m + 2, -inf), g(m + 2, -inf);
        for (int j = 1; j <= m; j ++) {
            f[j] = std::max(f[j - 1] + a[i][j], pre[i][j - 1] + dp[i - 1][j] + a[i][j]);
            dp[i][j] = std::max(dp[i][j], f[j] + suf[i][j + 1]);
        }
        for (int j = m; j >= 1; j --) {
            g[j] = std::max(g[j + 1] + a[i][j], suf[i][j + 1] + dp[i - 1][j] + a[i][j]);
            dp[i][j] = std::max(dp[i][j], g[j] + pre[i][j - 1]);
        }/*
        for (int j = 1; j <= m; j ++) {
            std::cout << dp[i][j] << ' ';
        }
        std::cout << '\n';*/
    }
    int max = -inf;
    for (int i = 1; i <= m; i ++) {
        //std::cout << dp[n][i] << ' ';
        max = std::max(max, dp[n][i]);
    }
    //std::cout << '\n';
    std::cout << max << '\n';
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