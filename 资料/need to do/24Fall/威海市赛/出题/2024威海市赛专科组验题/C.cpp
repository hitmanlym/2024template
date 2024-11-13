#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	// 3 * (1 + 3 + 5 + .. + (2 * n - 3)) + n - 1
	i64 ans = 3ll * (n - 1) * (n - 1) + (2 * n - 2);
	std::cout << ans << '\n';
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