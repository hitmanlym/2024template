#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::vector<int> > a(n + 1, std::vector<int>(n + 1)),
		b(n + 2, std::vector<int>(n + 2));
	std::vector<int> v(n + 1), fuck;
	for (int i = 1; i <= n; i ++) {
		std::cin >> v[i];
		fuck.push_back(v[i]);
	}
	std::multiset<int> big, small;
	auto add = [&](int x) -> void {
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
		}
	}
	std::sort(fuck.begin(), fuck.end());

	auto check = [&](int x) -> bool {
		for (int i = 1; i <= n; i ++) {
			for (int j = i; j <= n; j ++) {
				if (a[i][j] >= x) b[i][j] = 1;
				else b[i][j] = 0;
			}
		}
		for (int i = n; i >= 1; i --) {
			for (int j = 1; j <= n; j ++) {
				b[i][j] = b[i + 1][j] + b[i][j - 1] - b[i + 1][j - 1] + b[i][j];
			}
		}
		int num = 0;
		int total = n * (n + 1) / 2;
		for (int i = 1; i <= n; i ++) {
			for (int j = i; j <= n; j ++) {
				int op = (j - i + 1) * (j - i + 2) / 2;
				if (b[i][j] * 2 > op) {
					num ++;
				}
			}
		}
		if (num * 2 > total) {
			return true;
		}
		return false;
	};
/*
	int l = 1, r = fuck.size(), ans;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(fuck[mid - 1])) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	std::cout << fuck[ans - 1] << '\n';*/
	int l = 1, r = 1e9, ans;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(mid)) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	std::cout << ans << '\n';
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