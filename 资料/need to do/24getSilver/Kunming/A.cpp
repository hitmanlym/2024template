#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, m, k;
	std::cin >> n >> m >> k;
	std::vector<std::vector<int> > a(n + 1, std::vector<int>(m + 2)), b(n + 1, std::vector<int>(m + 1));
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i][0];
		for (int j = 1; j <= m; j ++) {
			std::cin >> a[i][j];
		}
		a[i][m + 1] = i;
	}
	std::sort(a.begin(), a.end(), [&](auto x, auto y) {
		return x[0] < y[0];
	});

	int o = -1, max = -1;
	for (int i = 1; i <= n; i ++) {
		if (a[i][0] != a[i - 1][0]) {
			o = max;
			max = 0;
		}	
		int sum = 0;
		for (int j = 1; j <= m; j ++) {
			if (a[i][j] != -1) sum += a[i][j];
		}
		for (int j = 1; j <= m; j ++) {
			if (a[i][j] != -1) continue;
			if (sum >= o + 1) {
				a[i][j] = 0;
				continue;
			}
			a[i][j] = std::min(o + 1 - sum, k);
			sum += a[i][j];
		}
		if (sum < o + 1) {
			std::cout << "No\n";
			return ;
		}
		max = std::max(max, sum);
	}
	std::cout << "Yes\n";
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			b[a[i][m + 1]][j] = a[i][j];
		}
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			std::cout << b[i][j] << ' ';
		}
		std::cout << '\n';
	}
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