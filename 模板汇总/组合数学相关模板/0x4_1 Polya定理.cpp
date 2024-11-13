#include<bits/stdc++.h>
using i64 = long long;
int mod = 1e9 + 7;
int qmi(int a, int b = mod - 2) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}
int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res = res / i * (i - 1);
        }
    }
    if (n > 1) {
        res = res / n * (n - 1);
    }
    return res;
}

void solve() { // 无所谓S
	int n;
	std::cin >> n;
	int ans = 0;
	for (int i = 1; i * i <= n; i ++) {
		if (n % i == 0) {
			ans = (ans + 1ll * qmi(n, i) * phi(n / i) % mod) % mod;
			if (i * i != n) {
				ans = (ans + 1ll * qmi(n, n / i) * phi(i) % mod) % mod;
			}
		}
	}
	ans = 1ll * ans * qmi(n) % mod;
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