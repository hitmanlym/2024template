#include<bits/stdc++.h>
using i64 = long long;
const int inf = 1e9 + 7;

void solve() {
	int n, L, R;
    std::cin >> n >> L >> R;
    std::vector<int> a(n + 1), dp(n + 1, -inf);
    for (int i = 0; i <= n; i ++) {
        std::cin >> a[i];
    }
    std::deque<int> q;

    q.push_front(0);
    dp[0] = 0;

    int ans = -inf;
    for (int i = L; i <= n; i ++) {
        int u = i - L;
        while (! q.empty() && dp[q.front()] <= dp[u]) {
            q.pop_front();
        }
        q.push_front(u);

        int v;
        while (! q.empty() && q.back() + R < i) {
            q.pop_back();
        }
        v = q.back();

        dp[i] = dp[v] + a[i];
        if (i + R > n) {
            ans = std::max(ans, dp[i]);
        }
    }
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