#include<bits/stdc++.h>
using i64 = long long;
using pii = std::array<int, 2>;
const int mod = 998244353;
int qmi(int a, int b = mod - 2) {
    if (a == 0) return 0;
    int res = 1;
    while (b) {
        if (b & 1) {
            res = 1ll * res * a % mod;
        }
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}
struct Comb {
    int n;
    std::vector<int> _fac, _invfac, _inv;
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    void init(int m) {
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i ++) {
            _fac[i] = 1ll * _fac[i - 1] * i % mod;
        }
        _invfac[m] = qmi(_fac[m], mod - 2);
        for (int i = m; i > n; i --) {
            _invfac[i - 1] = 1ll * _invfac[i] * i % mod;
            _inv[i] = 1ll * _invfac[i] * _fac[i - 1] % mod;
        }
        n = m;
    }
    int fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    int invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    int inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    int binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return 1ll * fac(n) * invfac(m) % mod * invfac(n - m) % mod;
    }
} comb;
void solve() {
    int n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    s = "#" + s;
    std::vector<std::vector<int> > f(n + 1, std::vector<int>(k + 1)); 
    const int inv2 = qmi(2);
    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        if (s[i] == '0') continue;
        int op = 1;
        if (s[i] == '?') op = inv2;
        for (int j = 0; j <= k; j ++) {
            for (int l = 0; l <= j; l ++) {
                f[i][j] = (f[i][j] + 1ll * f[i - 1][l] * comb.binom(j, l) % mod) % mod;
            }
            f[i][j] = 1ll * (f[i][j] + 1) * op % mod;
        }
        ans = (ans + f[i][k] % mod) % mod;
    }
    std::cout << ans << '\n';
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}