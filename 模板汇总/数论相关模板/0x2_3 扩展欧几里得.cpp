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
    int a, b, c;
    std::cin >> a >> b >> c;
    int x, y;
    int d = exgcd(a, b, x, y);
    if (c % d) {    // not exist.
        std::cout << "-1\n";
        return ;
    }
    int t = c / d, aa = a / d, bb = b / d;
    x *= t, y *= t;
    /*
    // xx = x + k * bb, yy = y - k * aa
    int minx = (x % bb + bb - 1) % bb + 1;
    int miny = (y % aa + aa - 1) % aa + 1;
    int maxx = (c - b * miny) / a;
    int maxy = (c - a * minx) / b;
    int cnt = (maxx - minx) / bb + 1; // (maxy - miny) / aa + 1
    if (maxx <= 0 && maxy <= 0); // no positive ans
    */

    if (x < 0) { // x 调整到最小正整数
        int k = std::ceil((1.0 - x) / bb);
        x += bb * k;
        y -= aa * k;
    } else {
        int k = (x - 1) / bb;
        x -= bb * k;
        y += aa * k;
    }

    if (y > 0) { // have positive solution
        int cnt = (y - 1) / aa + 1;
        std::cout << cnt << ' ';
        int minx = x, miny = (y - 1) % aa + 1;
        int maxx = x + (cnt - 1) * bb, maxy = y;
        std::cout << minx << ' ' << miny << ' ' << maxx << ' ' << maxy << '\n';     
    } else { // 
        int min_positive_x = x;
        int min_positive_y = y + aa * 1ll * std::ceil(((1.0 - y) / aa));
        std::cout << min_positive_x << ' ' << min_positive_y << '\n';
    }
}

signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}