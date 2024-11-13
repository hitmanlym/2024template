#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	std::sort(a.begin() + 1, a.end());
	int ans = 1;
	for (int i = 1; i <= n; i ++) {
		if (a[i] - (i - 1) <= 0) {
			std::cout << 0 << '\n';
			return ;
		}
		ans = 1ll * ans * (a[i] + 1 - i) % mod;
	}
	std::cout << ans << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}