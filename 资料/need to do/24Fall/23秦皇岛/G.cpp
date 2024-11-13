#include<bits/stdc++.h>
using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n + 1), b(m + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= m; i ++) {
        std::cin >> b[i];
    }
    i64 ans = 0;
    for (int i = 2; i <= n; i ++) {
        ans += std::abs(a[i] - a[i - 1]);
    }
    for (int i = 2; i <= m; i ++) {
        ans += std::abs(b[i] - b[i - 1]);
    }
    std::cout << ans << '\n';
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