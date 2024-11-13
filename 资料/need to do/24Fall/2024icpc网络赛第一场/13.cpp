#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	std::map<char, int> cnt;
	std::set<std::string> p[26];
	for (int i = 0; i < 26; i ++) {
		p[i].clear();
	}
	for (int i = 1; i <= n; i ++) {
		std::string s, t;
		char c;
		std::cin >> s >> c >> t;
		if (t[0] == 'a') {
			if (! p[c - 'A'].count(s)) {
				cnt[c] ++;
				p[c - 'A'].insert(s);
			}
		} 
	}	
	int ans = 0;
	char res;
	for (auto it : cnt) {
		if (it.second > ans) {
			ans = it.second;
			res = it.first;
		}
	}
	std::cout << res << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	 std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}