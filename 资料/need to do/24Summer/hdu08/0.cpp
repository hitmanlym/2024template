#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int ans = 0, cnt = 0;
	for (int i = 0; i < 8; i ++) {
		for (int j = 0; j < 8; j ++) {
			for (int k = 0; k < 8; k ++) {
				ans = std::max({(i ^ j) + (i ^ k) + (j ^ k), ans});
				if ((i ^ j) + (i ^ k) + (j ^ k) == 14) {
					std::cout << i << ' ' << j << ' ' << k << '\n';
					cnt ++;
				}
			}
		}
	}
	std::cout << ans << ' ' << cnt << '\n';
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