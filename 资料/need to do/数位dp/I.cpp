#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define i64 long long

const int N = 40;
int a[N];
i64 f[N][N * 1000];

i64 dfs(int len, bool limit, int sum) {
	if (sum < 0) return 0;
	// cut
	if (! len) return sum >= 0;
	if (! limit && f[len][sum] != -1) return f[len][sum];
	i64 res = 0;
	int end = limit ? a[len] : 9;
	for (int i = 0; i <= end; i ++) {
		res += dfs(len - 1, limit && i == end, sum - i * (1 << len - 1));
	}
	if (! limit) f[len][sum] = res;
	return res;
}
i64 dp(i64 n, i64 val) {
	int len = 0;
	while (n) {
		a[++ len] = n % 10;
		n /= 10;
	}
	return dfs(len, 1, val);
}
void solve() {
	int n = 1;
	std::cin >> n;
	memset(f, -1, sizeof f);
	for (int i = 1; i <= n; i ++) {
		
		i64 l, r;
		std::cin >> l >> r;

		i64 val = 0, op = 0;
		while (l) {
			val += (l % 10) * (1 << op);
			op ++;
			l /= 10;
		}
		std::cout << "Case #" << i << ": " << dp(r, val) << '\n';
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