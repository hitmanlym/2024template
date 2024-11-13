#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::array<i64, 3> > a(n);
	i64 ans = 0;
	for (int i = 0; i < n; i ++) {
		std::cin >> a[i][0] >> a[i][1] >> a[i][2];
		ans += a[i][1];
	}
	std::sort(a.begin(), a.end(), [&](auto x, auto y) {
		return x[0] * y[2] > y[0] * x[2];
	});
	i64 op = 0;
	for (int i = 0; i < n; i ++) {
		ans -= a[i][2] * op;
		op += a[i][0];
	}
	std::cout << ans << '\n';
}
int main() {
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}