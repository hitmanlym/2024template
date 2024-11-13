#include<bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;

const int Maxn = 2e6 + 10;
const double pi = acos(-1.0);
using CP = std::complex<double>;
CP a[Maxn << 1], b[Maxn << 1], c[Maxn << 1];
int tr[Maxn << 1], n, m;

void fft(int limit, CP *a, int type) {
	for (int i = 0; i < limit; i ++) {
		if (i < tr[i]) std::swap(a[i], a[tr[i]]);
	}

	for (int p = 2; p <= limit; p <<= 1) {
		int len = p >> 1;
		CP tG(cos(2.0 * pi / p), type * sin(2.0 * pi / p));
		for (int k = 0; k < limit; k += p) {
			CP e(1, 0);
			for (int l = k; l < k + len; l ++) {
				CP it = a[l + len] * e;
				a[l + len] = a[l] - it;
				a[l] = a[l] + it;
				e = e * tG;
			}
		}
	}
}

void solve() {
	std::cin >> n;
	m = n;
	double x;
	for (int i = 1; i <= n; i ++) {
		std::cin >> x;
		a[i] = x;
	}
	for (int i = 1; i <= n; i ++) {
		b[i] = 1.0 / i / i;
	}
	int limit = 1;
	while (limit <= n + n) limit <<= 1;
	for (int i = 0; i < limit; i ++) {
		tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? limit >> 1 : 0);
	}
	for (int i = 1; i <= n; i ++) {
		c[i] = a[n - i + 1];
	}
	fft(limit, a, 1);
	fft(limit, b, 1);
	fft(limit, c, 1);
	for (int i = 0; i < limit; i ++) {
		a[i] = a[i] * b[i];
		c[i] = c[i] * b[i];
	}
	fft(limit, a, -1);
	fft(limit, c, -1);
	for (int i = 1; i <= n; i ++) {
		double res = (a[i].real() - c[n - i + 1].real()) / limit;
		printf("%.3lf\n", res);
	}
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}