#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n + 1), pre(n + 1), suf(n + 2);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; i ++) {
		pre[i] = std::__gcd(pre[i - 1], a[i]);
	}
	for (int i = n; i >= 1; i --) {
		suf[i] = std::__gcd(suf[i + 1], a[i]);
	}
	int ans = pre[n];
	for (int i = 1; i <= n; i ++) {
		if (pre[i] == pre[i - 1]) continue;
		int res = 0;
		for (int j = i; j <= n; j ++) {
			res = std::__gcd(res, a[j] + k);
			ans = std::max(ans, std::__gcd(std::__gcd(pre[i - 1], res), suf[j + 1]));
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