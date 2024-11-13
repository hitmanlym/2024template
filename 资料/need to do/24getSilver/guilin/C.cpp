#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 1e9 + 7;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(2 * n + 1), b(2 * n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		b[i] = a[i];
		b[2 * n + 1 - i] = a[i];
		a[i + n] = a[i];
	}
	int suma = 0, sumb = 0, Fa, Fb;
	for (int i = 1; i <= 2 * n; i ++) {
		a[i] = (a[i] + a[i - 1]) % mod;
		b[i] = (b[i] + b[i - 1]) % mod;
		suma = (suma + a[i]) % mod;
		sumb = (sumb + b[i]) % mod;
	}
	Fa = a[2 * n], Fb = b[2 * n];
	int bit = 2 * n;
	for (int i = 1; i < m; i ++) {
		suma = (suma * 2 % mod + Fa * bit % mod) % mod;
		sumb = (sumb * 2 % mod + Fb * bit % mod) % mod;
		bit = bit * 2 % mod;
		Fa = Fa * 2 % mod;
		Fb = Fb * 2 % mod;
	}
	std::cout << std::max(suma, sumb) << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}