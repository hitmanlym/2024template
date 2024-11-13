#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
// #define int i64
// int qmi(int a, int b) {
//     if (a == 0) return 0;
//     int res = 1;
//     while (b) {
//         if (b & 1) {
//             res = 1ll * res * a % mod;
//         }
//         a = 1ll * a * a % mod;
//         b >>= 1;
//     }
//     return res;
// }
// struct Comb {
//     int n;
//     std::vector<int> _fac, _invfac, _inv;
//     Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
//     void init(int m) {
//         _fac.resize(m + 1);
//         _invfac.resize(m + 1);
//         _inv.resize(m + 1);

//         for (int i = n + 1; i <= m; i ++) {
//             _fac[i] = 1ll * _fac[i - 1] * i % mod;
//         }
//         _invfac[m] = qmi(_fac[m], mod - 2);
//         for (int i = m; i > n; i --) {
//             _invfac[i - 1] = 1ll * _invfac[i] * i % mod;
//             _inv[i] = 1ll * _invfac[i] * _fac[i - 1] % mod;
//         }
//         n = m;
//     }
//     int fac(int m) {
//         if (m > n) init(2 * m);
//         return _fac[m];
//     }
//     int invfac(int m) {
//         if (m > n) init(2 * m);
//         return _invfac[m];
//     }
//     int inv(int m) {
//         if (m > n) init(2 * m);
//         return _inv[m];
//     }
//     int binom(int n, int m) {
//         if (n < m || m < 0) return 0;
//         return 1ll * fac(n) * invfac(m) % mod * invfac(n - m) % mod;
//     }
// } comb;
void solve() {
    int n, m;
    std::cin >> n >> m;
    int lim = (m + 1) / 2;
    // y = x + 1, 与 y = x - (lim + 1) 之间. 我们来看横坐标，用组合数前缀和来容斥
    std::vector<int> sum(n + 1), inv(n + 1);
    sum[0] = inv[0] = inv[1] = 1;
    for (int i = 2; i <= n; i ++) {
        inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    }
    // return ;
    for (int i = 1; i <= n; i ++) {
        sum[i] = 1ll * sum[i - 1] * inv[i] % mod * (n - i + 1) % mod;
    }
    // return ;
    for (int i = 1; i <= n; i ++) {
        sum[i] = (sum[i - 1] + sum[i]) % mod;
    }
    // return ;
    auto get = [&](int l, int r) -> int {
        return (sum[r] - (l == 0 ? 0 : sum[l - 1])) % mod;
    };
    int l = (n + 1) / 2, r = (n + lim) / 2;
    int LIML = l, LIMR = r;
    // std::cout << LIML << ' ' << LIMR << '\n';
    int ans = get(l, r);
    auto trans = [&](int &l, int &r, int op) /*-> std::array<int, 2>*/ { // just for x.  X = y - 1 = (n - x) - 1
        int x = r;
        r = n - l + op, l = n - x + op;
        // return {l, r};
    };
    // auto transg = [&](int l, int r) -> std::array<int, 2> { // X = y + (lim + 1) = (n - x) + (lim + 1)
    //     int x = r;
    //     r = n - l + (lim + 1), l = n - x + (lim + 1);
    //     return {l, r};
    // };
    auto f = [&](auto self, int l, int r, int op) -> int { 
        if (op == 0) {// y = x + 1
            // auto it = trans(l, r, -1);
            // l = it[0], r = it[1];  
            trans(l, r, -1);
            // std::cout << "!! " << l << ' ' << r << '\n';
            // if (r < LIML) return 0;
            // if (l > LIMR) return 0;
            // l = std::max(l, LIML);
            // r = std::min(r, LIMR);
            if (r < 0) return 0;
            l = std::max(l, 0);
            r = std::min(r, LIML - 1);
        } else {// y = x - (lim + 1)
            // auto it = trans(l, r, (lim + 1));
            // l = it[0], r = it[1];
            trans(l, r, (lim + 1));
            // if (r < LIML) return 0;
            // if (l > LIMR) return 0;
            // l = std::max(l, LIML);
            // r = std::min(r, LIMR);
            if (l > n) return 0;
            l = std::max(l, LIMR + 1);
            r = std::min(r, n);
        }
        return (-self(self, l, r, op ^ 1) - get(l, r)) % mod;
    };
    // std::cout << ans << '\n';
    ans = (ans + f(f, l, r, 0)) % mod;
    // std::cout << ans << ' ' << l << ' ' << r << '\n';
    ans = (ans + f(f, l, r, 1)) % mod;
    // std::cout << ans << ' ' << l << ' ' << r << '\n';
    std::cout << (ans + mod) % mod << '\n';
}  
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}