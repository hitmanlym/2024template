#include<bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
#define int u64
const int mod1 = 998244353, mod2 = 1e9 + 7, mod3 = 19260817;
struct Hasher1{
    i64 x, y;
    Hasher1(const int& X = 0, const int& Y = 0) {
        x = X, y = Y;
    }
    u64 val(void) {
        return (((1ll * x) << 31ll) | (1ll * y));
    }
    friend Hasher1 operator + (const Hasher1& A, const Hasher1& B) {
        return Hasher1((A.x + B.x) % mod1, (A.y + B.y) % mod2);
    }
    friend Hasher1 operator - (const Hasher1& A, const Hasher1& B) {
        return Hasher1((A.x - B.x + mod1) % mod1, (A.y - B.y + mod2) % mod2);
    }
    friend Hasher1 operator * (const Hasher1& A, const Hasher1& B) {
        return Hasher1(1ll * A.x * B.x % mod1, 1ll * A.y * B.y % mod2);
    }
};
struct Hasher2{
	u64 x;
	Hasher2(const u64& X = 0){
		x = X;
	}
	u64 val(void) { return x; }
    friend Hasher2 operator + (const Hasher2& A, const Hasher2& B) {
        return Hasher2(A.x + B.x);
    }
    friend Hasher2 operator - (const Hasher2& A, const Hasher2& B) {
        return Hasher2(A.x - B.x);
    }
    friend Hasher2 operator * (const Hasher2& A, const Hasher2& B) {
        return Hasher2(A.x * B.x);
    }
};
const Hasher1 seed1 = (131, 13131);
const Hasher2 seed2 = (13131);
void solve() {
	int n;
	std::cin >> n;
	std::map<std::array<int, 2>, int> mp;
	// i64 ans = mod1;
	for (int i = 1; i <= n; i ++) {
		std::string s;
		std::cin >> s;
		int m = s.size();
		s = " " + s;
		Hasher1 op1 = Hasher1(0, 0);
		Hasher2 op2 = Hasher2(0);
		int ans = m;
		for (int j = 1; j <= m; j ++) {
			op1 = op1 * seed1 + Hasher1(s[j], s[j]);
			op2 = op2 * seed2 + Hasher2(s[j]);
			std::array v = {op1.val(), op2.val()};
			if (mp.count(v)) {
				ans = std::min(ans, m + mp[v] - 2 * j);
				mp[v] = std::min(mp[v], m);
			} else {
				mp[v] = m;
			}
		}
		std::cout << ans << '\n';
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