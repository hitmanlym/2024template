#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
#define int i64
void solve() {
	int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }

    std::vector<std::map<int, int> > e(n + 1);
    int ans = 0;

    for (int i = 1; i <= n; i ++) {
        ans = (ans + 1) % mod;
        for (int j = 1; j < i; j ++) {
            ans = (ans + 1) % mod;
            int u = a[i] - a[j];
            ans = (ans + e[j][u]) % mod;
            e[i][u] = (e[i][u] + e[j][u] + 1) % mod;
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