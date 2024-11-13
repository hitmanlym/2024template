#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<char> > e(n + 1, std::vector<char>(m + 1));
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			std::cin >> e[i][j];
		}
	} 
	int ans = 0;
	for (int i = 2; i <= n; i ++) {
		for (int j = 1; j < m; j ++) {
			char c = e[i][j], p = e[i - 1][j];
			if (p == e[i - 1][j + 1] && p == e[i][j + 1] && p != c) {
				if (c == 'p' && p == 'c') {
					ans ++;
				}
			}
		}
	}
	std::cout << ans << '\n';
}
int main() {
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}