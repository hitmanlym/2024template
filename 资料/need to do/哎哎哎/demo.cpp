#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	auto check = [&](double x) -> bool {
		std::vector<double> sum(n + 1, 0.0);
		for (int i = 1; i <= n; i ++) {
			sum[i] = sum[i - 1] + a[i] - x;
		}
		auto pre = sum, nxt = sum;
		for (int i = 1; i <= n; i ++) {
			pre[i] = std::min(pre[i - 1], pre[i]);
		} 
		for (int i = n - 1; i >= 1; i --) {
			nxt[i] = std::max(nxt[i + 1], nxt[i]);
		}

		for (int i = 2; i <= n - 1; i ++) {
			if (a[i] < a[i - 1] && a[i] < a[i + 1]) {
				if (pre[i - 2] <= nxt[i + 1]) {
					return true;
				}
			}
		}
		return false;
	};
	double l = 1, r = 1e10;
	int num = 50;
	while (num --) {
		double mid = (l + r) / 2.0;
		if (check(mid)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	printf("%.12lf\n", l);
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