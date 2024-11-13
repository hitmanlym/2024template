#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		a[i] -= i;
	}


	int l = 0; // l is denied.
	std::multiset<int> big, small;
	int rsum = 0, lsum = 0;
	auto add = [&](int x) -> void {
		if (big.size() == small.size()) {
			if (! small.size() || x >= *small.rbegin()) {
				rsum += x;
				big.insert(x);
			} else {
				auto it = small.rbegin();
				auto p = small.find(*it);
				int u = *it;
				small.erase(p);
				small.insert(x);
				big.insert(u);

				rsum += u;
				lsum += x - u;
			}
		} else {
			if (x <= *big.begin()) {
				lsum += x;
				small.insert(x);
			} else {
				auto it = big.begin();
				int u = *it;
				big.erase(it);
				big.insert(x);
				small.insert(u);

				lsum += u;
				rsum += x - u;
			}
		}
	};
	auto del = [&](int x) -> void {
		if (big.size() == small.size()) {
			auto it = big.find(x);
			if (it != big.end()) {
				rsum -= x;
				big.erase(it);

				auto t = small.rbegin();
				auto p = small.find(*t);
				big.insert(*t);
				rsum += *t;
				lsum -= *t;
				small.erase(p);
			} else {
				it = small.find(x);
				lsum -= x;
				small.erase(it);
			}
		} else {
			auto it = big.find(x);
			if (it != big.end()) {
				rsum -= x;
				big.erase(it);
			} else {
				it = small.find(x);
				lsum -= x;
				small.erase(it);

				auto t = big.begin();
				rsum -= *t;
				lsum += *t;
				small.insert(*t);
				big.erase(t);
			}
		}
	};
	auto get = [&]() -> std::vector<int> {
		std::vector<int> res;
		res.push_back(*big.begin());
		if (big.size() == small.size()) {
			res.push_back(*small.rbegin());
		}
		return res;
	};	
	// make small have n / 2
	int ans = 0;
	for (int r = 1; r <= n; r ++) {
		add(a[r]);
		while (true) {
			auto it = get();
			bool f = 0;
			for (auto mid : it) {
				if (k >= rsum - mid * big.size() + mid * small.size() - lsum) {
					f = 1;
				}
			}
			if (f) break;
			else {
				l ++;
				del(a[l]);
			}
		}
		ans = std::max(ans, r - l);
		// make big.size() >= small.size()
	}

	
	std::cout << ans << '\n';
}	
signed main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}