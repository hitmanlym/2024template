#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;

const int mod = 998244353;
void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        a[i] += 1;
        for (int j = 1; i * j + j <= n; j ++) {
            a[i * j + j] = (a[i * j + j] + a[i]) % mod;
        }
    } 
    for (int i = 1; i <= n; i ++) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    ///std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}