#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n, k;
	std::cin >> n >> k;
	if (! (k & 1) || (k >= 2 * n)) {
		std::cout << -1 << '\n';
		return ;
	}
	auto dfs = [&](auto self, int L, int R, int y) -> void {
		if (y == 1) {
			for (int i = L; i <= R; i ++) {
				std::cout << i << ' ';
			}
			return ;
		}
		if (y == 2 * (R - L + 1) - 1) {
			for (int i = R; i >= L; i --) {
				std::cout << i << ' ';
			}
			return ;
		}
		int l = (R - L + 1) / 2, r = (R - L + 1) - l;

		int maxl = l * 2 - 1, maxr = r * 2 - 1;
		int mid = (L + R) >> 1;
		int opl = std::min(maxl, y - 2), opr = y - 1 - opl;

		self(self, mid + 1, R, opl);
		self(self, L, mid, opr);
	};
	dfs(dfs, 1, n, k);
	std::cout << '\n';
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