#include<iostream>
#include<cstring>
#include<cmath>
#define i64 long long

const int N = 40;
int a[N];
i64 f[N][N];

i64 dfs(int len, bool limit, bool zero, int dig, int sum) { // zero == 1 : have zero prefix
	if (! len) return sum;
	if (! limit && ! zero && f[len][sum] != -1) return f[len][sum];
	i64 res = 0;
	int end = limit ? a[len] : 9;
	for (int i = 0; i <= end; i ++) {
		res += dfs(len - 1, limit && i == end, zero && i == 0, dig, (i == dig && (i || ! zero)) ? sum + 1 : sum);
	}
	if (! limit && ! zero) f[len][sum] = res;
	//std::cout << '\n' << "! " << dig << ' ' << len << ' ' << res << ' ' << sum << '\n'; 
	return res;
}
i64 dp(i64 n, int i) {
	memset(f, -1, sizeof f);
	int len = 0;
	while (n) {
		a[++ len] = n % 10;
		n /= 10;
	}
	return dfs(len, 1, 1, i, 0);
}
void solve() {
	i64 l, r;
	std::cin >> l >> r;
	for (int i = 0; i <= 9; i ++) {
		std::cout << dp(r, i) - dp(l - 1, i) << ' ';
	}
	std::cout << '\n';
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