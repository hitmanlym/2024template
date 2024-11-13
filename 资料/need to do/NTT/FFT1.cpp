#include<bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;

const int Maxn = 2e6 + 10;
const double pi = acos(-1.0);
struct CP {
	double x, y;
	CP(double a = 0, double b = 0) {x = a, y = b;}
	CP operator +(CP const &B) const {
		return CP(x + B.x, y + B.y);
	}
	CP operator -(CP const &B) const {
		return CP(x - B.x, y - B.y);
	}
	CP operator *(CP const &B) const {
		return CP(x * B.x - y * B.y, x * B.y + y * B.x);
	}
};
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
	for (int i = 0; i <= n; i ++) {
		std::cin >> a[i].x;
	}
	for (int i = 0; i <= m; i ++) {
		std::cin >> b[i].x;
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
		std::cout << (int)(a[i].x / limit + 0.5) << ' ';
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