#include<bits/stdc++.h>
using i64 = long long;
const int inf = 1e9;
void solve() {
	int n;
	std::cin >> n;
	std::string s;
	std::cin >> s;
	std::vector<std::string > ans;
	std::vector<int> num(n, inf);
 	std::vector<int> pre(n + 1);
 	std::vector<std::string> th(n + 1);
 	num[0] = 1;
 	pre[0] = -1;
 	pre[1] = 0;
 	num[1] = 2;
 	th[0] = s[0];
 	th[1] = s[1];
 	if (s[1] == s[0] && s[0] != 'D' && s[0] != 'L' && s[0] != 'V') {
 		num[1] = 1;
 		pre[1] = -1;
 		th[1] = th[0] + s[1];
 	}
 	for (int i = 2; i < n; i ++) {
 		pre[i] = i - 1;
 		if (num[i] > num[i - 1] + 1) {
 			pre[i] = i - 1;
 			th[i] = s[i];
 			num[i] = num[i - 1] + 1;
 		}
 		if (s[i - 2] == 'M' && s[i - 1] == 'M' && s[i] == 'M') {
 			int op = i - 3 < 0 ? 0 : num[i - 3];
 			if (op + 1 < num[i]) {
 				pre[i] = i - 3;
 				th[i] = "MMM";
 				num[i] = op + 1;
 			}
 		}
 		if (s[i - 2] == 'C' && s[i - 1] == 'C' && s[i] == 'C') {
 			int op = i - 3 < 0 ? 0 : num[i - 3];
 			if (op + 1 < num[i]) {
 				pre[i] = i - 3;
 				th[i] = "CCC";
 				num[i] = op + 1;
 			}
 		}
 		if (s[i - 2] == 'X' && s[i - 1] == 'X' && s[i] == 'X') {
 			int op = i - 3 < 0 ? 0 : num[i - 3];
 			if (op + 1 < num[i]) {
 				pre[i] = i - 3;
 				th[i] = "XXX";
 				num[i] = op + 1;
 			}
 		}
 		if (s[i - 2] == 'I' && s[i - 1] == 'I' && s[i] == 'I') {
 			int op = i - 3 < 0 ? 0 : num[i - 3];
 			if (op + 1 < num[i]) {
 				pre[i] = i - 3;
 				th[i] = "III";
 				num[i] = op + 1;
 			}
 		}
 		if (s[i - 1] == 'M' && s[i] == 'M') {
 			int op = num[i - 2];
 			if (op + 1 < num[i]) {
 				pre[i] = i - 2;
 				th[i] = "MM";
 				num[i] = op + 1;
 			}
 		}
 		if (s[i - 1] == 'C' && s[i] == 'C') {
 			int op = num[i - 2];
 			if (op + 1 < num[i]) {
 				pre[i] = i - 2;
 				th[i] = "CC";
 				num[i] = op + 1;
 			}
 		}
 		if (s[i - 1] == 'X' && s[i] == 'X') {
 			int op = num[i - 2];
 			if (op + 1 < num[i]) {
 				pre[i] = i - 2;
 				th[i] = "XX";
 				num[i] = op + 1;
 			}
 		}
 		if (s[i - 1] == 'I' && s[i] == 'I') {
 			int op = num[i - 2];
 			if (op + 1 < num[i]) {
 				pre[i] = i - 2;
 				th[i] = "II";
 				num[i] = op + 1;
 			}
 		}

 		if (s[i - 2] == 'M' && s[i - 1] == 'C' && s[i] == 'M') {
 			int op = i - 3 < 0 ? 0 : num[i - 3];
 			if (op + 1 < num[i]) {
 				num[i] = op + 1;
 				pre[i] = i - 3;
 				th[i] = "MCM";
 			}
 		} 
 		if (s[i - 2] == 'C' && s[i - 1] == 'X' && s[i] == 'C') {
			int op = i - 3 < 0 ? 0 : num[i - 3];
 			if (op + 1 < num[i]) {
 				num[i] = op + 1;
 				pre[i] = i - 3;
 				th[i] = "CXC";
 			}
 		} 
 		if (s[i - 2] == 'X' && s[i - 1] == 'I' && s[i] == 'X') {
 			int op = i - 3 < 0 ? 0 : num[i - 3];
 			if (op + 1 < num[i]) {
 				num[i] = op + 1;
 				pre[i] = i - 3;
 				th[i] = "XIX";
 			}
 		}
 	}

 	// for (int i = 0; i < n; i ++) {
 	// 	std::cout << num[i] << ' ';
 	// }
 	// std::cout << '\n';

 	int now = n - 1;
 	std::set<int> op;
 	while (now != -1) {
 		// std::cout << now << ' ';
 		ans.push_back(th[now]);
 		now = pre[now];
 	}
 	// std::cout << '\n';
 	std::cout << ans.size() << '\n';
 	while (ans.size()) {
 		std::cout << ans.back() << '\n';
 		ans.pop_back();
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
/*
12
MMMCMMCXCXIX
10
MMCMCMCMCM
27
MCMXXXLIVIIIVXMCMXCIXXIXIDC
27
MCMXXXLIVIIIVXCMCXCIXXIXIDC
*/