#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
using i64 = long long;
#define int i64
const int inf = 1e18 + 7;
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<std::array<int, 5> > a(n + 1);
	using pii = std::array<int, 3>;
	std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= 4; j ++) {
			std::cin >> a[i][j];
		}
		q.push({a[i][1], i, 1});
	}
	int ans = 0;
	while (k --) {
		auto it = q.top();
		q.pop();
		ans += it[0];
		int id = it[1], num = it[2];
		if (num < 4) {
			q.push({a[id][num + 1] - a[id][num], id, num + 1});
		}
		std::cout << ans << '\n';
	}
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