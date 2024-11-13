#include<bits/stdc++.h>
using i64 = long long;
const int N = 1000;
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::array<int, 2> > a(n + 1);
	std::vector<std::vector<int> > b(N + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i][0];
		a[i][1] = i;
		b[a[i][0]].push_back(i);
	}
	std::sort(a.begin() + 1, a.end());
	std::vector<std::array<int, 2> > ans; // 值域
	auto dfs = [&](auto self, int l, int r, int now) -> void {
		if (l == r) {
			for (int i = now; i < l; i ++) {
				ans.push_back({1, i});
			}
			return ;
		}
		int mid = l + r >> 1;
		bool f = 0;
		for (int i = mid + 1; i <= r; i ++) {
			for (auto it : b[i]) {
				ans.push_back({2, it});
				f = 1;
			}
 		} // ++
 		if (f) {
	 		for (int i = now + 1; i < mid + 1; i ++) {
	 			ans.push_back({1, i});
	 		}
			self(self, mid + 1, r, mid + 1);
 		}
		self(self, l, mid, now);
	};
	dfs(dfs, 0, N, 0);
	std::cout << ans.size() << '\n';
	for (auto it : ans) {
		std::cout << it[0] << ' ' << it[1] << '\n';
	}
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