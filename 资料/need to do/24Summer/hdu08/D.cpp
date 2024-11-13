#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	i64 n, m, a, b, ans = 0;
	std::cin >> n >> m >> a >> b;
	if (m == 1 || n == 1) ans += n * m;
	else {
		ans += n * 2 + m * 2 - 4;
		if (a == 1 || a == n || b == 1 || b == m);
		else {
			ans += std::max({n - 2, m - 2});
		}
	}
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