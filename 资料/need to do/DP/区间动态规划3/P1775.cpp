#include<bits/stdc++.h>
using i64 = long long;
const int inf = 998244353;
#define int i64
void solve() {
	int n;
    std::cin >> n;
    std::vector<int> a(n + 1), sum(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    std::vector<std::vector<int> > dp(n + 1, std::vector<int>(n + 1, inf));
    for (int i = 1; i <= n; i ++) {
        dp[i][i] = 0;
    }
    for (int len = 2; len <= n; len ++) {
        for (int l = 1, r; r = l + len - 1, r <= n; l ++) {
            for (int k = l; k < r; k ++) {
                dp[l][r] = std::min(dp[l][r], dp[l][k] + dp[k + 1][r] + sum[r] - sum[l - 1]);
            }
        }
    }
    std::cout << dp[1][n] << '\n';
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