#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), b(n + 1), o(n + 1);
	bool f = 0;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		if (o[a[i]]) {
			f = 1;
		} else {
			o[a[i]] = 1;
		}
	}
	for (int i = 1; i <= n; i ++) {
		std::cin >> b[i];
	}
	if (f) {
		std::cout << "shuishui\n";
	} else {
		std::cout << "sha7dow\n";
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