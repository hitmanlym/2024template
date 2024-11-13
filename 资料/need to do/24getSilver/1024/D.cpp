#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 24;
void solve() {
	int n, q;
	std::cin >> n >> q;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	int B = std::sqrt(n);
	std::vector<int> v(B + 1);
	// int q;
	// std::cin >> q;
	while (q --) {
		int k;
		std::cin >> k;
		if (k <= B) {
			v[k] ++;
		} else {
			for (int i = k; i <= n; i += k) {
				a[i] = a[i] * 10 % mod;
			}
		}
	}
	std::vector<int> pw(n + 1);
	pw[0] = 1;
	for (int i = 1; i <= n; i ++) {
		pw[i] = pw[i - 1] * 10 % mod;
	}
	for (int i = 1; i <= n; i ++) {
		int num = 0;
		for (int j = 1; j <= B; j ++) {
			if (i % j == 0) {
				num += v[j];
			}
		}
		// std::cout << a[i] << ' ' << num << '\n';
		if (num) a[i] = a[i] * pw[num] % mod;
		std::cout << a[i] << ' ';
	}
	std::cout << '\n';
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