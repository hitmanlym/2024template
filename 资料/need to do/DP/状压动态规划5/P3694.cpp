#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int inf = 1e9;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n + 1);
	std::vector<int> S(1 << m); // set.
	std::vector<std::vector<int> > pre(m, std::vector<int>(n + 1));
	std::vector<int> num(m);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		a[i] --;
		num[a[i]] ++;
		pre[a[i]][i] ++;
		for (int j = 0; j < m; j ++) {
			pre[j][i] += pre[j][i - 1];
		}
	}
	for (int i = 0; i < (1 << m); i ++) {
		for (int j = 0; j < m; j ++) {
			if (i >> j & 1) {
				S[i] += num[j];
			}
		}
	}
	// 
	std::vector<int> dp(1 << m, inf);
	dp[0] = 0;
	for (int i = 0; i < (1 << m); i ++) {
		for (int j = 0; j < m; j ++) {
			if (i >> j & 1) { // erase j.
				int R = S[i];
				int L = R - num[j] + 1;
				dp[i] = std::min({
					dp[i],
					dp[i - (1 << j)] + num[j] - (pre[j][R] - pre[j][L - 1])
				});
			}
		}
	}
	int ans = dp[(1 << m) - 1];
	std::cout << ans << '\n';
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