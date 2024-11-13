#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int inf = 1e18;
void solve() {
	int n;
	std::cin >> n;
	std::string s;
	std::cin >> s;
	std::vector<int> a;
	std::deque<int> b;
	for (int i = 0; i < n; i ++) {
		if (s[i] == '0') {
			a.push_back(i + 1);
		} else {
			b.push_back(i + 1);
		}
	}
	std::vector<bool> vis(n + 1);
	int sum = n * (n + 1) / 2;
	for (int i = n; i >= 1; i --) {
		if (vis[i]) continue;

		if (s[i - 1] == '1') {

			b.pop_back();

			if (a.size()) {
				sum -= i;
				int u = a.back();
				a.pop_back();
				vis[u] = 1;
			} else {
				if (b.size()) {
					sum -= i;
					int u = b.front();
					b.pop_front();
					vis[u] = 1;
				}
			}
		} else {
			a.pop_back();
		}
	}
	std::cout << sum << '\n';
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