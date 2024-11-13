#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
    int n, k;
    std::cin >> n >> k;
    int ans = n * k;
    for (int l = 1, r; l <= std::min(k, n); l = r + 1) {
        // 钦定 [l, r <--] 
        r = std::min(k / (k / l), n);
        ans -= (r - l + 1) * (l + r) / 2 * (k / l);
    }
    std::cout << ans << '\n';
}
signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}