#include<bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;

const int Maxn = 2e6 + 10;
const double pi = acos(-1.0);
using CP = std::complex<double>;
CP a[Maxn << 1], b[Maxn << 1];
int tr[Maxn << 1], n, m;

void fft(int limit, CP *a, int type) {
	if (limit == 1) return ;
	CP a1[limit >> 1], a2[limit >> 1];
	for (int i = 0; i < limit; i += 2) {
		a1[i >> 1] = a[i];
		a2[i >> 1] = a[i + 1];
	}
	fft(limit >> 1, a1, type);
	fft(limit >> 1, a2, type);

	CP w = CP(cos(2.0 * pi / limit), type * sin(2.0 * pi / limit));
	CP e = CP(1, 0);
	for (int i = 0; i < (limit >> 1); i ++, e = e * w) {
		CP it = e * a2[i];
		a[i] = a1[i] + it;
		a[i + (limit >> 1)] = a1[i] - it;
	}
}

void solve() {
	std::cin >> n >> m;
	int x;
	for (int i = 0; i <= n; i ++) {
		std::cin >> x;
		a[i] = x;
	}
	for (int i = 0; i <= m; i ++) {
		std::cin >> x;
		b[i] = x;
	}
	int limit = 1;
	while (limit <= n + m) limit <<= 1;
	fft(limit, a, 1);
	fft(limit, b, 1);
	for (int i = 0; i <= limit; i ++) {
		a[i] = a[i] * b[i];
	}
	fft(limit, a, -1);
	for (int i = 0; i <= n + m; i ++) {
		std::cout << (int)(a[i].real() / limit + 0.5) << ' ';
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