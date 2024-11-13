#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n, m, x, y;
	std::cin >> n >> m;
	std::vector<std::vector<char> > a(n + 1, std::vector<char>(m + 1));
	std::vector<std::vector<int> > b(n + 1);
	std::map<std::array<int, 2>, char> mp;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			std::cin >> a[i][j];
			if (a[i][j] == 'A') {
				x = i, y = j;
			} 
			if (a[i][j] != '.') {
				b[i].push_back(j);
				mp[{i, j}] = a[i][j] + 'a' - 'A';
			}
		}
	}
	int l = 1, r = m;
	for (auto it : b[x]) {
		if (it < y) {
			l = std::max(l, it + 1);
		}
		if (it > y) {
			r = std::min(r, it - 1);
		}
	}
	int max = r - l + 1, W = x, S = x, A = l, D = r;
	// std::cout << max << ' ' << W << ' ' << S << ' ' << A << ' ' << D << '\n';
	int aa = l, bb = r;
	for (int i = x; i >= 1; i --) {
		int aaa = aa, bbb = bb;
		for (int j = x + 1; j <= n; j ++) {
			bool op = 1;
			for (auto it : b[j]) {
				if (it < y) {
					aaa = std::max(aaa, it + 1);
				}
				if (it > y) {
					bbb = std::min(bbb, it - 1);
				}
				if (it == y) {
					op = 0;
					break;
				}
			}
			if (! op) break;
			if ((j - i + 1) * (bbb - aaa + 1) > max) {
				max = (j - i + 1) * (bbb - aaa + 1);
				W = i, S = j, A = aaa, D = bbb;
			}
		}
		bool op = 1;
		if (i - 1 >= 1) {
			for (auto it : b[i - 1]) {
				if (it < y) {
					aa = std::max(aa, it + 1);
				} 
				if (it > y) {
					bb = std::min(bb, it - 1);
				}
				if (it == y) {
					op = 0;
					break;
				}
			}
			if (! op) break;
			if ((x - i + 1 + 1) * (bb - aa + 1) > max) {
				max = (x - i + 1 + 1) * (bb - aa + 1);
				W = i - 1, S = x, A = aa, D = bb;
			}
		}
	}
	// std::cout << W << ' ' << S << " " << A << " " << D << ' ' << max << '\n';
	for (int i = W; i <= S; i ++) {
		for (int j = A; j <= D; j ++) {
			a[i][j] = 'a';
		}
	}
	auto work = [&](int ww, int ss, int aa, int dd) {
		if (ss < ww || dd < aa) return ;
		int l = ww;

		while (l <= ss) {
			int num = 0;
			for (auto it : b[l]) {
				if (it >= aa && it <= dd) {
					num ++;
				}
			}
			if (! num) {
				l ++;
			} else {
				break;
			}
		}

		for (int i = l; i <= ss; i ++) {
			int num = 0;
			for (auto it : b[i]) {
				if (it >= aa && it <= dd) {
					num ++;
				}
			}
			if (! num) {
				for (int j = aa; j <= dd; j ++) {
					a[i][j] = a[i - 1][j];
				}
				continue;
			} else {
				int xc = aa;
				char fi;
				for (auto it : b[i]) {
					if (it >= aa && it <= dd) {
						char c = mp[{i, it}];
						fi = c;
						for (int j = xc; j <= it; j ++) {
							a[i][j] = c;
						}
						xc = it + 1;
					}
				}
				for (int j = xc; j <= dd; j ++) {
					a[i][j] = fi;
				}
			}
		}
		for (int i = l - 1; i >= ww; i --) {
			for (int j = aa; j <= dd; j ++) {
				a[i][j] = a[i + 1][j];
			}
		}
	};
	work(1, W - 1, 1, m);
	work(W, S, 1, A - 1);
	work(W, S, D + 1, m);
	work(S + 1, n, 1, m);
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			if (mp.count({i, j})) {
				std::cout << (char)(a[i][j] + 'A' - 'a');
			} else {
				std::cout << a[i][j];
			}
		}
		std::cout << '\n';
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
/*
........
........
......X.
.F......
...A....
........
.P......


6 8
......X.
.F...U..
...A....
........
.....P..
..L.....
*/