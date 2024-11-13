#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
#include<map>
using i64 = long long;
#define int i64

const int mod = 1e9 + 7;
int qmi(int a, int b) {
    if (a == 0) return 0;
    int res = 1;
    while (b) {
        if (b & 1) {
            res = 1ll * res * a % mod;
        }
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}


void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int> > e(n + 1);
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	std::vector<std::array<int, 2> > px(n + 1), py(n + 1); // max, sec _ {point, len}
	//std::map<int, int> mp;
	std::array<int, 2> ans = {0, 0};
	auto dfs = [&](auto self, int u, int p) -> void {
		std::array<int, 2> fi = {0, 0}, se = {0, 0};
		for (auto v : e[u]) {
			if (v == p) continue;
			self(self, v, u);
			if (px[v] > fi) {
				se = fi;
				fi = px[v];
			} else if (px[v] > se) {
				se = px[v];
			}
		}
		px[u] = {fi[0] + e[u].size() - 1, fi[1] + 1};
		py[u] = {se[0] + e[u].size() - 1, se[1] + 1};
		ans = std::max({ans, {fi[0] + se[0] + e[u].size() - 1, fi[1] + se[1] + 1}});
	};
	__int128 P = 0;
	std::vector<int> x(n + 1), y(n + 1);
	std::vector<int> vv(n + 1);
	auto check = [&](auto self, int u, int p) -> void {
		int fi = 0, se = 0;
		for (auto v : e[u]) {
			if (v == p) continue;
			self(self, v, u);
			if (x[v] > fi) {
				se = fi;
				fi = x[v];
			} else if (x[v] > se) {
				se = x[v];
			}
		}
		x[u] = vv[u] + fi;
		y[u] = vv[u] + se;
		//std::cout << u << ' ' << x[u] << ' ' << y[u] << '\n';
		P = std::max(P, __int128(fi) + se + vv[u]);
	};
	auto print128 = [](__int128_t x) -> void
	{
	    if (!x)
	    {
	        std::cout << 0 << '\n';
	        return;
	    }
	    bool fg = (x < 0);
	    if (fg)
	        x = -x;
	    std::vector<int> dig;
	    while (x)
	    {
	        dig.push_back(x % 10);
	        x /= 10;
	    }
	    std::reverse(dig.begin(), dig.end());
	    if (fg)
	        std::cout << '-';
	    for (int i : dig)
	        std::cout << i;
	    std::cout << '\n';
	};
	if (m >= 30) {
		dfs(dfs, 1, 0);
		int res = ((qmi(2, m) - 1) * ans[0] % mod + ans[1]) % mod;
		std::cout << res << '\n';
	} else {
		for (int i = 1; i <= n; i ++) {
			vv[i] = (qmi(2, m) - 1) * (e[i].size() - 1) + 1;
		}
		check(check, 1, 0);
		P %= mod;
		print128(P);
	}
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}