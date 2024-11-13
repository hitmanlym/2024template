#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::map<std::string, int> mp;
	std::map<std::string, int> rev;
	std::vector<std::string> ss(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> ss[i];
		std::string s = ss[i];
		std::map<std::string, bool> have;
		for (int j = 0; j < s.size(); j ++) {
			std::string t = "";
			for (int k = j; k < s.size(); k ++) {
				t += s[k];
				have[t] = 1;
			}
		}
		for (auto it : have) {
			rev[it.first] = i;
			mp[it.first] ++;
		}
	}
	int q;
	std::cin >> q;
	while (q --) {
		std::string s;
		std::cin >> s;
		int ans = mp[s];
		std::cout << ans << ' ';
		if (! ans) {
			std::cout << "-\n";
		} else {
			std::cout << ss[rev[s]] << '\n';
		}
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}