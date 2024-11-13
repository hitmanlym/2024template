#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n, q;
	std::cin >> n >> q;
	std::vector<int> a(n + 1);
	int ans = 0;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		ans ^= a[i];
	}
	while (q --) {
		int op;
		std::cin >> op;
		if (op & 1) {
			std::cout << ans << '\n';
		} else {
			int x, y;
			std::cin >> x >> y;
			ans ^= a[x];
			a[x] = y;
			ans ^= a[x];
		}
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	while (t --) {
		solve();
	}
	return 0;
}