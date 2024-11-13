#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int a, b;
	std::cin >> a >> b;
	int l = std::sqrt(std::min(a, b));
	int r = std::sqrt(a + b);
	int ans = 1e9;
	for (int i = l; i <= r * 2; i ++) {
		ans = std::min(ans, (a + i - 1) / i + (b + i - 1) / i + i - 1);
	}
	std::cout << ans << '\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}