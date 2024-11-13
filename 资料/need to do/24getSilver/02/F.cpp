#include<bits/stdc++.h>
using i64 = long long;
const int mod1 = 998244353, mod2 = 1e9 + 7;
struct Hasher {
    i64 x, y;
    Hasher(const int& X = 0, const int& Y = 0) {
        x = X, y = Y;
    }
    i64 val(void) {
        return ((1ll * x) << 31ll) |  (1ll * y);
    }
    friend Hasher operator + (const Hasher& A, const Hasher& B) {
        return Hasher((A.x + B.x) % mod1, (A.y + B.y) % mod2);
    }
    friend Hasher operator - (const Hasher& A, const Hasher& B) {
        return Hasher((A.x - B.x + mod1) % mod1, (A.y - B.y + mod2) % mod2);
    }
    friend Hasher operator * (const Hasher& A, const Hasher& B) {
        return Hasher(1ll * A.x * B.x % mod1, 1ll * A.y * B.y % mod2);
    }
};
const Hasher seed = (31, 131);
void solve() {
	int n;
	std::cin >> n;
	std::map<i64, int> mp;
	// i64 ans = mod1;
	for (int i = 1; i <= n; i ++) {
		std::string s;
		std::cin >> s;
		int m = s.size();
		s = " " + s;
		Hasher op = Hasher(1, 1);
		int ans = m;
		for (int j = 1; j <= m; j ++) {
			op = op * seed + Hasher(s[j] - 'a', s[j] - 'a');
			i64 v = op.val();
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