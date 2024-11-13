#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::string s;
	std::cin >> s;
	std::reverse(s.begin(), s.end());
	std::vector<int> cnt(k);
	for (int i = 0; i < n; i ++) {
		std::string t;
		std::cin >> t;
		std::reverse(t.begin(), t.end());
		for (int j = 0; j < k; j ++) cnt[j] += t[j] - '0';
	}
	std::vector<std::vector<int> > vis(k, std::vector<int>(n + 1, false));
	std::string res = "";
	auto dfs = [&](auto self, int i, int cur) -> bool {
		if (i == k) {
			if (cur == 0) {
				return true;
			}
			return false;
		}
		if (vis[i][cur]) return false;
		vis[i][cur] = 1;
		for (int c = 0; c < 2; c ++) {
			int u = cur;
			if (c) u += n - cnt[i];
			else u += cnt[i];
			if ((u & 1) == s[i] - '0') {
				if (self(self, i + 1, u / 2)) {
					res += char(c + '0');
					return true;
				}
			}
		}
		return false;
	};
	dfs(dfs, 0, 0);
	if (res.empty()) std::cout << -1 << '\n';
	else std::cout << res << '\n'; 
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