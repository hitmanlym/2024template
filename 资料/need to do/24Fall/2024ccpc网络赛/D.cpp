#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
void solve() {
	std::string s, t;
	std::cin >> s >> t;
	int n = s.size(), m = t.size();
	std::vector<std::vector<int> > p(m + 1, std::vector<int>(m + 1));
	for (int i = 0; i < n; i ++) {
		auto op = p;
		for (int l = 1; l <= m; l ++) {
			for (int r = l + 1; r <= m; r ++) {
				for (int k = l; k < r; k ++) {
					p[l][r] = (p[l][r] + 1ll * op[l][k] * op[k + 1][r] % mod) % mod;
					//std::cout << "!!! " << l << ' ' << r << ' ' << k << '\n'; 
					//std::cout << "!!! " << op[l][k] << ' ' << op[k + 1][r] << ' ' << p[l][r] << '\n';
				}
			}
		}
		for (int l = 1; l <= m; l ++) {
			for (int r = l + 2; r <= m; r ++) {
				for (int k = l + 1; k < r; k ++) {
					if (t[k - 1] == s[i]) {
						p[l][r] = (p[l][r] + 1ll * op[l][k - 1] * op[k + 1][r] % mod) % mod; 
						//std::cout << "??? " << l << ' ' << r << ' ' << k << '\n'; 
					}
				}
			}
		}
		for (int l = 1; l <= m; l ++) {
			for (int r = l; r <= m; r ++) {
				if (l - 1 >= 1 && s[i] == t[l - 1 - 1]) {
					p[l - 1][r] = (p[l - 1][r] + op[l][r]) % mod;
					//std::cout << "### " << l << ' ' << r << ' ' << l - 1 << '\n'; 
				}
				if (r + 1 <= m && s[i] == t[r + 1 - 1]) {
					p[l][r + 1] = (p[l][r + 1] + op[l][r]) % mod;
					//std::cout << "@@@ " << l << ' ' << r << ' ' << r + 1 << '\n'; 
				}
			}
		}

		for (int l = 1; l <= m; l ++) {
			for (int r = l; r <= m; r ++) {
				p[l][r] = (p[l][r] + op[l][r]) % mod;
			}
		}
		for (int l = 1; l <= m; l ++) {
			if (s[i] == t[l - 1]) {
				p[l][l] = (p[l][l] + 1) % mod;
			}
		}
		/*
		for (int l = 1; l <= m; l ++) {
			for (int r = l; r <= m; r ++) {
				std::cout << p[l][r] << ' ';
			}
			std::cout << '\n';
		}
		std::cout << '\n';*/
	}
	std::cout << p[1][m] << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}