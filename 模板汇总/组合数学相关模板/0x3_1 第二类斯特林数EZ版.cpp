#include<bits/stdc++.h>
using i64 = long long;
#define int i64

const int mod = 1e9 + 7;
int qmi(int a, int b) {
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
// n 不同， m 相同集合, 非空
int S(int n, int m) {
    i64 res = 0;
    for (int i = 0; i <= m; i ++) {
        res = (res + ((m - i) % 2 ? -1 : 1) * comb.binom(m, i) % mod * qmi(i, n) % mod) % mod;
    }
    res = res * comb.invfac(m) % mod;
    return (res + mod) % mod;
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    for (int i = 0; i <= n; i ++) {
        std::cout << S(n, i) << ' ';
    }
    std::cout << '\n';
    return 0;
}