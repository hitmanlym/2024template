#include<iostream>
#include<cstring>
#include<cmath>
#define i64 long long

const int N = 40;
int mod;
int a[N];
i64 f[N][400][400];

i64 dfs(int len, bool limit, bool zero, int sum, int num) {
	// cut
	if (num + len * 9 < mod) return 0;
	if (! len) return num == mod && sum == 0;
	if (! limit && ! zero && f[len][sum][num] != -1) return f[len][sum][num];
	i64 res = 0;
	int end = limit ? a[len] : 9;
	for (int i = 0; i <= end; i ++) {
		res += dfs(len - 1, limit && i == end, zero && i == 0,
			(i || ! zero) ? (sum * 10 + i) % mod : sum, 
			(i || ! zero) ? num + i : num);
	}
	if (! limit && ! zero) f[len][sum][num] = res;
	return res;
}
i64 dp(i64 n) {
	int len = 0;
	while (n) {
		a[++ len] = n % 10;
		n /= 10;
	}
	i64 res = 0;
	for (mod = 1; mod <= len * 9; mod ++) {
		memset(f, -1, sizeof f);
		res += dfs(len, 1, 1, 0, 0);
	}
	return res;
}
void solve() {
	int n = 1;
	//std::cin >> n;
	while (n --) {
		i64 l, r;
		std::cin >> l >> r;
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