#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 1e9 + 7;
const int N = 55;
int c[N][N][N][3];
void solve() {
	int n, T;
	std::cin >> n >> T;
	std::vector<std::vector<int> > a(3);
	for (int i = 1; i <= n; i ++) {
		int t, op;
		std::cin >> t >> op;
		a[op - 1].push_back(t);
	} 
	int A = a[0].size(), B = a[1].size(), C = a[2].size();
	std::vector<std::vector<int> > f(A + 2, std::vector<int>(T + 1));
	std::vector<std::vector<std::vector<int> > >
		g(B + 2, std::vector<std::vector<int> > (C + 2, std::vector<int>(T + 1)));
	f[0][0] = 1;
	g[0][0][0] = 1;
	for (int i = 0; i < A; i ++) {
		for (int j = A; j >= 0; j --) {
			for (int t = T; t >= a[0][i]; t --) {
				(f[j + 1][t] += f[j][t - a[0][i]]) % mod;
			}
		}
	}
	//std::cout << f[1][1] << '\n';
	for (int i = 0; i < B; i ++) {
		for (int j = B; j >= 0; j --) {
			for (int k = C; k >= 0; k --) {
				for (int t = T; t >= a[1][i]; t --) {
					(g[j + 1][k][t] += g[j][k][t - a[1][i]]) % mod;
				}
			}
		}
	}
	for (int i = 0; i < C; i ++) {
		for (int j = B; j >= 0; j --) {
			for (int k = C; k >= 0; k --) {
				for (int t = T; t >= a[2][i]; t --) {
					(g[j][k + 1][t] += g[j][k][t - a[2][i]]) % mod;
				}
			}
		}
	}
	//std::cout << g[1][1][2] << '\n';
	c[1][0][0][0] = c[0][1][0][1] = c[0][0][1][2] = 1;
	for (int i = 0; i <= A; i ++) {
		for (int j = 0; j <= B; j ++) {
			for (int k = 0; k <= C; k ++) {
				(c[i + 1][j][k][0] += (c[i][j][k][1] + c[i][j][k][2]) % mod) % mod;
				(c[i][j + 1][k][1] += (c[i][j][k][0] + c[i][j][k][2]) % mod) % mod;
				(c[i][j][k + 1][2] += (c[i][j][k][0] + c[i][j][k][1]) % mod) % mod;
			}
		}
	}
	std::vector<int> fac(n + 1);
	fac[0] = 1;
	for (int i = 1; i <= n; i ++) {
		fac[i] = 1ll * fac[i - 1] * i % mod;
	}
	int ans = 0;
	for (int i = 0; i <= A; i ++) {
		for (int j = 0; j <= B; j ++) {
			for (int k = 0; k <= C; k ++) {
				for (int t = 0; t <= T; t ++) {
					(ans += 
						1ll * fac[i] * fac[j] % mod * fac[k] % mod
							* (1ll * c[i][j][k][0] + c[i][j][k][1] + c[i][j][k][2]) % mod
							* f[i][t] % mod * g[j][k][T - t] % mod) % mod;

					//std::cout << "?? " << i << ' ' << j << ' ' << k << ' ' << t << '\n';
					//std::cout << "!! " << f[i][t] << ' ' << g[j][k][T - t] << '\n';
				}
			}
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