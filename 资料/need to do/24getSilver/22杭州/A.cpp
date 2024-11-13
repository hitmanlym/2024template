#include<bits/stdc++.h>
using i64 = long long;
#define int i64 // must.
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
// 仅保证a, mod 互质,求逆元    a关于mod 的逆元
int ex_inv(int a, int m) {
    int x, y;
    exgcd(a, m, x, y);
    int res = (x % m + m) % m;
    return res;
}
void solve() { // ax + by = c

    int n, m;
    std::cin >> n >> m;
    i64 sum = 0;
    std::vector<int> aaa(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> aaa[i];
        sum += aaa[i];
    }
    int xx = n, yy = n * (n + 1) / 2, zz = m;
    int g = std::__gcd(xx, std::__gcd(yy, zz));
    int min = sum % g;
    int mul = (sum / g) % m;

    int a = m, b = -std::__gcd(xx, yy), c = g;
    // std::cout << a << ' ' << b << ' ' << c << '\n';
    int x, y;
    int d = exgcd(a, b, x, y);
    int t = c / d, aa = a / d, bb = b / d;
    x *= t, y *= t;
    int U = y;
/*
    int D = std::__gcd(xx, yy);
    a = m, b = D, c = g * y;
    d = exgcd(a, b, x, y);
    t = c / d;
    x *= t;

    // std::cout << g * y << '\n';*/
    a = xx, b = yy, c = std::__gcd(xx, yy) * U; // + ? * m
    //std::cout << a << ' ' << b << ' ' << c << '\n';
    d = exgcd(a, b, x, y);
    // std::cout << d << ' ' << c << '\n';
    t = c / d, aa = a / d, bb = b / d;
    x *= t, y *= t;

    std::cout << min << '\n';
    //std::cout << x << ' ' << y << '\n';
    std::cout << (x * mul % m + m) % m << ' ' << (y * mul % m + m) % m << '\n';
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