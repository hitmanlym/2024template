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

    sum = (sum - min) % m;
    // if (sum == 0) sum = m;
    int G = std::__gcd(xx, yy);

    int x, y;
    int a = m, b = -G, c = sum;
    int d = exgcd(a, b, x, y);
    int t = c / d, aa = a / d, bb = b / d;
    x = x * t, y = y * t;
    if (x < 0) {
        int k = std::ceil((1.0 - x) / bb);
        x += bb * k;
        y -= aa * k;
    } else {
        int k = (x - 1) / bb;
        x -= bb * k;
        y += aa * k;
    }

    a = xx, b = yy, c = x * m - sum;
    d = exgcd(a, b, x, y);
    t = c / d, aa = a / d, bb = b / d;
    x = x * t, y = y * t;
    if (x < 0) {
        int op = (-x + m - 1) / m;
        x += op * m;
    }
    if (y < 0) {
        int op = (-y + m - 1) / m;
        y += op * m;
    }

    std::cout << min << '\n';
    std::cout << (x + m) % m << ' ' << (y + m) % m << '\n';
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