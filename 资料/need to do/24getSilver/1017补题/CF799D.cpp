#include<bits/stdc++.h>
using i64 = long long;
const int inf = 1e9;
void solve() {
	int a, b, c, d, n;
	std::cin >> a >> b >> c >> d >> n;
	// 最大的22个左右吧，剩下的用 2
	std::vector<int> y;
	int num = 0;
	for (int i = 1; i <= n; i ++) {
		int x;
		std::cin >> x;
		if (x == 2) num ++;
		else y.push_back(x);
	}
	std::sort(y.begin(), y.end(), [&](auto u, auto v) {
		return u > v;
	});
	int res = inf;
	while (y.size() > 22) y.pop_back(); // 一定能覆盖掉啊？

	if (a > b) std::swap(a, b);
	if (c > d) std::swap(c, d);

	int siz = y.size();
	for (int i = 0; i < (1 << siz); i ++) {
		for (int k = 0; k < 2; k ++) {
			i64 Nc = c, Nd = d;
			if (k) std::swap(Nc, Nd);
			int ans = 0;
			for (int j = 0; j < siz; j ++) {
				if (i >> j & 1) {
					if (Nc < a) {
						Nc *= y[j];
						ans ++;
					}
				} else {
					if (Nd < b) {
						Nd *= y[j];
						ans ++;
					}
				}
			}
			int need = 0;
			while (Nc < a) {
				need ++;
				Nc *= 2;
			} 
			while (Nd < b) {
				need ++;
				Nd *= 2;
			}
			if (num >= need) {
				res = std::min(res, ans + need);
			}
		}
	}
	if (res == inf) {
		std::cout << -1 << '\n';
	} else {
		std::cout << res << '\n';
	}
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}