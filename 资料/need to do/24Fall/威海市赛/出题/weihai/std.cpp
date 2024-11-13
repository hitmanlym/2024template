#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	std::string s;
	std::cin >> s;
	int n = s.size();
	s = "#" + s;
	std::vector<std::vector<int> > nxt(n + 1, std::vector<int>(26));
	std::vector<int> last(26, n + 1);
	for (int i = n; i >= 0; i --) {
		int u = s[i] - 'a';
		for (int j = 0; j < 26; j ++) {
			nxt[i][j] = last[j];
		}
		if (u >= 0 && u < 26) {
			last[u] = i;
		}
	}
	i64 ans = 0;
	std::string t = "weihai";
	for (int i = 1; i <= n; i ++) {
		int r = i - 1;
		for (auto c : t) {
			int u = c - 'a';
			r = nxt[r][u];
			if (r == n + 1) break;
		}
		ans += n - r + 1;
	}
	std::cout << ans << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	while (t --) {
		solve();
	}
	return 0;
}
/*
wxeyizhaiw

weihaiweihai
*/