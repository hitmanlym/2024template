#include <bits/stdc++.h>
using namespace std;
#define i64 __int128
int read()
{
    int res = 0, bj = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-') bj = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        res = res * 10 + ch - '0';
        ch = getchar();
    }
    return res * bj;
}
i64 qmi(i64 a, int b) {
    i64 res = 1;
    while (b) {
        if (b & 1) res = res * a;
        b >>= 1;
        a = a * a;
    } 
    return res;
}
const i64 inf = 1e18;
void solve() {
    long long n, k;
    std::cin >> n >> k;
    int ans = 0;
    if (k == 3) {
        for (int i = 1; 1ll * i * i * i <= n; i ++) {
            if (n % i == 0) {
                i64 l = 1, r = 2e9, res = -1;
                while (l <= r) {
                    i64 mid = l + r >> 1; 
                    i64 x = mid, y = x + i;
                    if (x * x + y * y + x * y >= n / i) {
                        res = mid;
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                }
                if (res == -1) continue;
                i64 x = res, y = res + i;
                //std::cout <<x << ' ' <<y <<'\n';
                if (x * x + y * y + x * y == n / i) {
                    ans ++;
                }
            }
        }
    } else if (k == 4) {
        for (int i = 1; 1ll * i * i * i <= n; i ++) {
            if (n % i == 0) {
                i64 l = 1, r = 1e7, res = -1;
                while (l <= r) {
                    i64 mid = l + r >> 1; 
                    i64 x = mid, y = x + i;
                    if ((x * x + y * y) * (x + y) >= n / i) {
                        res = mid;
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                }
                if (res == -1) continue;
                i64 x = res, y = res + i;
                if ((x * x + y * y) * (x + y) == n / i) {
                    ans ++;
                }
            }
        }
    } else {
        for (int i = 1; 1ll * i * i * i <= n; i ++) { // 
            if (n % i == 0) {
                i64 l = 1, r = 1e5, res = -1;
                while (l <= r) {
                    i64 mid = l + r >> 1;
                    i64 x = mid, y = x + i;
                    if (qmi(y, k) - qmi(x, k) >= n) {
                        res = mid;
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                }
                if (res == -1) continue;
                i64 x = res, y = res + i;
                if (qmi(y, k) - qmi(x, k) == n) {
                    ans ++;
                }
            }
        }/*
        for (int i = 1; i <= 4000; i ++) {
            for (int j = i + 1; j <= 4000; j ++) {
                long long op = qmi(j, k) - qmi(i, k);
                if (op == n) {
                    ans ++;
                }
            }
        }*/
    }
    std::cout << ans << '\n';
}
int main()
{
    int t = 1;
    std::cin >>t;
    while (t --) {
        solve();
    }
    return 0;
}