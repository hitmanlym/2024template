#include<bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
#define int u64
using Poly = std::vector<int>;
//4179340454199820289
const int G = 3, mod = 4179340454199820289, Maxn = 2e6 + 10;
int qmi(int a, int b = mod - 2) {
	int res = 1;
	while (b) {
		if (b & 1) {
			res = (__int128)res * a  % mod;
		}
		a = (__int128)a * a % mod;
		b >>= 1;
	}
	return res;
}
const int invG = qmi(G);
int tr[Maxn << 1], tf;
void tpre(int n) {
	if (tf == n) return ;
	tf = n;
	for (int i = 0; i < n; i ++) {
		tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
	}
}

void NTT(int n, int *g, bool op) {
	tpre(n);
	static u64 f[Maxn << 1], w[Maxn << 1];
	w[0] = 1;
	for (int i = 0; i < n; i ++) {
		f[i] = (g[tr[i]]) % mod;
	}
	for (int l = 1; l < n; l <<= 1) {
    	u64 tG = qmi(op ? G : invG, (mod - 1) / (l + l));
    	for (int i = 1; i < l; i ++) w[i] = (__int128)(w[i - 1]) * tG % mod;
    	for (int k = 0; k < n; k += l + l)
      		for (int p = 0; p < l; p ++) {
        		int tt = (__int128)w[p] * f[k | l | p] % mod;
        		f[k | l | p] = (f[k | p] + mod - tt) % mod;
        		f[k | p] = (f[k | p] + tt) % mod;
      		}      
    	if (l == (1 << 10))
      		for (int i = 0; i < n; i ++) f[i] %= mod;
  	}
	if (! op) {
    	u64 invn = qmi(n);
    	for(int i = 0; i < n; ++ i) {
    		g[i] = (__int128) f[i] % mod * invn % mod;
    	}
  	} else {
  		for (int i = 0; i < n; ++ i) {
  			g[i] = f[i] % mod;
  		}
  	}
}

void px(int n, int *f, int *g) {
	for (int i = 0; i < n; ++ i) {
		f[i] = (__int128)f[i] * g[i] % mod;
	}
}

Poly operator +(const Poly &A, const Poly &B) {
	Poly C = A;
	C.resize(std::max(A.size(), B.size()));
	for (int i = 0; i < B.size(); i ++) {
		C[i] = (C[i] + B[i]) % mod;
	}
	return C;
}
Poly operator -(const Poly &A, const Poly &B) {
	Poly C = A;
	C.resize(std::max(A.size(),B.size()));
	for (int i = 0; i < B.size(); i ++) {
		C[i] = (C[i] + mod - B[i]) % mod;
	}
	return C;
}
Poly operator *(const int c, const Poly &A) {
	Poly C;
	C.resize(A.size());
	for (int i = 0; i < A.size(); i ++) {
		C[i] = 1ll * c * A[i] % mod;
	}
	return C;
}
int lim; // set.
Poly operator *(const Poly &A, const Poly &B) {
	static int a[Maxn << 1], b[Maxn << 1];
	for (int i = 0; i < A.size(); i ++) a[i] = A[i];
	for (int i = 0; i < B.size(); i ++) b[i] = B[i];
	Poly C;
	C.resize(/*std::min(lim, */(int)(A.size() + B.size() - 1));
	int n = 1; 
	for(n; n < A.size() + B.size() - 1; n <<= 1);
	NTT(n, a, 1);
	NTT(n, b, 1);
	px(n, a, b);
	NTT(n, a, 0);
	for (int i = 0; i < C.size(); i ++) {
		C[i] = a[i];
	}
	for (int i = 0; i <= n; i ++) {
		a[i] = 0;
		b[i] = 0;
	}
	return C;
}
void pinv(int n, const Poly &A, Poly &B) {
	if (n == 1) B.push_back(qmi(A[0]));
	else if (n & 1){
		pinv(-- n, A, B);
		int sav = 0;
		for (int i = 0; i < n; i ++) {
			sav = (sav + 1ll * B[i] * A[n - i] % mod) % mod;
		}
		B.push_back(1ll * sav * qmi(mod - A[0]) % mod);
	} else {
		pinv(n / 2, A, B);
		Poly sA;
		sA.resize(n);
		for (int i = 0; i < n; i ++) {
			sA[i] = A[i];
		}
		B = 2 * B - B * B * sA;
		B.resize(n);
	}
}
Poly pinv(const Poly &A) {	// P-inv
	Poly C;
	pinv(A.size(), A, C);
	return C;
}
int inv[Maxn];
void Init() {
	inv[1] = 1;
	for (int i = 2; i <= lim; i ++) {
		inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
	}
}
Poly dao(const Poly &A) {	// P-qiu-dao
	Poly C = A;
	for (int i = 1; i < C.size(); i ++) {
		C[i - 1] = 1ll * C[i] * i % mod;
	}
	C.pop_back();
	return C;
}
Poly ints(const Poly &A) { // P-ji-fen
	Poly C = A;
	for (int i = C.size() - 1; i; i --)
		C[i] = 1ll * C[i - 1] * inv[i] % mod;
	C[0] = 0;
	return C;
}
Poly ln(const Poly &A) {	// P-ln
	return ints(dao(A) * pinv(A));
}
void pexp(int n, const Poly &A, Poly &B) {
	if (n == 1) B.push_back(1);
	else if (n & 1) {
		pexp(n - 1, A, B);
		n -= 2;
	 	int sav = 0;
		for (int i = 0; i <= n; i ++) {
			sav = (sav + 1ll * (i + 1) * A[i + 1] % mod * B[n - i] % mod) % mod;
		}
		B.push_back(1ll * sav * inv[n + 1] % mod);
	} else {
		pexp(n / 2, A, B);
		Poly lnB = B;
		lnB.resize(n);
		lnB = ln(lnB);
		for (int i = 0; i < lnB.size(); i ++) {
			lnB[i] = (mod + A[i] - lnB[i]) % mod;
		}
		lnB[0] ++;
		B = B * lnB;
		B.resize(n);
	}
}
Poly pexp(const Poly &A) {	// P-exp
	Poly C;
	pexp(A.size(), A, C);
	return C;
}


void solve() {
	int n;
	std::cin >> n;
	std::vector<int> v(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> v[i];
	}
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		a[i] = a[i - 1] + v[i];
	}
	int max = a[n];
	Poly g(max + 1);
	for (int i = 0; i <= n; i ++) {
		g[a[i]] ++;
	}
	auto h = g;
	std::reverse(h.begin(), h.end());
	//lim = max * 2;
	Poly f = g * h;
	std::vector<int> num(max + 1);
	for (int i = 0; i <= max; i ++) {
		num[i] = f[max + i];
	}
	num[0] = (num[0] - (n + 1)) / 2; // 0 [0, 0] -- [n, n] 
	for (int i = 1; i <= max; i ++) {
		num[i] += num[i - 1];
	}
	int m;
	std::cin >> m;
	while (m --) {
		int k;
		std::cin >> k;
		auto it = std::lower_bound(num.begin(), num.end(), k) - num.begin();
		std::cout << it << '\n';
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