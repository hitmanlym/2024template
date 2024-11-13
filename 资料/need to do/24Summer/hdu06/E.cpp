#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;
// 2000 * 60000 * 10 = 1200000000
void solve() {
    int n, k, M;
    std::cin >> n >> k >> M;
    int x = 1;
    std::vector<int> d(k);
    d[0] = 1;
    for (int i = 1; i < k; i ++) {
        x *= 3;
        d[i] = x;
    }
    x *= 3;
    std::vector<std::string> s(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> s[i];
    }
    // 0 -> A
    // 1 -> B
    // 2 -> C
    std::vector<int> dp(x), ans(x);
    std::vector<bool> b(x), o(x);
    dp[0] = 1;
    b[0] = 1;
    for (int i = 1; i <= n; i ++) {
        for (int j = 0; j < x; j ++) {
            int op = j;
            for (int l = 0; l < k; l ++) {
                if (s[i][l] == '0') continue; 
                int it = (j / d[l]) % 3;
                if (s[i][l] == '+') {
                    if (it == 2) op -= 2 * d[l];
                    else op += d[l];
                } else {
                    if (it == 0) op += 2 * d[l];
                    else op -= d[l];
                }
            }
            // std::cout << j << ' ' << op << ' ' << x << '\n'; 
            // if (op < 0 || op >= x) continue;
            
            if (b[j]) {//std::cout << "!!! " << op << '\n';
                ans[op] += dp[j];
                o[op] = 1;
                if (ans[op] >= M) ans[op] -= M;
            }
            
        }
        for (int j = 0; j < x; j ++) {
            if (o[j]) {
                dp[j] += ans[j];
                if (dp[j] >= M) dp[j] -= M;
                b[j] = 1;
                o[j] = 0;
                ans[j] = 0;
            }
        }
    }
    std::vector<std::pair<std::string, int> > anss;
    for (int i = 0; i < x; i ++) {
        if (b[i]) {
            std::string t;
            for (int j = 0; j < k; j ++) {
                int it = (i / d[j]) % 3;
                if (it == 0) t.push_back('A');
                else if (it == 1) t.push_back('B');
                else t.push_back('C');
            }
            anss.push_back(std::make_pair(t, dp[i]));
        }
    }
    std::sort(anss.begin(), anss.end());
    for (auto it : anss) {
        std::cout << it.first << ' ' << it.second << '\n';
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}