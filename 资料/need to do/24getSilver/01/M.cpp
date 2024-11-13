#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	int num = 0;
	int u = 0, sum = 0;
	while (true) {
		bool f = 1;
		for (int i = 1; i <= n; i ++) {
			sum += a[i] % 10;
			a[i] /= 10;
			if (a[i]) f = 0;
		}
		sum /= 10;
		num += sum;
		if (f) {
			break;
		}
	}
	while (sum) {
		sum /= 10;
		num += sum;
	}
	std::cout << num << '\n';
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