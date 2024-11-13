#include<bits/stdc++.h>
using i64 = long long;
#define int i64
// O(p)
int mod;
int qmi(int a, int b = mod - 2, int mod = mod) {
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
struct exLucas { // if p is sure, use liner.
    std::vector<int> u, v;
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
    int F(int n, int p, int x) { // n! % x
        if (n == 0) return 1;
        int cir = 1, rem = 1;
        for (int i = 1; i <= x; i ++) {
            if (i % p) cir = cir * i % x;
        }
        cir = qmi(cir, n / x, x);
        for (int i = x * (n / x); i <= n; i ++) {
            if (i % p) rem = rem * (i % x) % x;
        }
        return F(n / p, p, x) * cir % x * rem % x;
    }
    int BINOM(int n, int m, int p, int x) { // (n, m) % p_i^a_i
        int fx = F(n, p, x), fy = F(m, p, x), fz = F(n - m, p, x);
        auto div = [&](int n, int p) -> int {
            int cnt = 0;
            do {
                n /= p;
                cnt += n;
            } while(n);
            return cnt;
        };
        int op = qmi(p, div(n, p) - div(m, p) - div(n - m, p), x);
        return fx * ex_inv(fy, x) % x * ex_inv(fz, x) % x * op % x;
    }
    void breakdown(int a, int b) {
        u.assign(1, 0);
        v.assign(1, 0);

        int n = mod;
        for (int i = 2; i * i <= mod; i ++) {
            if (! (n % i)) {
                int x = 1;
                while (! (n % i)) {
                    n /= i;
                    x *= i;
                }
                u.push_back(x);
                v.push_back(BINOM(a, b, i, x));
            }
        }
        if (n > 1) {
            u.push_back(n);
            v.push_back(BINOM(a, b, n, n));
        }
    }
    int exCRT() { // u - m
        int siz = u.size();
        if (siz < 2) {
            return 0;
        }
        int lcm = u[1], now = v[1];
        for (int i = 2; i < siz; i ++) {
            int A = u[i], B = v[i];
            B = (B - now % A + A) % A;
            int x, y;
            int d = exgcd(lcm, A, x, y);
            if (B % d) {
                return -1;
            }
            int k = x * (B / d) % A;
            now += k * lcm;
            lcm = lcm / d * A;
            now = (now % lcm + lcm) % lcm;
        }
        return now;
    }
    int exlucas(int a, int b) {
        breakdown(a, b);
        int res = exCRT();
        return res;
    }
} tr;
void solve() { // p is prime
	int a, b, p;
    std::cin >> a >> b >> p;
    mod = p;
    int ans = tr.exlucas(a, b);
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