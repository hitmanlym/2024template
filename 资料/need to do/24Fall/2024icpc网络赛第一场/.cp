#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::vector<int> > a(n + 1, std::vector<int>(n + 1));
	std::vector<int> v(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> v[i];
	}
	std::multiset<int> big, small;
	auto add = [&](int x) -> int  {
		if (big.size() == small.size()) {
			if (! small.size() || x >= *small.rbegin()) {
				big.insert(x);
			} else {
				auto it = small.rbegin();
				auto p = small.find(*it);
				int u = *it;
				small.erase(p);
				small.insert(x);
				big.insert(u);
			}
		} else {
			if (x <= *big.begin()) {
				small.insert(x);
			} else {
				auto it = big.begin();
				int u = *it;
				big.erase(it);
				big.insert(x);
				small.insert(u);
			}
		}
	};
	auto get = [&]() -> int {
		if (big.size() == small.size()) {
			return *small.rbegin();
		}
		return *big.begin();
	};
	for (int i = 1; i <= n; i ++) {
		big.clear();
		small.clear();
		for (int j = i; j <= n; j ++) {
			add(v[j]);
			a[i][j] = get();
			std::cout << a[i][j] << ' ';
		}
		std::cout << '\n';
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