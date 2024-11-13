#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int inf = 1e18;
using pii = std::array<int, 2>;
void solve() {
	long long n, m;
	std::cin >> n >> m;
	std::vector<std::array<int, 3> > a(n + 2);
	int s = 0, pr = 0;
	for (int i = 1; i <= n; i ++) {
		long long x, y, z;
		std::cin >> x >> y >> z;
		// std::cin >> a[i][0] >> a[i][1] >> a[i][2];
		a[i] = {x, y, z};
		s += a[i][1];
		pr += a[i][0] * a[i][1];
	}
	std::sort(a.begin() + 1, a.end(), [&](auto x, auto y) {
		return x[0] > y[0];
	});
	int f = m - s;
	int ans = 0, pre = 0;
	for (int i = 1; i <= n; i ++) {
		// std::cout << pr << ' ' << pre << ' ' << (f - a[i][1]) << '\n';
		ans = std::max(ans, pr + pre + f * a[i][0]);
		f -= (a[i][2] - a[i][1]);
		if (f <= 0) break;
		pre += (a[i][2] - a[i][1]) * a[i][0];
	}
	f = m - s;
	std::vector<pii> b(n + 1);
	std::vector<int> ss(n + 1);
	int ui = 0;
	for (int i = 1; i <= n; i ++) {
		ui += a[i][2] - a[i][1];
		// std::cout << "!!! " << a[i][1] << ' ' << a[i][2] << '\n';
		b[i] = {ui, (a[i][2] - a[i][1]) * a[i][0]};
		ss[i] = ss[i - 1] + b[i][1];
	}
	// for (int i = 1; i <= n; i ++) {
	// 	// std::cout << b[i][0] << ' ';
	// }
	// std::cout << '\n';
	for (int i = n; i >= 1; i --) {
		int op = f + a[i][1];
		int now = pr - a[i][1] * a[i][0];
		int fk = std::upper_bound(b.begin(), b.end(), (pii){op, inf}) - b.begin();
		// std::cout << (long long)op << ' ' << (long long)fk << '\n';
		fk = std::min(fk, i + 1);
		fk --;
		int res = op - b[fk][0];
		ans = std::max(ans, now + ss[fk] + res * a[fk + 1][0]);
	}
	std::cout << (long long)ans << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	long long t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}
/*
2 10
1 1 2
2 1 2
 */
