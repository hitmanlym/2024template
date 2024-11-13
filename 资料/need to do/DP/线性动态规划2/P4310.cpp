#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
#define int i64

void solve() {
    int n;
    std::cin >> n;
    int ans = 0;
    std::vector<int> t(31);
    for (int i = 1; i <= n; i ++) {
        int o = 0, x;
        std::cin >> x;
        for (int j = 0; j <= 30; j ++) {
            if ((x >> j) & 1) {
                o = std::max(o, t[j]);
            }
        }
        o ++;
        ans = std::max(ans, o);
        for (int j = 0; j <= 30; j ++) {
            if ((x >> j) & 1) {
                t[j] = std::max(t[j], o);
            }
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