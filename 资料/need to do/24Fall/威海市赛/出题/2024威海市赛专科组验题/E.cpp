#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> st;
	int now = 0;
	bool f = 1;
	for (int i = 1; i <= n; i ++) {
		int x;
		std::cin >> x;
		if (! f) continue;
		if (now >= x && st.back() != x) {
			f = 0;
			continue;
		}
		while (now < x) {
			st.push_back(++ now);
		}
		st.pop_back();
	}
	if (f) {
		std::cout << "YES\n";
	} else {
		std::cout << "NO\n";
	}
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