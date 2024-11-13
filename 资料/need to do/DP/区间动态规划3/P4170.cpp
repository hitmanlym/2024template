#include<bits/stdc++.h>
using i64 = long long;
const int mod = 19650827;
#define int i64
void solve() {
	std::string s;
    std::cin >> s;
    int n = s.size();
    s = " " + s;
    std::vector<std::vector<int> > dp(n + 1, std::vector<int>(n + 1, mod));
    for (int i = 1; i <= n; i ++) {
        dp[i][i] = 1;
        if (i + 1 <= n) {
            if (s[i] == s[i + 1]) dp[i][i + 1] = 1;
            else dp[i][i + 1] = 2;
        }
    }
    for (int len = 3; len <= n; len ++) {
        for (int l = 1, r; r = l + len - 1, r <= n; l ++) {
            if (s[l] == s[r]) {
                dp[l][r] = std::min(dp[l + 1][r], dp[l][r - 1]);
            }
            for (int k = l; k < r; k ++) {
                dp[l][r] = std::min(dp[l][r], dp[l][k] + dp[k + 1][r]);
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