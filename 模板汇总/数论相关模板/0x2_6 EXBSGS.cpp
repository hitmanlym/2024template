#include<bits/stdc++.h>
using i64 = long long;
#define int i64

std::unordered_map<int, int> hash;
struct exBSGS {
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
    int ex_inv(int a, int m) {
        int x, y;
        exgcd(a, m, x, y);
        int res = (x % m + m) % m;
        return res;
    }
    int BSGS(int a, int b, int p) {
        if (1ll % p == b % p) return 0;
        int k = std::sqrt(p) + 1;
        hash.clear();
        for (int i = 0, j = b % p; i < k; i ++) {
            hash[j] = i; 
            j = 1ll * j * a % p;
        }
        int ak = 1;
        for (int i = 0; i < k; i ++) {
            ak = 1ll * ak * a % p;
        } 
        for (int i = 1, j = ak; i <= k; i ++) {
            if (hash.count(j)) return 1ll * i * k - hash[j];
            j = 1ll * j * ak % p;
        }
        return -1;
    }
    int work(int a, int b, int p) {
        if (p == 1) return 0; 
        a %= p; 
        b %= p; 
        if (b == 1) return 0; 
        int x = 0, t, ans; 
        i64 y = 1; 
        while ((t = std::__gcd(a, p)) != 1) {
            if (b % t) return -1; 
            b /= t;
            p /= t;
            x ++;
            y = y * (a / t) % p; 
            if (b == y) return x;
        }
        ans = BSGS(a, b * ex_inv(y, p) % p, p); 
        if (ans == -1) return -1; 
        return ans + x;
    }
} tr;
void solve(int a, int p, int b) { // a^x = b (mod p) [a!-!p]
    //int a, p, b;
    //std::cin >> p >> a >> b; 
    int res = tr.work(a, b, p);
    if (res == -1) {
        std::cout << "No Solution\n";
    } else {
        std::cout << res << '\n';
    }
}
signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    int a, p, b;
    while (std::cin >> a >> p >> b) {
        if (! a && ! b && ! p) break;
        solve(a, p, b);
    }
    return 0;
}