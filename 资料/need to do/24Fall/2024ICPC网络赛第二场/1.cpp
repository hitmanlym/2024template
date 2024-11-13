#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n, k;
	std::cin >> n >> k;
	int min = 1e9;
	for (int i = 1; i <= k; i ++) {
		int x;
		std::cin >> x;
		min = std::min(min, x);
	}
	std::map<std::string, std::vector<int> > mp;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::string s;
		std::cin >> a[i] >> s;
		mp[s].push_back(a[i]);
	}
	std::vector<int> have;
	//std::cout << "!!! " << mp.size() << '\n';
	for (auto it : mp) {
		std::sort(it.second.begin(), it.second.end(), [&](auto x, auto y) {
			return x > y;
		});
		int num = 0;
		for (auto v : it.second) {
			have.push_back(v);
			num ++;
			if (num == min) break;
		}
	}	
	std::sort(have.begin(), have.end());
	/*for (auto it : have) {
		std::cout << it << ' ';
	}
	std::cout << '\n';*/
	int total = have.size();
	for (int i = 1; i <= n; i ++) {
		auto it = std::lower_bound(have.begin(), have.end(), a[i]) - have.begin();
		//std::cout << "??? " << it << '\n';
		std::cout << total - it << '\n';
	}
}
int main() {
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}