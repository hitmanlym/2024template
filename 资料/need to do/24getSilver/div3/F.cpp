#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 1e9 + 7;
void solve() {
	int n, k;
	std::cin >> n >> k;
	n %= mod;
	int a = 1, b = 1, c;
	if (k == 1) {
		std::cout << n << '\n';
		return ;
	}
	for (int i = 3; ; i ++) {
		c = (a + b) % k;
		a = b;
		b = c;
		if (c == 0) {
			std::cout << n * i % mod << '\n';
			return ;
		}
	}
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}