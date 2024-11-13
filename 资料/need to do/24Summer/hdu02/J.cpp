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

void solve() {
	std::string s;
	std::cin >> s;
	std::map<char, int> mp;
	for (auto c : s) {
		mp[c] ++;
 	}
 	if (s[0] == s[4]) {
 		std::cout << s[0] << '\n';
 		return ;
 	}
 	if (mp[s[0]] == mp[s[4]]) {
 		std::cout << "N\n";
 		return ;
 	}
 	if (mp[s[0]] > mp[s[4]]) {
 		std::cout << s[0] << '\n';
 	} else {
 		std::cout << s[4] << '\n';
 	}
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}