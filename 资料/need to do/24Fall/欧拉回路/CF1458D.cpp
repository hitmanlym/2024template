#include<bits/stdc++.h>
using i64 = long long;
void solve() {
    std::string s;
    std::cin >> s;
    int n = s.size();
    s = " " + s;
    const int M = n;
    std::vector<std::array<int, 2> > a(2 * n + 1);
    for (int i = 1, cur = 0; i <= n; i ++) {
        a[M + cur][s[i] - '0'] ++;
        cur += (s[i] == '0' ? -1 : 1);
    }
    for (int i = 1, cur = 0; i <= n; i ++) {
        if (a[M + cur][0] && a[M + cur - 1][1]) {
            std::cout << 0;
            a[M + cur][0] --;
            cur --;
        } else if (a[M + cur][1]) {
            std::cout << 1;
            a[M + cur][1] --;
            cur ++;
        } else {
            std::cout << 0;
            a[M + cur][0] --;
            cur --;
        }
    }
    std::cout << '\n';
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