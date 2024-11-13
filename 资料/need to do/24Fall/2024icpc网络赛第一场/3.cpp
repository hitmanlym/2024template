#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::vector<int> > a(n + 1);
	for (int i = 1; i <= n; i ++) {
		int l, r;
		std::cin >> l >> r;
		a[l].push_back(r);
	}
	for (int i = 1; i <= n; i ++) {
		std::sort(a[i].begin(), a[i].end());
	}
	
	int f = 1;
	int now = 1;
	while (now <= n) {
		if (! a[now].size()) {
			f = 0;
			break;
		}
		int op = a[now].back();
		if (! (op - now + 1) & 1) {
			f = 0;
			break;
		}
		for (int i = now; i < op; i ++) {
			if (i == now) {
				if (a[i].size() != 2 || a[i][0] != i + 1) {
					f = 0;
					break;
				}
			} else {
				if (a[i].size() != 1 || a[i][0] != i + 1) {
					f = 0;
					break;
				}
			}
		}
		now = op + 1;
	}
	std::cout << f << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}