#include <bits/stdc++.h>
using i64 = long long;
const i64 inf = 1e18;
void solve() {
    int n;
    i64 l, r;
    std::cin >> n >> l >> r;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    std::sort(a.begin() + 1, a.end());
    int m = -1;
    for (int i = 1; i <= n; i ++) {
        if (a[i]) {
            m = a[i];
            break;
        }
    }

    std::vector<i64> f(m, inf);
    f[0] = 0;

    for (int i = 1; i <= n; i ++) {
        for (int j = 0, lim = std::__gcd(a[i], m); j < lim; j ++) {
            for (int t = j, c = 0; c < 2; c += t == j) {
                int np = (t + a[i]) % m;
                f[np] = std::min(f[np], f[t] + a[i]);
                t = np;
            }
        }
    }
    i64 ans = 0;
    for (int i = 0; i < m; i ++) {
        if (r >= f[i]) {
            ans += (r - f[i]) / m + 1;
        }
        if (l - 1 >= f[i]) {
            ans -= (l - 1 - f[i]) / m + 1;
        }
    }
    std::cout << ans << '\n';
}
int main() {
    int t = 1;
    //cin >> t;
    while (t --) {
        solve();
    }
}