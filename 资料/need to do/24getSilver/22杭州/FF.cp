#include<bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
const u64 b = 13131; 
// ???????
void solve() {
	int n, m;
	std::string s;
	std::cin >> n;
	std::map<u64, bool> mp;
	bool flag = 0;
	auto check = [&]() -> bool {
		for (int i = 0; i + 2 < s.size(); i ++) {
			if (s[i]=='b' && s[i+1]=='i' && s[i+2]=='e') {
				return true;
			}
		}
		return false;
	};
	for (int i = 1; i <= n; i ++) {
		std::cin >> m;
		flag = 0;
		for (int j = 1; j <= m; j ++) {
			std::cin >> s;
			u64 op = 0;
			for (auto c : s) {
				op = op * b + c;
			}

			if (check() && ! mp.count(op)) {
				std::cout << s << '\n';
				mp[op] = 1;
				flag = 1;
			}
		}
		if (! flag) {
			std::cout << "Time to play Genshin Impact, Teacher Rice!\n";
		}
	}
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