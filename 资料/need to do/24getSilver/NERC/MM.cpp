#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	i64 ans = 0;
	for (int i = 1; i <= n; i ++) {
		int r = n;
		std::unordered_map<int, short> mp;
		while (r > i) {
			if (mp.count(a[r])) ans += mp[a[r]];
			if (! ((a[i] + a[r]) & 1)) {
				mp[(a[i] + a[r]) >> 1] ++;
			}
			r --;
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