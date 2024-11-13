#include<bits/stdc++.h>
using i64 = long long;

#define int i64
const int inf = 1e9 + 7;
void solve() {
    std::string s;
    std::cin >> s;
    int n = s.size();
    std::vector<std::vector<int> > dp(n + 1, std::vector<int>(n + 1));
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            if (s[i - 1] == s[n - j]) {
                dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    int ans = n - dp[n][n];
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