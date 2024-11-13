#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		a[i] += a[i - 1];
	}
	std::map<int, int> mp;
	mp[0] = 0;
	// int ans = 0;
	std::vector<int> dp(n + 1);
	for (int i = 1; i <= n; i ++) {
		dp[i] = dp[i - 1];
		if (mp.count(a[i]))
		dp[i] = std::max(dp[i], dp[mp[a[i]]] + 1);
		mp[a[i]] = i;
	}
	std::cout << dp[n] << '\n';
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