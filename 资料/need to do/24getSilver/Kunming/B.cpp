#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	int m;
	std::cin >> m;
	int sum = 0;
	for (int i = 1; i <= n; i ++) {
		int o = a[i] / k;
		sum += o;
		b[i] = k - a[i] % k;
	}
	std::sort(b.begin(), b.end());
	for (int i = 1; i <= n; i ++) {
		if (m >= b[i]) {
			sum ++;
			m -= b[i];
		}
	}
	sum += m / k;
	std::cout << sum << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}