#include<bits/stdc++.h>
using i64 = long long;
const int inf = 1e9;
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::array<int, 3> > a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i][0] >> a[i][1] >> a[i][2];
	} 
	// std::vector<std::array<int, 2> > p(4);
	// p[0] = {inf, -inf};
	// p[1] = {inf, inf};
	// p[2] = {-inf, inf};
	// p[3] = {-inf, -inf};
	int minx = inf, miny = inf, maxx = -inf, maxy = -inf;

	for (int i = 1; i <= n; i ++) {
		int x = a[i][0], y = a[i][1], z = a[i][2];
		int W = y + z, S = y - z, A = x - z, D = x + z;/*
		p[0][0] = std::min(p[0][0], A);
		p[0][1] = std::max(p[0][1], W);
		p[1][0] = std::min(p[1][0], A);
		p[1][1] = std::min(p[1][1], S);
		p[2][0] = std::max(p[2][0], D);
		p[2][1] = std::min(p[2][1], S);
		p[3][0] = std::max(p[3][0], D);
		p[3][1] = std::max(p[3][1], W);*/
		minx = std::min(minx, A);
		miny = std::min(miny, S);
		maxx = std::max(maxx, D);
		maxy = std::max(maxy, W);
	}
	// minus ---------------------------------------don't
	int X = (minx + maxx) / 2;
	int Y = (miny + maxy) / 2;
	int OP = std::max((maxx - minx), (maxy - miny));
	int H = (OP + 1) / 2;

	// if (((minx + maxx) & 1) && OP == (maxx - minx) 
	// 	|| ((miny + maxy) & 1) && OP == (maxy - miny)) {
	// 	H ++;
	// }
	std::cout << X << ' ' << Y << ' ' << H << '\n';
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
2
3 3 3
5 5 2

3
3 3 3
6 6 2
9 3 3

*/