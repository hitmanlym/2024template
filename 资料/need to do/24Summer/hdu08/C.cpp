#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	i64 sum = 0, sum2 = 0;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		/*sum = (sum + a[i]) % mod;
		sum2 = (sum + 1ll * a[i] * a[i] % mod) % mod;*/
	}
	i64 ans = 0;
	for (int i = 1; i <= n; i ++) {
		sum = (sum + a[i]) % mod;
		sum2 = (sum + 1ll * a[i] * a[i] % mod) % mod;
		ans = (ans + 1ll * a[i] * (1ll * (sum - a[i]) * (sum - a[i]) % mod - (sum2 - 1ll * a[i] * a[i] % mod)) % mod) % mod;
		ans = (ans + 1ll * a[i] * (sum2 - 1ll * a[i] * a[i] % mod) % mod) % mod;
		ans = (ans + 1ll * a[i] * a[i] % mod * (sum - a[i]) % mod) % mod;
	}
	std::cout << (ans + mod) % mod;
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}