#include<bits/stdc++.h>
using i64 = long long;
const int mod = 19650827;
#define int i64
void solve() {
	int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    std::vector<std::vector<std::array<int, 2> > > dp(n + 1, std::vector<std::array<int, 2 > >(n + 1));
    for (int i = 1; i <= n; i ++) {
        dp[i][i][0] = 1;
    }  
    for (int len = 2; len <= n; len ++) {
        for (int l = 1, r; r = l + len - 1, r <= n; l ++) {
            if (a[l] < a[l + 1]) {
                dp[l][r][0] = (dp[l][r][0] + dp[l + 1][r][0]) % mod;
            }
            if (a[l] < a[r]) {
                dp[l][r][0] = (dp[l][r][0] + dp[l + 1][r][1]) % mod;
            }
            if (a[r] > a[l]) {
                dp[l][r][1] = (dp[l][r][1] + dp[l][r - 1][0]) % mod;
            }
            if (a[r] > a[r - 1]) {
                dp[l][r][1] = (dp[l][r][1] + dp[l][r - 1][1]) % mod;
            }
        }
    }
    int ans = (dp[1][n][0] + dp[1][n][1]) % mod;
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