#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	std::vector<i64> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	i64 sum = 1500, ans = -1;
	for (int i = 1; i <= n; i ++) {
		sum += a[i];
		if (sum >= 4000) {
			ans = i;
			break;
		}
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