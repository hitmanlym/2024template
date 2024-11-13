#include<bits/stdc++.h>
using i64 = long long;
// O(p) 

int mod;
struct Lucas { // if p is sure, use liner.
    int qmi(int a, int b = mod - 2) {
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
    int binom(int a, int b) {
        if (a < b) return 0;
        i64 down = 1, up = 1;
        for (int i = a, j = 1; j <= b; i --, j ++) {
            up = up * i % mod;
            down = down * j % mod;
        } 
        return up * qmi(down) % mod;
    }
    int lucas(int a, int b) {
        if (a < mod && b < mod) return binom(a, b);
        return binom(a % mod, b % mod) * lucas(a / mod, b / mod) % mod;
    }

} tr;
void solve() { // p is prime
	int a, b, p;
    std::cin >> a >> b >> p;
    mod = p;
    int ans = tr.lucas(a + b, b);
    std::cout << ans << '\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}