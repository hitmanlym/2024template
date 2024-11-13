#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(m + 1), b(m + 1), dp(1 << n, 1e9);
	for (int i = 1; i <= m; i ++) {
		for (int j = 0; j < n; j ++) {
			int x;
			std::cin >> x;
			if (x == 1) a[i] |= (1 << j);
			if (x == -1) b[i] |= (1 << j);
		}
	}
	dp[0] = 0;
	std::vector<bool> vis(1 << n);
	std::queue<int> q;
	q.push(0);
	while (! q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for (int i = 1; i <= m; i ++) {
			int st = (u | a[i]) & (~ b[i]);
			if (dp[st] > dp[u] + 1) {
				dp[st] = dp[u] + 1;
				if (! vis[st]) {
					vis[st] = 1;
					q.push(st);
				}
			}
		}
	}
	int ans = dp[(1 << n) - 1];
	if (ans == 1e9) ans = -1;
	std::cout << ans << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}