#include<bits/stdc++.h>
using i64 = long long;
// x ^ 2 = n (mod p) p is odd and prime


std::mt19937_64 rng(std::random_device{}()); // 好像 _64 更快
struct XP {
	i64 I = 0;
	using CP = std::complex<i64>;
	CP mul(CP x, CP y, i64 mod) {
		CP res((x.real() * y.real() % mod + I * x.imag() % mod * y.imag() % mod) % mod,
			(x.imag() * y.real() % mod + x.real() * y.imag() % mod) % mod);
		return res;
	}
	CP qmi(CP a, i64 b, i64 mod) {
		CP res = 1;
		while (b) {
			if (b & 1) res = mul(res, a, mod);
			a = mul(a, a, mod);
			b >>= 1;
		}
		return res;
	}

	std::vector<i64> get(i64 n, i64 p) {
		std::vector<i64> res;
		if (n == 0) { res.push_back(0); return res; }
		i64 mod = p; n %= p;
		if (p == 2) { res.push_back(n); return res; }
		if (qmi((CP){n, 0}, (mod - 1) >> 1, mod) == p - 1) {
			res.clear();
			return res;
		}

		i64 a = (i64)rng() % mod;
		auto check = [&](i64 x) -> bool {
			return qmi((CP){x, 0}, (mod - 1) >> 1, mod).real() == 1;
		};
		while (! a || check((a * a + mod - n) % mod)) {
			a = (i64)rng() % mod;
		}
		I = (a * a + mod - n) % mod;
		CP A(a, 1);
		i64 ans = ((qmi(A, (mod + 1) >> 1, mod)).real() + mod) % mod;
		i64 op = p - ans;
		if (ans > op) std::swap(ans, op);
		res.push_back(ans);
		if (ans != op) res.push_back(op);
		return res; 
	}
} tr;
void solve() {
	i64 n, p;
	std::cin >> n >> p;
	auto it = tr.get(n, p);
	if (! it.size()) {
		std::cout << "Hola!\n";
		return ;
	}
	for (auto v : it) {
		std::cout << v << ' ';
	}
	std::cout << '\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}