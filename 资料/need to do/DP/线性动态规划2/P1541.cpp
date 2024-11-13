#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
#define int i64

const int N = 43;
int dp[N][N][N][N];
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> v(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> v[i];
    }
    std::vector<int> op(5);
    for (int i = 1; i <= m; i ++) {
        int x;
        std::cin >> x;
        op[x] ++;
    }
    for (int a = 0; a <= op[1]; a ++) {
        for (int b = 0; b <= op[2]; b ++) {
            for (int c = 0; c <= op[3]; c ++) {
                for (int d = 0; d <= op[4]; d ++) {
                    int x = 1 + a * 1 + b * 2 + c * 3 + d * 4;
                    int res = 0;
                    if (a) res = std::max(res, dp[a - 1][b][c][d]);
                    if (b) res = std::max(res, dp[a][b - 1][c][d]);
                    if (c) res = std::max(res, dp[a][b][c - 1][d]);
                    if (d) res = std::max(res, dp[a][b][c][d - 1]);
                    dp[a][b][c][d] = res + v[x];
                }
            }
        }
    }
    std::cout << dp[op[1]][op[2]][op[3]][op[4]] << '\n';
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