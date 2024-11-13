#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using Points = std::vector<std::array<int, 2> >;
using Poly = std::vector<int>;
const int mod = 1e9 + 7;
int qmi(int a, int b = mod - 2) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
struct Lagrange {
    int n;
    Points a;
    void init(int n, Points &X) {
        this -> n = n;
        a.assign(X.begin(), X.end());
    }
    int get(int k) {
        int ans = 0;
        for (int i = 1; i <= n; i ++) {
            int s1 = a[i][1] % mod;
            int s2 = 1;
            for (int j = 1; j <= n; j ++) {
                if (i == j) continue;
                s1 = s1 * (k - a[j][0]) % mod;
                s2 = s2 * (a[i][0] - a[j][0]) % mod;
            }
            ans = (ans + s1 * qmi(s2) % mod) % mod;
        }
        return (ans + mod) % mod;
    }
} tr;

struct exLagrange { // 连续的 下标从 0 开始. 0 -- (k + 1)[n] {k + 1次 Poly}
    int n;
    Poly a, pl, pr, fac;
    void init(int n, Poly &X) {
        this -> n = n;
        pl.assign(n + 1, 0);
        pr.assign(n + 1, 0);
        fac.assign(n + 1, 0);
        a.assign(X.begin(), X.end()); //
    }
    void pre(int k) {
        fac[0] = 1;
        for (int i = 1; i <= n; i ++) {
            fac[i] = fac[i - 1] * i % mod;
        }
        pl[0] = 1;
        for (int i = 1; i <= n; i ++) {
            pl[i] = pl[i - 1] * (k - i + 1) % mod; 
        }
        pr[n] = 1;
        for (int i = n - 1; i >= 0; i --) {
            pr[i] = pr[i + 1] * (k - i - 1) % mod;
        }
    }
    int get(int k) {
        pre(k);
        int ans = 0;
        for (int i = 0; i <= n; i ++) {
            int x = pl[i] * pr[i] % mod;
            int y = fac[i] * (((n - i) & 1) ? -1ll : 1ll) * fac[n - i] % mod;
            ans = (ans + a[i] * x % mod * qmi(y) % mod) % mod;
        }
        return (ans + mod) % mod;
    }   
} extr;
void solve() { // 当我们的连续 n 个值不是从 0 开始，只需要保留 d，整体偏移即可
                // 函数是平移的.
    /*int n, k;
    std::cin >> n >> k;
    Points a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i][0] >> a[i][1];
    }
    tr.init(n, a);
    int ans = tr.get(k);
    std::cout << ans << '\n';*/
    int n, k;
    std::cin >> n >> k; // k + 1 次多项式
    Poly a(k + 2);
    int y = 0;
    for (int i = 0; i <= k + 1; i ++) { // 左移一位.
        y = (y + qmi(i + 1, k)) % mod;
        a[i] = y;
    }
    extr.init(k + 1, a);
    int ans = extr.get(n - 1); // 左移.
    std::cout << ans << '\n';
}
signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}
