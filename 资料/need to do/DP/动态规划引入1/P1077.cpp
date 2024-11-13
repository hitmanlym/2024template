#include<bits/stdc++.h>
using i64 = long long;

const int mod = 1e6 + 7;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n + 1);
	std::vector<int> dp(m + 1);
	dp[0] = 1;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		for (int j = m; j >= 0; j --) {
			for (int k = 1; k <= std::min(j, a[i]); k ++) {
				dp[j] = (dp[j] + dp[j - k]) % mod;
			}
		}
	}
	std::cout << dp[m] << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}