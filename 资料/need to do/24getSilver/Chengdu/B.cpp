#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 1e9 + 7;
const int N = 305;
int dp[N][N][N][4], use[N][N][N], S[N][N][N]; // n, a, b, (i - a - b)
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::string s;
	std::cin >> s;
	int A = 0, B = 0, C = 0, R = 0;
	for (auto c : s) {
		if (c == '?') R ++;
		else if (c == 'a') A ++;
		else if (c == 'b') B ++;
		else C ++;
	}
	s = " " + s;
	if (s[1] == '?') { // use...
		dp[1][1][0][1] = 1;
		dp[1][0][1][2] = 1;
		dp[1][0][0][3] = 1;
	} else if (s[1] == 'a') {
		dp[1][1][0][1] = 1;
	} else if (s[1] == 'b') {
		dp[1][0][1][2] = 1;
	} else if (s[1] == 'c') {
		dp[1][0][0][3] = 1;
	}
	auto add = [&](int &u, int v) -> void {
		u = (u + v) % mod;
	};
	for (int i = 2; i <= n; i ++) {
		for (int j = 0; j <= n; j ++) {
			for (int k = 0; k <= n - j; k ++) {
				int o = n - j - k;
				if (s[i] == '?') {
					if (j > 0) {
						add(dp[i][j][k][1], dp[i - 1][j - 1][k][2] + dp[i - 1][j - 1][k][3]);
					}
					if (k > 0) {
						add(dp[i][j][k][2], dp[i - 1][j][k - 1][1] + dp[i - 1][j][k - 1][3]);
					}
					if (o > 0) {
						add(dp[i][j][k][3], dp[i - 1][j][k][1] + dp[i - 1][j][k][2]);
					}
				} else if (s[i] == 'a') {
					if (j > 0) {
						add(dp[i][j][k][1], dp[i - 1][j - 1][k][2] + dp[i - 1][j - 1][k][3]);
					}
				} else if (s[i] == 'b') {
					if (k > 0) {
						add(dp[i][j][k][2], dp[i - 1][j][k - 1][1] + dp[i - 1][j][k - 1][3]);
					}
				} else if (s[i] == 'c') {
					if (o > 0) {
						add(dp[i][j][k][3], dp[i - 1][j][k][1] + dp[i - 1][j][k][2]);
					}
				}
			}
		}
	}
	// dp[n] [j][k][n - j - k]
	// 前缀...
	// ... use
	for (int i = 0; i <= n; i ++) {
		for (int j = 0; j <= n; j ++) {
			if (i >= A && j >= B && (n - i - j) >= C) {
				int sum = 0;
				for (int k = 1; k <= 3; k ++) {
					add(sum, dp[n][i][j][k]);
				}
				add(use[i - A][j - B][(n - i - j - C)], sum);
			}
		}
	}
	for (int i = 1; i <= n + 1; i ++) {
		for (int j = 1; j <= n + 1; j ++) {
			for (int k = 1; k <= n + 1; k ++) {
				add(S[i][j][k], S[i - 1][j][k] + S[i][j - 1][k] + S[i][j][k - 1]
					- S[i - 1][j - 1][k] - S[i - 1][j][k - 1] - S[i][j - 1][k - 1]
					+ S[i - 1][j - 1][k - 1] + use[i - 1][j - 1][k - 1]);
			}
		}
	}
	// use.
	while (k --) {
		int a, b, c;
		std::cin >> a >> b >> c;
		// // std::cout << 
		// int ans = 0;
		// for (int i = 0; i <= a; i ++) {
		// 	for (int j = 0; j <= b; j ++) {
		// 		for (int k = 0; k <= c; k ++) {
		// 			add(ans, use[i][j][k]);
		// 		}
		// 	}
		// }
		// // for (int i = 0; i <= a; i ++) {
		// // 	int low = 0;
		// // 	int O = std::max(0ll, C - i - c);
		// // 	if (O > std::min(b, C - i)) continue;
		// // 	if (O > 0) {
		// // 		low = pre[i][O - 1];
		// // 	}
		// // 	// std::cout << O << ' ' << i << ' ' << std::min(b, C - i) << '\n';
		// // 	ans = (ans + pre[i][std::min(b, C - i)]) % mod;
		// // 	ans = (ans - low) % mod;
		// // }
		// std::cout << (ans + mod) % mod << '\n';

		std::cout << (S[a + 1][b + 1][c + 1] + mod) % mod << '\n';
	}
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}
/*
6 3
??????
2 2 2
2 3 3
3 3 3

6 3
a?b??c
2 2 2
1 1 1
1 0 2
*/