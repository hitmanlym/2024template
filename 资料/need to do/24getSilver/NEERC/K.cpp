#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n + 1);
	int sum = 0;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		sum += a[i];
		a[i] += a[i - 1];
	}
	if (sum % k != 0) {
		std::cout << "No\n";
		return ;
	}
	sum /= k;
	int num = 0;
	std::vector<int> ans;
	for (int i = 1; i <= n; i ++) {
		if (a[i] - a[num] == sum) {
			ans.push_back(i - num);
			num = i;
		}
	}
	if (ans.size() != k) {
		std::cout << "No\n";
		return ;
	} 
	std::cout << "Yes\n";
	for (auto it : ans) {
		std::cout << it << ' ';
	}
	std::cout << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}