#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 1e9 + 7;

void solve() {
	int n, c;
    std::cin >> n >> c;
    std::vector<int> a(n + 1), b(n + 1), sum(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i] >> b[i];
        sum[i] = sum[i - 1] + b[i];
    }
    std::vector<std::vector<std::array<int, 2> > > 
        dp(n + 1, std::vector<std::array<int, 2> >(n + 1, {mod, mod}));
    dp[c][c][0] = dp[c][c][1] = 0;

    for (int len = 2; len <= n; len ++) {
        for (int l = 1, r; r = l + len - 1, r <= n; l ++) {
            dp[l][r][0] = std::min({
                dp[l + 1][r][0] + (a[l + 1] - a[l]) * (sum[n] - sum[r] + sum[l]),
                dp[l + 1][r][1] + (a[r] - a[l]) * (sum[n] - sum[r] + sum[l])
            });
            dp[l][r][1] = std::min({
                dp[l][r - 1][1] + (a[r] - a[r - 1]) * (sum[n] - sum[r - 1] + sum[l - 1]),
                dp[l][r - 1][0] + (a[r] - a[l]) * (sum[n] - sum[r - 1] + sum[l - 1])
            });
        }
    }
    int ans = std::min(dp[1][n][0], dp[1][n][1]);
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