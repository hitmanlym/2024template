#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define i64 long long

const int N = 40, M = 2520;
int a[N];
int p[M + 1], idx = 0;
i64 f[N][50][M + 1];

i64 dfs(int len, bool limit, int lcm, int mod) {
	// cut
	if (! len) return mod % lcm == 0;
	if (! limit && f[len][p[lcm]][mod] != -1) return f[len][p[lcm]][mod];
	i64 res = 0;
	int end = limit ? a[len] : 9;
	for (int i = 0; i <= end; i ++) {
		res += dfs(len - 1, limit && i == end, (i == 0) ? lcm : lcm * i / std::__gcd(i, lcm), (mod * 10 + i) % M);
	}
	if (! limit) f[len][p[lcm]][mod] = res;
	return res;
}
i64 dp(i64 n) {
	int len = 0;
	while (n) {
		a[++ len] = n % 10;
		n /= 10;
	}
	i64 res = 0;
	return dfs(len, 1, 1, 0);
}
void solve() {
	int n = 1;
	std::cin >> n;
	memset(f, -1, sizeof f);
	for (int i = 1; i <= M; i ++) {
		if (M % i == 0) {
			p[i] = ++ idx;
		}
	}
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