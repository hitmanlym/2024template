#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define i64 long long

const int N = 5e3 + 10, M = 61, mod = 1e9 + 7;
int a[N], m;
i64 f[N][M + 1][M + 1];
i64 dd[N];
i64 dfs(int len, bool limit, int d, int sum) {
	// cut
	if (! len) return d == 0;
	if (! limit && f[len][d][sum] != -1) return f[len][d][sum];
	i64 res = 0;
	int end = limit ? a[len] : 9;
	for (int i = 0; i <= end; i ++) {
		res += dfs(len - 1, 
			limit && i == end, 
			((d + sum * i - i * dd[len - 1]) % m + m) % m, 
			(sum + i) % m);
		res %= mod;
	}
	if (! limit) f[len][d][sum] = res;
	return res % mod;
}
i64 dp(std::string &n) {
	int len = n.size();
	for (int i = 1; i <= len; i ++) {
		a[i] = n[len - i] - '0';
	}
	for (int i = 1; i <= len; i ++) {
		dd[i] = dd[i - 1] * 10 % m;
	}
	for (int i = 0; i <= len; i ++) {
		for (int j = 0; j <= m; j ++) {
			for (int k = 0; k <= m; k ++) {
				f[i][j][k] = -1;
			}
		}
	}
	return dfs(len, 1, 0, 0);
}
void solve() {
	int n = 1;
	std::cin >> n;
	dd[0] = 1;

	auto check = [&](std::string s) -> bool {
		int x = 0, fx = 0, sum = 0;
		int n = s.size();
		for (int i = 0; i < n; i ++) {
			x = (x * 10 + s[i] - '0') % m;
			fx = (fx + sum * (s[i] - '0')) % m;
			sum = (sum + (s[i] - '0')) % m;
		}
		return x == fx;
	};

	for (int i = 1; i <= n; i ++) {
		
		std::string l, r;
		std::cin >> l >> r >> m;
		int fix = 0;
		// check(l) -> fix + 1
		if (check(l)) {
			fix = 1;
		}
		std::cout << ((dp(r) - dp(l) + fix) % mod + mod) % mod << '\n';
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	//std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}