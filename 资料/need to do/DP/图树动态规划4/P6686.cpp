#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int N = 2e5 + 10;
const int mod = 998244353;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), b(N + 1), sum(N + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		b[a[i]] ++;
	}
	for (int i = 1; i <= N; i ++) {
		sum[i] = sum[i - 1] + b[i];
	}

	int ans = 0;
	for (int i = 1; i <= N; i ++) {
		if (b[i] < 2) continue;
		int R = std::min(2 * i - 1, N);
		ans += (sum[R] - b[i]) * b[i] * (b[i] - 1) / 2;
		ans %= mod;
		if (b[i] > 2) {
			ans += b[i] * (b[i] - 1) * (b[i] - 2) / 6;
			ans %= mod;
		}
	}
	std::cout << ans << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}