#include<bits/stdc++.h>
using i64 = long long;
#define int i64
int num(int x) {
	int res = 0;
	while (x) {
		res ++;
		x -= (x & (-x));
	}
	return res;
}
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; i ++) {
		std::cin >> a[i];
	}
	int q =  1000, ans = 0;

	while (q --) {
		std::shuffle(a.begin(), a.end(), std::default_random_engine(seed));
		int now = 0;
		for (int i = 0; i < n; i ++) {
			now |= a[i];
			ans = std::max(ans, i + 1 - num(now));
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