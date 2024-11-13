#include<bits/stdc++.h>
using i64 = long long;
const int inf = 1e9 + 7;
#define int i64
void solve() {
	int n, m;
    std::string s, t;
    std::cin >> n >> s >> m >> t;
    std::vector<int> a(n + 1), b(m + 1);
    std::map<char, int> mp;
    mp['A'] = 1;
    mp['C'] = 2;
    mp['G'] = 3;
    mp['T'] = 4;
    for (int i = 1; i <= n; i ++) {
        a[i] = mp[s[i - 1]];
    }
    for (int i = 1; i <= m; i ++) {
        b[i] = mp[t[i - 1]];
    }
    std::vector<std::vector<int> > it(6, std::vector<int>(6));
    std::map<std::array<int, 2>, int> u;
    u[{1, 2}] = -1; u[{1, 3}] = -2; u[{1, 4}] = -1;
    u[{1, 5}] = -3; u[{2, 3}] = -3; u[{2, 4}] = -2;
    u[{2, 5}] = -4; u[{3, 4}] = -2; u[{3, 5}] = -2;
    u[{4, 5}] = -1;

    for (int i = 1; i <= 5; i ++) {
        for (int j = 1; j <= 5; j ++) {
            
            int a = std::min(i, j), b = std::max(i, j);
            it[i][j] = u[{a, b}];

            if (i == j) it[i][j] = 5;
        }
    }

    std::vector<std::vector<int> > dp(n + 1, std::vector<int>(m + 1, -inf));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i ++) {
        dp[i][0] = dp[i - 1][0] + it[a[i]][5];
    }
    for (int i = 1; i <= m; i ++) {
        dp[0][i] = dp[0][i - 1] + it[b[i]][5];
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            dp[i][j] = std::max({
                dp[i - 1][j] + it[a[i]][5],
                dp[i][j - 1] + it[b[j]][5],
                dp[i - 1][j - 1] + it[a[i]][b[j]]
            });
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