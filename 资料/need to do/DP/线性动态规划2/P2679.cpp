#include<bits/stdc++.h>
using i64 = long long;

#define int i64
const int mod = 1e9 + 7;
const int N = 1e3 + 10, M = 2e2 + 10;
int dp[2][N][M][2];
void solve() {
	int n, m, k;
    std::cin >> n >> m >> k;
    std::string s, g;
    std::cin >> s >> g;
    dp[0][0][0][0] = 1;
    for (int i = 1; i <= n; i ++) {
        int o = i & 1;
        dp[o][0][0][0] = 1;
        for (int j = 1; j <= m; j ++) {
            for (int t = 1; t <= k; t ++) {
                dp[o][j][t][0] = dp[o][j][t][1] = 0;
                dp[o][j][t][0] = (dp[o ^ 1][j][t][0] + dp[o ^ 1][j][t][1]) % mod;
                if (s[i - 1] == g[j - 1]) {
                    dp[o][j][t][1] = (dp[o ^ 1][j - 1][t][1] + 
                        dp[o ^ 1][j - 1][t - 1][0] + dp[o ^ 1][j - 1][t - 1][1]) % mod;
                }
            }
        }
    }
    int ans = (dp[n & 1][m][k][0] + dp[n & 1][m][k][1]) % mod;
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