#include<bits/stdc++.h>
using i64 = long long;

const int N = 10;
i64 dp[N][N * N][1024];
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> ok, cnt(1 << n);
	for (int i = 0; i < (1 << n); i ++) {
		cnt[i] = __builtin_popcount(i);
		if (! (i & ((i << 1) | (i >> 1)))) {
			ok.push_back(i);
		}
	}
	dp[0][0][0] = 1;
	for (int i = 1; i <= n; i ++) {
		for (auto st : ok) {
			for (auto lst : ok) {
				if (st & (lst | (lst << 1) | (lst >> 1))) continue;
				for (int j = cnt[st]; j <= k; j ++) {
					dp[i][j][st] += dp[i - 1][j - cnt[st]][lst];
				}
			}
		}
	}
	i64 ans = 0;
	for (auto st : ok) {
		ans += dp[n][k][st];
	}
	std::cout << ans << '\n';
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