#include<bits/stdc++.h>
using i64 = long long;
using db = long double;
using pii = std::array<int, 2>;
void solve() {
    int n, m;
    double k;
    std::cin >> n >> m >> k;
    std::vector<db> p(n + 1);
    for (int i = 0; i <= n; i ++) {
        int u;
        std::cin >> u;
        p[i] = u;
    }
    p[0] *= 1.0 / k;
    std::vector<db> r(n + 1);
    r[0] = 1.0;
    for (int i = 1; i <= n; i ++) {
        r[i] = r[i - 1] * (1.0 - k);
    }

    db ans = 0;
    int S = 450;
    std::vector<std::vector<db> > suf(n + 2, std::vector<db>(S + 1));
    for (int i = 1; i <= S; i ++) {
        suf[n + 1][i] = -1e15;
    }
    for (int i = 0; i <= n; i ++) {
        suf[i][0] = 0;
    }
    for (int i = n; i >= 0; i --) {
        for (int j = 1; j <= S; j ++) {
            if (n - i + 1 - j > m) continue;
            suf[i][j] = std::max(suf[i + 1][j], p[i] * r[j - 1] + suf[i + 1][j - 1]);
            if (i == 0 || j == S) {
                ans = std::max(ans, suf[i][j]);
            }
        }
    }
    std::cout << std::fixed << std::setprecision(12) << ans * k << '\n';
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