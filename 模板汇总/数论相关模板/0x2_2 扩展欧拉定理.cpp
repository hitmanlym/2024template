#include<bits/stdc++.h>
using i64 = long long;
#define int i64
int getphi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res = res / i * (i - 1);
        }
    }
    if (n > 1) {
        res = res / n * (n - 1);
    }
    return res;
}
int qmi(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void solve() { // 不保证互质, b > phi 时要 + phi(it)
    // a^b (mod m)
    int a, m, b = 0;
    std::cin >> a >> m;
    int phi = getphi(m);
    std::string s; // b
    std::cin >> s;
    int siz = s.size();
    bool flag = 0;
    for (int i = 0; i < siz; i ++) {
        b = (b * 10 + s[i] - '0');
        if (b >= phi) {
            flag = 1, b %= phi;
        }
    }
    if (flag) b += phi;
    int ans = qmi(a, b, m);
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