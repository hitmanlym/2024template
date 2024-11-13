#include<iostream>
#include<cstring>
#include<cmath>
#define i64 long long

const int N = 40;
int a[N];
i64 f[N][2];

i64 dfs(int len, bool limit, bool pre) { // zero == 1 : have zero prefix
	if (! len) return 1;
	if (! limit & f[len][pre] != -1) return f[len][pre];
	i64 res = 0;
	int end = limit ? a[len] : 9;
	for (int i = 0; i <= end; i ++) {
		if (pre && i == 9) continue;
		res += dfs(len - 1, limit && i == end, i == 4);
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
	memset(f, -1, sizeof f);
	int n;
	std::cin >> n;
	while (n --) {
		i64 x;
		std::cin >> x;
		std::cout << (x + 1) - dp(x) << '\n';
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