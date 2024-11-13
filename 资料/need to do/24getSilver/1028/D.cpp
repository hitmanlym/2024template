#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int inf = 1e18;
using pii = std::array<int, 2>;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), sum(n + 1), S(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		S[i] = S[i - 1] + a[i];
	}
	std::vector<int> s(n + 1);	
	s[1] = 1;
	for (int i = 2; i <= n; i ++) {
		s[i] = s[i - 1] + (n + 2 - i);
	}
	std::vector<pii> p(n + 2);
	int last = 0;
	for (int i = n; i >= 1; i --) {
		last = last + a[i] * (n - i + 1);
		p[i] = {s[i], last};
	}
	p[n + 1] = {p[n][0] + 1, 0};
	for (int i = 1; i <= n; i ++) {
		sum[i] = sum[i - 1] + p[i][1];
	}
	std::vector<int> suf(n + 2), ssuf(n + 2), pre(n + 1), ppre(n + 1);
	for (int i = n; i >= 1; i --) {
		suf[i] = suf[i + 1] + a[i];
	}
	for (int i = n; i >= 1; i --) {
		ssuf[i] = ssuf[i + 1] + suf[i];
	}
	for (int i = 1; i <= n; i ++) {
		pre[i] = pre[i - 1] + a[i];
	}
	for (int i = 1; i <= n; i ++) {
		ppre[i] = ppre[i - 1] + pre[i];
	}
	int q;
	std::cin >> q;
	while (q --) {
		int l, r;
		std::cin >> l >> r;
		int L = std::lower_bound(p.begin(), p.end(), (pii){l, 0ll}) - p.begin();
		int R = std::upper_bound(p.begin(), p.end(), (pii){r, inf}) - p.begin() - 1;
		if (r != p[R + 1][0] - 1) {
			R --;
		}
		int res = sum[R] - sum[L - 1];

		// L - 1 的后缀 x 个 , R + 1 的前缀 y 个
		int x = p[L][0] - l, y = r - p[R + 1][0] + 1;
		// std::cout << L << ' ' << R << ' ' << res << ' ' << x << ' ' << y << '\n';
		if (x) {
			res = res + (S[n] - S[L - 2]) * x - ssuf[n - x + 2];
		}
		// std::cout << res << '\n';
		if (y) {
			res = res + (ppre[R + 1 + y - 1] - ppre[R] - S[R] * y);
		}
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
/*
4
1 2 5 10
5
2 9
5 7
1 10
5 9
1 6


4
1 2 5 10
1
3 8

*/