#include<iostream>
#include<cstring>
#include<cmath>
#define i64 long long

const int N = 40;
int mod;
int a[N];
i64 f[N][1005];

i64 dfs(int len, bool limit, int m) {
	if (! len) return m % mod == 0;
	if (! limit && f[len][m] != -1) return f[len][m];
	i64 res = 0;
	int end = limit ? a[len] : 9;
	for (int i = 0; i <= end; i ++) {
		res += dfs(len - 1, limit && i == end, m + i);
	}
	if (! limit) f[len][m] = res;
	return res;
}
i64 dp(i64 n) {
	
	int len = 0;
	while (n) {
		a[++ len] = n % 10;
		n /= 10;
	}
	return dfs(len, 1, 0);
}
void solve() {
	i64 l, r;
	while (std::cin >> l >> r >> mod) {
		memset(f, -1, sizeof f);

			std::cout << dp(r) - dp(l - 1) << '\n';
			
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