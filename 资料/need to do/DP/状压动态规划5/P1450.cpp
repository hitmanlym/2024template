#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	std::vector<int> C(4);
	for (int i = 0; i < 4; i ++) {
		std::cin >> C[i];
	}
	int n;
	std::cin >> n;
	const int N = 1e5 + 10;
	std::vector<int> dp(N + 1);
	dp[0] = 1;
	for (int i = 0; i < 4; i ++) {
		for (int j = C[i]; j <= N; j ++) {
			dp[j] += dp[j - C[i]];
		}
	}
	while (n --) {
		std::vector<int> d(4);
		int s;
		for (int i = 0; i < 4; i ++) {
			std::cin >> d[i];
		}
		int ans = 0;
		std::cin >> s;
		for (int i = 0; i < (1 << 4); i ++) {
			int u = __builtin_popcount(i);
			int f = 1;
			if (u & 1) f = -1;
			int op = s;
			for (int j = 0; j < 4; j ++) {
				if (i >> j & 1) {
					op -= C[j] * (d[j] + 1);
				}
			}
			if (op < 0) continue;
			ans += f * dp[op];
		}
		std::cout << ans << '\n';
	}

} 
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}