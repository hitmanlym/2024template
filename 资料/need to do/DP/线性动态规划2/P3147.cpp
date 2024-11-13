#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
#define int i64

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    std::vector<std::vector<int> > dp(60, std::vector<int>(n + 2));
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
        dp[a[i]][i] = i + 1;
    }
    int ans = 0;
    for (int i = 2; i < 60; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (! dp[i][j]) {
                dp[i][j] = dp[i - 1][dp[i - 1][j]];
            }
            if (dp[i][j]) {
                ans = i;
            }
        }
    }
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