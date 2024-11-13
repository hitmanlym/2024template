#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;
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
void solve() {
    int n;
    std::cin >> n;
    std::cout << (1ll * (n - 1) * (n - 1) % mod * qmi(n, mod - 2) + 1) % mod;
    //std::cout << a
    //std::cout << qmi(998244353, mod - 2) << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}