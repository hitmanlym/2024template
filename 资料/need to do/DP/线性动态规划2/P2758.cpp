#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
#define int i64
void solve() {
	std::string s, t;
    std::cin >> s >> t;
    int n = s.size(), m = t.size();

    std::vector<std::vector<int> > dp(n + 1, std::vector<int>(m + 1, mod));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i ++) {
        dp[i][0] = i;
    }
    for (int i = 1; i <= m; i ++) {
        dp[0][i] = i;
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            dp[i][j] = std::min({dp[i][j], dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1});
            // {s_i, t_{j - 1}}, {s_{i - 1}, t_j}, {s_{i - 1}, t_{j - 1}} // del/add del/add change 
        }
    }
    std::cout << dp[n][m] << '\n';
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