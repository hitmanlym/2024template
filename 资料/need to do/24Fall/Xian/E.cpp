#include<bits/stdc++.h>
using i64 = long long;
const int N = 5001;
void solve() {
	int n;
	std::cin >> n;
	std::bitset<N> b[n + 1];
	for (int i = 0; i < n; i ++) {
		std::string s;
		std::cin >> s;
		for (int j = 0; j < n; j ++) {
			b[i][j] = s[j] - '0';
		}
	}
	std::vector<int> ans;

	std::vector<bool> vis(n + 1);
	for (int i = 0; i < n; i ++) {
		bool f = 1;
		for (int j = 0; j < n; j ++) {
			if (i == j || vis[j]) continue;

			if ((b[i] | b[j]) == b[j]) {
				f = 0;
				break;
			}
		}
		if (f) {
			ans.push_back(i + 1);
			if (ans.size() > 2) {
				break;
			}
		} else {
			vis[i] = 1;
		}
	}
	if (ans.size() == 3) {
		for (auto it : ans) {
			std::cout << it << ' ';
		}
		std::cout << '\n';
	} else {
		std::cout << "NOT FOUND\n";
	}
}
int main() {	
	int t = 1;
	while (t --) {
		solve();
	}
	return 0;
}