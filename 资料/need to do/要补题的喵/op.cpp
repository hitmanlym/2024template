#include<bits/stdc++.h>
using i64 = long long;
using pii = std::array<int, 2>;
#define int i64
int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, x, y);
    int z = x;
    x = y;
    y = z - (a / b) * y;
    return d;
}
void solve(int n, int m) { // ax + by = c
    /*int n, m;
    std::cin >> n >> m;*/
    int x, y;
    int a = m - 1, b = 1 - n, c = n - m;
    int d = exgcd(a, b, x, y);
    int x0 = abs(b / d);
    int y0 = abs(a / d);
    x *= c / d;
    if(x < 0) {
    x = x + (-x / x0 + 1) * x0;
    }
    else x %= x0;
    y = (c - a * x) / b;
    int ans = n * m - ((m - 1) * x + m) + x * y / 2;
    std::cout << ans << '\n';
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    int a, b;
    while (std::cin >> a >> b) {
        solve(a, b);
    }
    return 0;
}