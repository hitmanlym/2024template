#include<bits/stdc++.h>
using i64 = long long;

const int N = 255;
const int mod = 998244353;
#define int i64
int dp[N][N][N], f[N][N][N];
void solve() {
	int n;
	std::cin >> n; 
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			for (int k = 1; k <= n; k ++) {
				if (a[i] == a[j] && a[i] == a[k]) {
					dp[i][j][k] = (f[i - 1][j - 1][k - 1] + 1) % mod;
				}
				f[i][j][k] = dp[i][j][k]
						   + f[i - 1][j][k] + f[i][j - 1][k] + f[i][j][k - 1]
						   - f[i - 1][j - 1][k] - f[i - 1][j][k - 1] - f[i][j - 1][k - 1]
						   + f[i - 1][j - 1][k - 1];
				f[i][j][k] = (f[i][j][k] % mod + mod) % mod;
			}
		}
	}
	std::cout << f[n][n][n] << '\n';
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