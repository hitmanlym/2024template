#include <bits/stdc++.h>
using i64 = long long;
#define int i64
signed main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    std::cin >> s;
    std::vector<int> dp(1 << 10);
    dp[0] = 1;
    int ans = 0;
    int state = 0;
    for (auto c : s) {
        int u = c - '0';
        state ^= (1 << u);
        ans += dp[state];
        for (int i = 0; i <= 9; i ++) {
            ans += dp[state ^ (1 << i)];
        }
        dp[state] ++;
    }
    std::cout << ans << '\n';
    return 0;
}