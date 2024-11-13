#include<bits/stdc++.h>
using i64 = long long;

#define int i64
const int inf = 1e9 + 7;
const int N = 105;
int dp[N][N][2];
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int> > a(n + 1, std::vector<int>(m + 1));
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            std::cin >> a[i][j];
        }
    }
    std::vector<std::vector<int > > dp(n + 1, std::vector<int >(m + 1));
    // 第 i 个 放置在 第 j 位置上，每次找 i - 1 个 放置在 1 -- j - 1 位置的最大值
    std::vector<int> max(m + 1);
    for (int i = 1; i <= n; i ++) {
        std::vector<int> it(m + 1);
        it[0] = -inf;
        for (int j = 1; j <= m; j ++) {
            dp[i][j] = max[j - 1] + a[i][j];
            it[j] = std::max(it[j - 1], dp[i][j]);
        }
        std::swap(max, it);
    }
    int ans = -inf;// niu
    for (int i = 1; i <= m; i ++) {
        ans = std::max(ans, dp[n][i]);
    }
    std::cout << ans << '\n';
    int o = n;
    std::vector<int> res(n + 1);
    while (o --) {
        for (int i = 1; i <= m; i ++) {
            if (dp[o + 1][i] == ans) {
                ans -= a[o + 1][i];
                res[o + 1] = i;
                break;
            }
        }
    }
    for (int i = 1; i <= n; i ++) {
        std::cout << res[i] << ' ';
    }
    std::cout << '\n';
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