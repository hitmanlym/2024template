#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n + 1), pre(n + 1), suf(n + 2);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		pre[i] = pre[i - 1] ^ a[i];
	}
	for (int i = n; i >= 1; i --) {
		suf[i] = suf[i + 1] ^ a[i];
	}
	std::vector<std::array<int, 3> > q(m);
	std::vector<std::array<int, 2> > replace;
	for (int i = 0; i < m; i ++) {
		std::cin >> q[i][0];
		if (q[i][0] == 0) {
			std::cin >> q[i][1] >> q[i][2];
		}
	}
	int add = 0, B = std::sqrt(n) * 2;
	for (int i = 0; i < m; i ++) {
		if (q[i][0] == 2) {
			if (add) {
				for (auto it : replace) {
					a[it[0]] = a[it[1]];
				}
				replace.clear();
				for (int i = 1; i <= n; i ++) {
					a[i] += add;
					add = 0;
				}
				for (int i = 1; i <= n; i ++) {
					pre[i] = pre[i - 1] ^ a[i];
				}
				for (int i = n; i >= 1; i --) {
					suf[i] = suf[i + 1] ^ a[i];
				}
			} /*else if (replace.size() > B){
				for (auto it : replace) {
					a[it[0]] = a[it[1]];
				}
				replace.clear();
				for (int i = 1; i <= n; i ++) {
					pre[i] = pre[i - 1] ^ a[i];
				}
				for (int i = n; i >= 1; i --) {
					suf[i] = suf[i + 1] ^ a[i];
				}
			}*/
			if (! replace.size()) {
				std::cout << pre[n] << '\n';
				continue;
			}
			int ans = 0;
			for (auto it : replace) {
				ans = ans ^ pre[it[0] - 1];
				ans = ans ^ suf[it[0] + 1];
				ans = ans ^ it[1];
			}
			std::cout << ans << '\n';
		} else {
			if (q[i][0] == 1) {
				for (auto it : replace) {
					a[it[0]] = a[it[1]] - add;
				}
				replace.clear();
				add ++;
			} else {
				replace.push_back({q[i][1], q[i][2]});
			}
		}
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