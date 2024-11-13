#include<bits/stdc++.h>
using i64 = long long;
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
void solve() { // 二叉树
    int n, m;
    std::cin >> n >> m;
    std::cout << 1ll * n * qmi(n + m) % mod << ' ' << 1ll * m * qmi(n + m) % mod << '\n'; 
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