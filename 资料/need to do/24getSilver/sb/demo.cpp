#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 1e9 + 7;
int qmi(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) {
			res = 1ll * res * a % mod;
		} 
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return res;
}
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	std::vector<int> op;
	i64 sum = 0, num = 0;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		if (a[i] & 1) {
			sum += a[i];
		} else {
			while (a[i] % 2 == 0) {
				num ++;
				a[i] >>= 1;
			}
			op.push_back(a[i]);
			sum += a[i];
		}
		if (op.size()) {
			std::cout << (((sum - op.back()) + op.back() * qmi(2, num) % mod) % mod + mod) % mod << '\n';
		} else {
			std::cout << sum << '\n';
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