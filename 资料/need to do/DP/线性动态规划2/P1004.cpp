#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
#define int i64

const int N = 10;
int dp[N * 2][N][N];
void solve() {
	int n;
    std::cin >> n;
    std::vector<std::vector<int> > e(n + 1, std::vector<int>(n + 1));

    int x, y, z;
    std::cin >> x >> y >> z;
    while (x) {
        e[x][y] = z;
        std::cin >> x >> y >> z;
    }
    for (int k = 2; k <= n + n; k ++) {
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= n; j ++) {
                int x = k - i, y = k - j;
                if (x < 1 || y < 1 || x > n || y > n) continue;
                int w = e[i][x];
                if (i != j) w += e[j][y];
                dp[k][i][j] = std::max({
                    dp[k - 1][i][j], dp[k - 1][i - 1][j], dp[k - 1][i][j - 1], dp[k - 1][i - 1][j - 1]
                }) + w;
            }
        }
    }
    std::cout << dp[n + n][n][n] << '\n';
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