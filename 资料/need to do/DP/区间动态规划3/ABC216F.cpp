#include<bits/stdc++.h>
using i64 = long long;
#define int i64

const int mod = 998244353;
void solve() {
	int n;
    std::cin >> n;
    std::vector<std::array<int, 2> > a(n);
    for (int i = 0; i < n; i ++) {
        std::cin >> a[i][0];
    }
    for (int i = 0; i < n; i ++) {
        std::cin >> a[i][1];
    }
    std::sort(a.begin(), a.end());

    int N = 5e3 + 10;
    std::vector<int> dp(N + 1, 1);
    int ans = 0;
    for (int i = 0; i < n; i ++) {
        if (a[i][0] >= a[i][1]) {
            ans = (ans + dp[a[i][0] - a[i][1]]) % mod;
        }
        for (int j = N; j >= a[i][1]; j --) {
            dp[j] = (dp[j] + dp[j - a[i][1]]) % mod;
        }
    }
    std::cout << ans << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}