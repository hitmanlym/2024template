#include<iostream>
#include<cstring>
using i64 = long long;

const int N = 10;
int a[N];
i64 f[N][2];

i64 dfs(int len, bool limit, bool pre) {
	if (! len) return 1;
	if (! limit && f[len][pre] != -1) return f[len][pre];
	i64 res = 0;
	int end = limit ? a[len] : 9;
	for (int i = 0; i <= end; i ++) {
		if (i == 4 || pre && i == 2) continue;
		res += dfs(len - 1, limit && i == end, i == 6);
	}
	if (! limit) f[len][pre] = res;
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
	memset(f, -1, sizeof f);
	while (std::cin >> l >> r) {
		if (! l) {
			break;
		}
		std::cout << dp(r) - dp(l - 1) << '\n';
	}
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