#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	if (n == 1 || n % 4 == 0) {
		std::cout << "impossible\n";
		return ;
	}
	std::vector<int> a(n);
	for (int i = 0; i < n; i ++) {
		a[i] = i;
	}
	std::swap(a[0], a[1]);
	for (int i = 4; i < n; i += 4) {
		std::swap(a[i], a[i - 1]);
	}
	for (int i = 0; i < n; i ++) {
		std::cout << a[i] << ' ';
	}
	std::cout << '\n';
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