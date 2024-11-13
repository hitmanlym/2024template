#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	i64 sum = 0, x;
	for (int i = 1; i <= n; i ++) {
		std::cin >> x;
		sum += x;
	}
	double ans = (double)sum / (n + 1);
	//std::cout << ans * 2 << ' ';
	printf("%.10lf ", ans * 2);
	for (int i = 2; i <= n; i ++) {
		//std::cout << ans << ' ';
		printf("%.10lf ", ans);
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}