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
	for (int i = 2; i < n; i ++) {
		std::vector<int> b;
		for (int j = 1; j < i; j ++) {
			b.push_back(a[i] - a[j]);
		}
		std::sort(b.begin(), b.end());
		for (int j = i + 1; j <= n; j ++) {
			int it = a[j] - a[i];
			int l = std::lower_bound(b.begin(), b.end(), it) - b.begin();
			int r = std::upper_bound(b.begin(), b.end(), it) - b.begin();
			ans += r - l;
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