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
	int l = 1, r = n, ans = 0;
	while (l <= r) {
		if (l > 1 && a[l] == a[l - 1]) ans ++;
		if (r < n && a[r] == a[r + 1]) ans ++;
		if (l == r) {
			break;
		} else {
			if (l + 1 == r) {
				ans += (a[l] == a[r]);
				l ++;
				r --;
			} else {
				l ++;
				r --;	
				int num = (a[l] == a[l - 1]) + (a[r] == a[r + 1]);
				int op = (a[l] == a[r + 1]) + (a[r] == a[l - 1]);
				if (op < num) {
					std::swap(a[l], a[r]);
				}
			}
		}
	}
	std::cout << ans << '\n';
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