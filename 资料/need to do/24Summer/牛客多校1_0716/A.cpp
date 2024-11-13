#include<bits/stdc++.h>
using i64 = long long;
#define int i64
int mod;

void solve() {
	int n, m;
	std::cin >> n >> m >> mod;
    std::vector<int> p(n * m);
    p[0] = 1;
    for (int i = 1; i < n * m; i ++) {
        p[i] = p[i - 1] * 2 % mod; 
    }
	int ans = 0;
    std::vector<std::vector<int> > C(n + 1, std::vector<int>(n + 1));
    C[0][0] = 1;
    for (int i = 1; i <= n; i ++) {
        C[i][0] = 1;
        for (int j = 1; j <= n; j ++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
        }
    }
    std::vector<std::vector<std::array<int, 2> > > dp(n + 1, std::vector<std::array<int, 2> >(m + 1));
    for (int i = 1; i <= n; i ++) {
        dp[i][0][0] = 1;
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j < m; j ++) {
            dp[i][j][0] = dp[i][j - 1][0] * (p[i] - 1) % mod;
            dp[i][j][1] = (dp[i][j - 1][0] + dp[i][j - 1][1] * p[i] % mod) % mod;
        }
    }
    std::vector<std::vector<int> > f(n + 1, std::vector<int>(m));
    std::vector<int> pick(m, 1);
    for (int i = 1; i <= n; i ++) {
        std::vector<int> op(m);
        for (int j = 1; j < m; j ++) {
            f[i][j] += pick[j - 1];
            op[j] = op[j - 1] + f[i][j] * p[j];
        }
        pick = op;
        for (int i = 1; i < m; i ++) {
            std::cout << op[i] << ' ';
        }
        std::cout << '\n';
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j < m; j ++) {
            std::cout << f[i][j] << ' ';
        }
        std::cout << '\n';
    }
    int last = 0;
	for (int i = 1; i <= n; i ++) {
        int a = p[(n - i) * (m - 1)] * C[n][i] % mod;
        ans = (ans + a * (p[i * (m - 1)] - dp[i][m - 1][1]) % mod) % mod; // 满足的 - 唯一的
        
        (last += f[i][m - 1]) % mod;
        ans = (ans - last) % mod;

        //std::cout << last << '\n';
	}
	std::cout << (ans + mod) % mod << '\n';
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