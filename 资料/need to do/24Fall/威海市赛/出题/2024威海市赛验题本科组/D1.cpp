#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
void solve() {
	int n, m;
	std::cin >> n >> m;
	int k = (m + 1) / 2;
	std::vector<std::array<int, 2> > dp(k + 1);
	dp[0][0] = 1;
	dp[0][1] = 0;
	//std::cout << "?\n";
	for (int i = 1; i <= n; i ++) {
		if (i & 1) { // 奇数 + 前位偶数
			for (int j = std::min(k, i / 2); j >= 0; j --) {
				dp[j + 1][1] = (dp[j + 1][1] + dp[j][0]) % mod;
			}
		} else { // 偶数 + 前位奇数
			for (int j = std::min(k, i / 2); j >= 0; j --) {
				dp[j][0] = (dp[j][0] + dp[j][1]) % mod;
			}
		}
	}
	//std::cout << "?\n";
	std::cout << dp[k][m & 1] << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}