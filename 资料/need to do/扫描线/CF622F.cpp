#include <bits/stdc++.h>
using i64 = long long;
#define int i64
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
signed main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    std::vector<int> pl(k + 4), pr(k + 4), fac(k + 4);
    pl[0] = pr[k + 3] = fac[0] = 1;
    for (int i = 1; i <= k + 2; i ++) {
        pl[i] = pl[i - 1] * (n - i) % mod;
        fac[i] = fac[i - 1] * i % mod;
    }
    for (int i = k + 2; i >= 1; i --) {
        pr[i] = pr[i + 1] * (n - i) % mod;
    }
    int y = 0, ans = 0;
    for (int i = 1; i <= k + 2; i ++) {
        y = (y + qmi(i, k)) % mod;
        int a = pl[i - 1] * pr[i + 1] % mod;
        int b = fac[i - 1] * (((k - i) & 1) ? -1ll : 1ll) * fac[k + 2 - i] % mod;
        ans = (ans + y * a % mod * qmi(b) % mod) % mod;
    }
    std::cout << (ans + mod) % mod << '\n';
    return 0;
}