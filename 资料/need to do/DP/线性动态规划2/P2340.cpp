#include<bits/stdc++.h>
using i64 = long long;

#define int i64
const int M = 4e5 + 10;
const int inf = 1e9 + 7;
void solve() {
    int n;
    std::cin >> n;
    std::vector<std::array<int, 2> > e(n + 1);
    int o = 0, p = 0;
    for (int i = 1; i <= n; i ++) {
        std::cin >> e[i][0] >> e[i][1];
    }
    std::vector<int> dp(M * 2 + 1, -inf);
    dp[M] = 0;

    for (int i = 1; i <= n; i ++) {
        if (e[i][0] > 0) {
            for (int j = M * 2; j >= e[i][0]; j --) {
                dp[j] = std::max(dp[j], dp[j - e[i][0]] + e[i][1]);
            }
        } else {
            for (int j = 0; j - e[i][0] <= M * 2; j ++) {
                dp[j] = std::max(dp[j], dp[j - e[i][0]] + e[i][1]);
            }
        }
    }
    int ans = 0;
    for (int i = M; i <= M * 2; i ++) {
        if (dp[i] >= 0) {
            ans = std::max(ans, i + dp[i] - M);
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