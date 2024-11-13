#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	std::string s, t = "weihai";
	std::cin >> s;
	int n = s.size();
	s = "#" + s;
	int num = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = i + 5; j <= n; j ++) {
			int now = 0;
			for (int k = i; k <= j; k ++) {
				if (s[k] == t[now]) {
					now ++;
					if (now == 6) break;
				}
			}
			if (now == 6) {
				num ++;
			}
		}
	}
	std::cout << num << '\n';
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