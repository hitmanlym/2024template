#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int inf = 1e18;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	std::sort(a.begin() + 1, a.end());
	auto check = [&](int x) -> bool {
		int num = 0;
		std::vector<bool> b(n + 1);
		for (int i = 1; i <= n; i ++) {
			if (! b[i]) {
				for (int j = i + 1; j <= n; j ++) {
					if (a[j] - a[i] <= x) {
						b[i] = 1;
						b[j] = 1;
						break;
					}
				}
				if (! b[i]) {
					num ++;
				}
			}
		}
		return num <= 1;
	};
	int l = 1, r = inf, ans;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
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