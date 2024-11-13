#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int inf = 1e17;
void solve() {
	int n, m, k;
	std::cin >> n >> m >> k;
	std::string s;
	std::cin >> s;
	int x = n + 1, y = m + 1;
	std::vector<std::vector<int> > b(n * 2 + 1, std::vector<int>(m * 2 + 1));
	b[x][y] = 1;
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	int nx = 0, ny = 0;
	for (auto c : s) {
		if (c == 'U') {
			nx ++;
			x ++;
		} else if (c == 'D') {
			nx --;
			x --;
		} else if (c == 'L') {
			ny ++;
			y ++;
		} else {
			ny --;
			y --;
		}
		x1 = std::max(x1, nx);
		x2 = std::min(x2, nx);
		y1 = std::max(y1, ny);
		y2 = std::min(y2, ny);
		if (x < 0 || x > 2 * n || y < 0 || y > 2 * m) continue;
		b[x][y] = 1;
	}
	// for (int i = 1; i <= n * 2; i ++) {
	// 	for (int j = 1; j <= m * 2; j ++) {
	// 		std::cout << b[i][j] << ' ';
	// 	}
	// 	std::cout << '\n';
	// } 
	for (int i = 1; i <= n * 2; i ++) {
		for (int j = 1; j <= m * 2; j ++) {
			b[i][j] += b[i - 1][j] + b[i][j - 1];
			b[i][j] -= b[i - 1][j - 1];
		}
	}
	int ans = 0; // 只剩下哪些了()
	int all = (n - std::min(n, x1 - x2)) * (m - std::min(m, y1 - y2));
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			int lx = n + 1 - i + 1 + x1, rx = n + 1 + n - i + x2;
			int ly = m + 1 - j + 1 + y1, ry = m + 1 + m - j + y2;
			if (lx > rx || ly > ry) {
				if (k == 0) ans ++;
				continue;
			}
			// std::cout << lx << ' ' << rx << ' ' << ly << ' ' << ry << '\n';
			if (all - (b[rx][ry] - b[lx - 1][ry] - b[rx][ly - 1] + b[lx - 1][ly - 1]) == k) {
				ans ++;
			}
		}
	}
	std::cout << ans << '\n';
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

/// 


// aabcc
// ccbaa

// aabccccbaa
// ccbaabcc

/*
3
4 5 3
ULDDRR
4 5 0
UUUUUUU
4 5 10
UUUUUUU
*/