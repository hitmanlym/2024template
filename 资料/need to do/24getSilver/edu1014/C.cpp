#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n + 1);
	std::map<int, int> mp;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		mp[a[i]] ++;
	}
	std::deque<int> q;
	int ans = 0, sum = 0, lst = -1;
	for (auto it : mp) {
		int u = it.first, v = it.second;
		if (lst == -1 || u == lst + 1) {
			if (q.size() == k) {
				ans = std::max(ans, sum);
				sum -= q.front();
				q.pop_front();
			}
			sum += v;
			q.push_back(v);
		} else {
			ans = std::max(ans, sum);
			q.clear();
			q.push_back(v);
			sum = v;
		}
		lst = u;
	}
	ans = std::max(ans, sum);
	std::cout << ans << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}