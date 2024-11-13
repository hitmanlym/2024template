#include<bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
#define int u64
const int mod3 = 99824435319198111, mod2 = 2119851155111, mod1 = 19260817;
struct Hasher {
    u64 x, y;
    Hasher(const int& X = 0, const int& Y = 0) {
        x = X, y = Y;
    }
    u64 val(void) {
        return (((1ll * x) << 8ll) | (1ll * y));
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

// struct Hasher{
// 	u64 x;
// 	Hasher(const u64& X = 0){
// 		x = X;
// 	}
// 	u64 val(void) { return x; }
//     friend Hasher operator + (const Hasher& A, const Hasher& B) {
//         return Hasher(A.x + B.x);
//     }
//     friend Hasher operator - (const Hasher& A, const Hasher& B) {
//         return Hasher(A.x - B.x);
//     }
//     friend Hasher operator * (const Hasher& A, const Hasher& B) {
//         return Hasher(A.x * B.x);
//     }
// };
const Hasher seed = (11, 1331);
void solve() {
	int n;
	std::cin >> n;
	std::map<u64, int> mp;
	// i64 ans = mod1;
	for (int i = 1; i <= n; i ++) {
		std::string s;
		std::cin >> s;
		int m = s.size();
		s = " " + s;
		Hasher op = Hasher(0, 0);
		int ans = m;
		for (int j = 1; j <= m; j ++) {
			op = op * seed + Hasher(s[j], s[j]);
			u64 v = op.val();
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