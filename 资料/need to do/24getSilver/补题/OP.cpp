#include <algorithm>
#include <iostream>
#include <cstdio>
#define maxn 3510
const int mod = 1e9 + 7;

namespace Math {
	inline int pw(int base, int p, const int mod) {
		static int res;
		for (res = 1; p; p >>= 1, base = static_cast<long long> (base) * base % mod) if (p & 1) res = static_cast<long long> (res) * base % mod;
		return res;
	}
	inline int inv(int x, const int mod) { return pw(x, mod - 2, mod); }
}

int n, m;
namespace Poly {
#define N 8192
	inline void clear(register int *l, const int *r) {
		if (l >= r) return ;
		while (l != r) *l++ = 0;
	}
	template <const int mod, const int G> struct P {
		int lim, s, rev[N];
		int Wn[N | 1];
		inline void reduce(int &x) { x += x >> 31 & mod; }
		inline void init(int n) {
			lim = 1, s = -1; while (lim < n) lim <<= 1, ++s;
			for (register int i = 1; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
			const int t = Math::pw(G, (mod - 1) / lim, mod);
			*Wn = 1; for (register int *i = Wn; i != Wn + lim; ++i) *(i + 1) = static_cast<long long> (*i) * t % mod;
		}
		inline void NTT(int *A, const int op = 1) {
			for (register int i = 1; i < lim; ++i) if (i < rev[i]) std::swap(A[i], A[rev[i]]);
			for (register int mid = 1; mid < lim; mid <<= 1) {
				const int t = lim / mid >> 1;
				for (register int i = 0; i < lim; i += mid << 1) {
					for (register int j = 0; j < mid; ++j) {
						const int W = op ? Wn[j * t] : Wn[lim - j * t];
						const int X = A[i + j], Y = static_cast<long long> (A[i + j + mid]) * W % mod;
						reduce(A[i + j] += Y - mod), reduce(A[i + j + mid] = X - Y);
					}
				}
			}
			if (!op) {
				const int ilim = Math::inv(lim, mod);
				for (register int *i = A; i != A + lim; ++i) *i = static_cast<long long> (*i) * ilim % mod;
			}
		}

		int res[N];
		inline int operator [] (const int i) { return res[i]; }

		int C[N], D[N];
		void MUL(int *A, int *B) {
			std::copy(A, A + n, C), clear(C + n, C + lim);
			std::copy(B, B + n, D), clear(D + n, D + lim);
			NTT(C), NTT(D);
			for (int i = 0; i < lim; i++) res[i] = static_cast<long long> (C[i]) * D[i] % mod;
			NTT(res, 0);
		}
		void SQR(int *A) {
			std::copy(A, A + n, C), clear(C + n, C + lim);
			NTT(C);
			for (int i = 0; i < lim; i++) res[i] = static_cast<long long> (C[i]) * C[i] % mod;
			NTT(res, 0);
		}
	} ;
	const int mod1 = 469762049, mod2 = 998244353, mod3 = 1004535809;
	const long long mod_1_2 = static_cast<long long> (mod1) * mod2;
	const int inv_1 = Math::inv(mod1, mod2), inv_2 = Math::inv(mod_1_2 % mod3, mod3);
	P<mod1, 3> P1;
	P<mod2, 3> P2;
	P<mod3, 3> P3;
	inline int get(const int A, const int B, const int C) {
		const long long x = static_cast<long long> (B - A + mod2) % mod2 * inv_1 % mod2 * mod1 + A;
		return (static_cast<long long> (C - x % mod3 + mod3) % mod3 * inv_2 % mod3 * (mod_1_2 % mod) % mod + x) % mod;
	}

	inline void reduce(int &x) { x += x >> 31 & mod; }
	inline void init(int n) {
		P1.init(n), P2.init(n), P3.init(n);
	}
	void MUL(int *A, int *B) {
		P1.MUL(A, B), P2.MUL(A, B), P3.MUL(A, B);
		for (int i = 0; i < n + n; i++) reduce(A[i] = get(P1[i], P2[i], P3[i]) + get(P1[i + n], P2[i + n], P3[i + n]) - mod);
	}
	void SQR(int *A) {
		P1.SQR(A), P2.SQR(A), P3.SQR(A);
		for (int i = 0; i < n + n; i++) reduce(A[i] = get(P1[i], P2[i], P3[i]) + get(P1[i + n], P2[i + n], P3[i + n]) - mod);
	}
	inline void PW(int *res, int *base, int p) {
		init(n << 1);
		res[0] = 1, clear(res + 1, res + n);
		while (p) {
			if (p & 1) {
				MUL(res, base);
			}
			p >>= 1;
			SQR(base);

			// std::cout << "!!!\n";
			// for (int i = 0; i < n + n; i ++) {
			// 	std::cout << base[i] << ' ';
			// }
			// std::cout << '\n';
			// for (int i = 0; i < n + n; i ++) {
			// 	std::cout << res[i] << ' ';
			// }
			// std::cout << '\n';
		}
	}
#undef N
}

int f[8192], g[8192];
int main() {
	scanf("%d%d", &n, &m);
	f[1] = f[n - 1] = 1;
	Poly::PW(g, f, m);
	printf("%d\n", g[0]);
	return 0;
}