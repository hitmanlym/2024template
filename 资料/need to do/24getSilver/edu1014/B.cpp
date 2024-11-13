#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 1e9 + 7;
int qmi(int a, int b) {
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
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; i ++) {
		std::cin >> b[i];
	}
	for (int i = 1; i <= n; i ++) {
		if (b[i] == a[i]) {
			std::cout << 1 << '\n';
		} else {
			std::cout << qmi(2, b[i]) << '\n';
		}
	}
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