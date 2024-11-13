#include<bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;

const int Maxn = 2e6 + 10;
using CP = i64;
const int G = 3, mod = 998244353;
CP a[Maxn << 1], b[Maxn << 1];
int tr[Maxn << 1], n, m;
int qmi(int a, int b = mod - 2) {
	int res = 1;
	while (b) {
		if (b & 1) {
			res = 1ll * res * a  % mod;
		}
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return res;
}
const int invG = qmi(G);


void ntt(int limit, CP *a, bool type) {
	for (int i = 0; i < limit; i ++) {
		if (i < tr[i]) std::swap(a[i], a[tr[i]]);
	}

	for (int p = 2; p <= limit; p <<= 1) {
		int len = p >> 1;
		CP tG = qmi(type ? G : invG, (mod - 1) / p);
		for (int k = 0; k < limit; k += p) {
			CP e = 1;
			for (int l = k; l < k + len; l ++) {
				CP it = a[l + len] * e % mod;
				a[l + len] = (a[l] - it + mod) % mod;
				a[l] = (a[l] + it) % mod;
				e = e * tG % mod;
			}
		}
	}
}

void solve() {
	i64 SUM = 0, s = 0, op;
	std::cin >> n >> op;
	m = n;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[n - i + 1];
		SUM += a[n - i + 1] * a[n - i + 1];
		s += a[n - i + 1];
	}
	for (int i = 1; i <= m; i ++) {
		std::cin >> b[i];
		SUM += b[i] * b[i];
		s -= b[i];
	}
	for (int i = 1; i <= m; i ++) {
		b[i + m] = b[i];
	}
	m += m;
	int limit = 1;
	while (limit <= n + m) limit <<= 1;
	for (int i = 0; i < limit; i ++) {
		tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? limit >> 1 : 0);
	}
	ntt(limit, a, 1);
	ntt(limit, b, 1);
	for (int i = 0; i < limit; i ++) {
		a[i] = a[i] * b[i];
	}
	ntt(limit, a, 0);
	int invL = qmi(limit);
	i64 max = 0;
	for (int i = n + 1; i <= 2 * n; i ++) {
		max = std::max(max, a[i] * invL % mod);
	}
	SUM -= 2 * max;

	s *= 2;
	double toX = -1.0 * s / n / 2;
	int X;
	if( toX > 0 ) X = (i64)( toX + 0.5 ) ;
	else X = (i64)( toX - 0.5 ) ; 
	SUM += X * X * n + s * X ;


	std::cout << SUM << '\n';
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