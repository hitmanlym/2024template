#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
const int M = 501;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n + 1), b(m + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= m; i ++) {
		std::cin >> b[i];
	}
	std::vector<int> dp(M + 1);	
	i64 ans = 0;
	for (int tag = M - 1; tag >= 0; tag --) {
		std::vector<std::array<int, 2> > e;
		int num = 0;
		for (int i = 1; i <= m; i ++) {
			if (b[i] - tag >= 1) {
				e.push_back({b[i] - tag, 1});
				num ++;
			}
		}
		if (! num) continue;
		for (int i = 1; i <= n; i ++) {
			e.push_back({a[i], 0});
		}
		std::sort(e.begin(), e.end());
		int esiz = e.size();
		std::vector<std::vector<int> > f(esiz + 1, std::vector<int>(M + 1));
		f[esiz][0] = 1;
		for (int i = esiz - 1; i >= 0; i --) {
			if (e[i][1] == 1) {
				for (int j = M; j >= 1; j --) {
					f[i][j] = f[i + 1][j - 1];
				}
			} else {
				for (int j = M - 1; j >= 0; j --) {
					f[i][j] = (f[i + 1][j] + 1ll * (j + 1) * f[i + 1][j + 1] % mod) % mod;
				}
			}
		}
		for (int i = 0; i < num; i ++) {
			dp[tag] = (dp[tag] + f[0][i]) % mod;
		}
		/*std::cout << "!!! " << num << "\n";
		if (dp[tag]) {
			std::cout << "TAG : " << tag << '\n';
			std::cout << "      " << dp[tag] << '\n';
			for (int i = 0; i <= esiz; i ++) {
				for (int j = 0; j <= M; j ++) {
					std::cout << f[i][j] << ' ';
				}
				std::cout << '\n';
			}
		}*/
		//std::cout << dp[tag] << '\n';
		ans = (ans + 1ll * tag * (dp[tag] - dp[tag + 1]) % mod) % mod;
	}
	std::cout << (ans + mod) % mod << '\n';
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