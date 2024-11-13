#include<bits/stdc++.h>
using i64 = long long;
#define int i64 // must.
struct exCRT {
    int n;
    std::vector<int> a, m; // 先 a 后 m
    void init(int n, std::vector<int> &u, std::vector<int> &v) {
        this -> n = n;
        a.assign(u.begin(), u.end());
        m.assign(v.begin(), v.end());
    }
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
    int work() {
        /*
        int lcm = m[1], now = a[1];
        for (int i = 2; i <= n; i ++) {
            int A = m[i], B = a[i];
            B = (B - now % A + A) % A;
            int x, y;
            int d = exgcd(lcm, A, x, y);
            if (B % d) {
                return -1;
            }
            int k = x * ((B / d) % A) % A; 
            now += k * lcm;
            lcm = lcm / d * A;
            now = (now % lcm + lcm) % lcm;
        }
        return now;
        */
        for (int i = 2; i <= n; i ++) {
            int A = m[i - 1], b = m[i], x, y;
            int c = a[i] - a[i - 1];
            int d = exgcd(A, b, x, y);
            if (c % d) {
                return -1;
            }
            int t = b / d;
            x = (x * (c / d) % t + t) % t;
            a[i] = a[i - 1] + m[i - 1] * x;
            m[i] = m[i] / d * m[i - 1];
        }
        return a[n];
    }
} tr;
void solve() { // like x = a_i (mod m_i) ; m_i 两两互质
    int n;
    std::cin >> n;
    std::vector<int> m(n + 1), a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> m[i] >> a[i];
    }
    exCRT t;
    t.init(n, a, m);
    int res = t.work();
    std::cout << res << '\n';
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