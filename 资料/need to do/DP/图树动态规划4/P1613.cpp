#include<bits/stdc++.h>
using i64 = long long;
const int N = 51;
bool dp[N][N][31]; // 2 ^ k
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int> > d(n + 1, std::vector<int>(n + 1, 1e9));
	for (int i = 1; i <= m; i ++) {
		int u, v;
		std::cin >> u >> v;
		dp[u][v][0] = 1;
		d[u][v] = 1;
	}
	for (int b = 1; b <= 30; b ++) {
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= n; j ++) {
				for (int k = 1; k <= n; k ++) {
					if (dp[i][k][b - 1] && dp[k][j][b - 1]) {
						dp[i][j][b] = 1;
						d[i][j] = 1;
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			for (int k = 1; k <= n; k ++) {
				if (d[i][j] > d[i][k] + d[k][j]) {
					d[i][j] = d[i][k] + d[k][j];
				}
			}
		}
	}
	int ans = d[1][n];
	std::cout << ans << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}