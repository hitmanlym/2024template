#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n, k;
	std::cin >> n >> k;
	std::set<int> st;
	for (int i = 1; i <= n; i ++) {
		int x;
		std::cin >> x;
		st.insert(x);
	}
	int l = 0;
	int odd = 0, even = 0;
	for (auto it : st) {
		while (l < it) {
			if (l & 1) {
				odd ++;
				if (odd == k + 1) {	
					std::cout << "Bob\n";
					return ;
				}
			} else {
				even ++;
				if (even == k + 1) {
					std::cout << "Alice\n";
					return ;
				}
			}
			l ++;
		}
		l = it + 1;
	}
	while (odd <= k && even <= k) {
		if (l & 1) {
			odd ++;
			if (odd == k + 1) {	
				std::cout << "Bob\n";
				return ;
			}
		} else {
			even ++;
			if (even == k + 1) {
				std::cout << "Alice\n";
				return ;
			}
		}
		l ++;
	}
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