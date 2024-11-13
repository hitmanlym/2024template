#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;
using u64 = unsigned long long;
using Poly = std::vector<int>;
//
const u64 P = 4179340454199820289;
const int G = 3, mod = 998244353, Maxn = 2e6 + 10;
u64 QMI(u64 a, u64 b = P - 2) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = (__int128)res * a  % P;
        }
        a = (__int128)a * a % P;
        b >>= 1;
    }
    return res;
}
int qmi(int a, int b = mod - 2) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = 1ll * res * a  % mod;
        }
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}
struct Comb {
    int n;
    std::vector<int> _fac, _invfac, _inv;
    //Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    void init(int m) {
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        _invfac[0] = 1;
        _fac[0] = 1;
        _inv[0] = 0;

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
const int invG = QMI(G);
int tr[Maxn << 1], tf;
void tpre(int n) {
    if (tf == n) return ;
    tf = n;
    for (int i = 0; i < n; i ++) {
        tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
    }
}

void NTT(int n, u64 *g, bool op) {
    tpre(n);
    static u64 f[Maxn << 1], w[Maxn << 1];
    w[0] = 1;
    for (int i = 0; i < n; i ++) {
        f[i] = (g[tr[i]]) % P;
    }
    for (int l = 1; l < n; l <<= 1) {
        u64 tG = QMI(op ? G : invG, (P - 1) / (l + l));
        for (int i = 1; i < l; i ++) w[i] = (__int128)(w[i - 1]) * tG % P;
        for (int k = 0; k < n; k += l + l)
            for (int p = 0; p < l; p ++) {
                u64 tt = (__int128)w[p] * f[k | l | p] % P;
                f[k | l | p] = (f[k | p] + P - tt) % P;
                f[k | p] = (f[k | p] + tt) % P;
            }      
        if (l == (1 << 10))
            for (int i = 0; i < n; i ++) f[i] %= P;
    }
    if (! op) {
        u64 invn = QMI(n);
        for(int i = 0; i < n; ++ i) {
            g[i] = (__int128) f[i] % P * invn % P;
        }
    } else {
        for (int i = 0; i < n; ++ i) {
            g[i] = f[i] % P;
        }
    }
}

void px(int n, u64 *f, u64 *g) {
    for (int i = 0; i < n; ++ i) {
        f[i] = (__int128)f[i] * g[i] % P;
    }
}
int lim; // set.
Poly operator *(const Poly &A, const Poly &B) {
    static u64 a[Maxn << 1], b[Maxn << 1];
    for (int i = 0; i < A.size(); i ++) a[i] = A[i];
    for (int i = 0; i < B.size(); i ++) b[i] = B[i];
    Poly C;
    C.resize(/*std::min(lim, */(int)(A.size() + B.size() - 1));
    int n = 1; 
    for(n; n < A.size() + B.size() - 1; n <<= 1);
    NTT(n, a, 1);
    NTT(n, b, 1);
    px(n, a, b);
    NTT(n, a, 0);
    for (int i = 0; i < C.size(); i ++) {
        C[i] = a[i];
    }
    for (int i = 0; i <= n; i ++) {
        a[i] = 0;
        b[i] = 0;
    }
    return C;
}

void solve() {
    comb.init(0);
    int n, t;
    std::cin >> n >> t;
    std::vector<int> a(n + 1);
    int max = 0;
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
        max = std::max(max, a[i]);
    }
    Poly g(max + 1);
    for (int i = 1; i <= n; i ++) {
        g[a[i]] ++;
    }
    auto h = g;
    std::reverse(h.begin(), h.end());
    //lim = max * 2;
    Poly f = g * h;
    std::vector<int> num(max + 1);
    for (int i = 0; i <= max; i ++) {
        num[i] = f[max + i];
    }
    num[0] = num[0] - n;
    /*
    std::cout << max << '\n';
    for (int i = 0; i <= max; i ++) {
        std::cout << num[i] << ' ';
    }
    std::cout << '\n';*/

    int ans = 0;
    for (int i = 0; i <= max && i <= t; i ++) {
        ans = (ans + 1ll * num[i] * comb.binom(t, i) % mod * 
        qmi(n - 2, i) % mod * qmi(((comb.binom(n - 2, 2) + 1) % mod), t - i) % mod) % mod;

        //std::cout << ans << '\n';
    }
    ans = 1ll * ans * qmi(qmi((1ll * n * (n - 1) / 2) % mod, t)) % mod;
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