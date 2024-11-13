#include<iostream>
#include<cstring>
#include<cmath>
#define i64 long long

const int N = 100;
int k;
int a[N];
i64 f[11][N][1 << 11];

i64 dfs(int len, bool limit, bool zero, int st) {
	if (! len) return st == 0;
	if (! limit && ! zero && f[k][len][st] != -1) return f[k][len][st];
	i64 res = 0;
	int end = limit ? a[len] : k - 1;
	for (int i = 0; i <= end; i ++) {
		res += dfs(len - 1, limit && i == end, zero && i == 0, 
			(i || ! zero) ? (st ^ (1 << i)) : st);
	}
	if (! limit && ! zero) f[k][len][st] = res;
	return res;
}
i64 dp(i64 n) {
	int len = 0;
	while (n) {
		a[++ len] = n % k;
		n /= k;
	}
	int st = 0;
	return dfs(len, 1, 1, st);
}
void solve() {
	int n;
	std::cin >> n;
	memset(f, -1, sizeof f);
	while (n --) {
		i64 l, r;
		std::cin >> k >> l >> r;
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