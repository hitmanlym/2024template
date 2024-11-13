#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
// #define int long long
const int mod = 1e9 + 7;
namespace Math {
	inline int pw(int base, int p, const int mod) {
		static int res;
		for (res = 1; p; p >>= 1, base = static_cast<long long> (base) * base % mod) if (p & 1) res = static_cast<long long> (res) * base % mod;
		return res;
	}
	inline int inv(int x, const int mod) { return pw(x, mod - 2, mod); }
}

const int mod1 = 469762049, mod2 = 998244353, mod3 = 1004535809, G = 3;
const long long mod_1_2 = static_cast<long long> (mod1) * mod2;
const int inv_1 = Math::inv(mod1, mod2), inv_2 = Math::inv(mod_1_2 % mod3, mod3);
struct Int {
	int A, B, C;
	explicit inline Int() { }
	explicit inline Int(int __num) : A(__num), B(__num), C(__num) { }
	explicit inline Int(int __A, int __B, int __C) : A(__A), B(__B), C(__C) { }
	static inline Int reduce(const Int &x) {
		return Int(x.A + (x.A >> 31 & mod1), x.B + (x.B >> 31 & mod2), x.C + (x.C >> 31 & mod3));
	}
	inline friend Int operator + (const Int &lhs, const Int &rhs) {
		return reduce(Int(lhs.A + rhs.A - mod1, lhs.B + rhs.B - mod2, lhs.C + rhs.C - mod3));
	}
	inline friend Int operator - (const Int &lhs, const Int &rhs) {
		return reduce(Int(lhs.A - rhs.A, lhs.B - rhs.B, lhs.C - rhs.C));
	}
	inline friend Int operator * (const Int &lhs, const Int &rhs) {
		return Int(
		static_cast<long long> (lhs.A) * rhs.A % mod1, 
		static_cast<long long> (lhs.B) * rhs.B % mod2, 
		static_cast<long long> (lhs.C) * rhs.C % mod3);
	}
	inline int get() {
		long long x = static_cast<long long> (B - A + mod2) % mod2 * inv_1 % mod2 * mod1 + A;
		return (static_cast<long long> (C - x % mod3 + mod3) % mod3 * inv_2 % mod3 * (mod_1_2 % mod) % mod + x) % mod;
	}
};

#define maxn 131072
namespace Poly {
#define N (maxn << 1)
	int lim, s, rev[N];
	Int Wn[N | 1];
	inline void init(int n) {
		s = -1, lim = 1; while (lim < n) lim <<= 1, ++s;
		for (register int i = 1; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
		const Int t(Math::pw(G, (mod1 - 1) / lim, mod1), Math::pw(G, (mod2 - 1) / lim, mod2), Math::pw(G, (mod3 - 1) / lim, mod3));
		*Wn = Int(1); for (register Int *i = Wn; i != Wn + lim; ++i) *(i + 1) = *i * t;
	}
	inline void NTT(Int *A, const int op = 1) {
		for (register int i = 1; i < lim; ++i) if (i < rev[i]) std::swap(A[i], A[rev[i]]);
		for (register int mid = 1; mid < lim; mid <<= 1) {
			const int t = lim / mid >> 1;
			for (register int i = 0; i < lim; i += mid << 1) {
				for (register int j = 0; j < mid; ++j) {
					const Int W = op ? Wn[t * j] : Wn[lim - t * j];
					const Int X = A[i + j], Y = A[i + j + mid] * W;
					A[i + j] = X + Y, A[i + j + mid] = X - Y;
				}
			}
		}
		if (!op) {
			const Int ilim(Math::inv(lim, mod1), Math::inv(lim, mod2), Math::inv(lim, mod3));
			for (register Int *i = A; i != A + lim; ++i) *i = (*i) * ilim;
		}
	}
#undef N
}
Int A[maxn << 1], B[maxn << 1], C[maxn << 1], D[maxn << 1], res[maxn << 1];
signed main() {
	int n, m;
	std::cin >> n >> m;
	Poly::init(n + n);
	for (int i = 0; i < Poly::lim; i ++) {
		A[i] = Int(0);
		B[i] = Int(0);
	}
	A[1] = Int(1), A[n - 1] = Int(1);
	B[0] = Int(1);
	while (m) {
		if (m & 1) {
			for (int i = 0; i < n; i ++) {
				C[i] = B[i];
				D[i] = A[i];
			}
			for (int i = n; i < Poly::lim; i ++) {
				C[i] = Int(0);
				D[i] = Int(0);
			}
			Poly::NTT(C), Poly::NTT(D);
			for (int i = 0; i < Poly::lim; i ++) {
				res[i] = C[i] * D[i];
			}
			Poly::NTT(res, 0);
			for (int i = 0; i < n + n; i ++) {
				B[i] = Int(((res[i].get() + res[i + n].get()) % mod + mod) % mod);
			}
		}

		for (int i = 0; i < n; i ++) {
			C[i] = A[i];
		}
		for (int i = n; i < Poly::lim; i ++) {
			C[i] = Int(0);
		}
		Poly::NTT(C);
		for (int i = 0; i < Poly::lim; i ++) {
			res[i] = C[i] * C[i];
		}
		Poly::NTT(res, 0);
		for (int i = 0; i < n + n; i ++) {
			A[i] = Int(((res[i].get() + res[i + n].get()) % mod + mod) % mod);
		}
		m >>= 1;
	}
	std::cout << B[0].get() << '\n';
	return 0;
}
// 10 100 the last time