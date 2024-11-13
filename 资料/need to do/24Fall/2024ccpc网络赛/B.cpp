#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
void solve() {
	int n;
	std::cin >> n;
	std::vector<i64> a(n + 1);
	std::map<int, int> mp;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		mp[a[i]] ++;
	}
	std::sort(a.begin() + 1, a.end());
	i64 ans = 0;
	for (int i = 1; i <= n; i ++) {
		ans += 1ll * a[i] * i;
		ans -= 1ll * a[i] * (n - i + 1);
	}
	std::cout << ans << ' ';
	std::vector<i64> jc(n + 1);
	jc[0] = 1;
	for (int i = 1; i <= n; i ++) {
		jc[i] = 1ll * jc[i - 1] * i % mod;
	}
	if (mp.size() == 1) {
		std::cout << jc[n] << '\n';
	} else {
		i64 res = 2;
		for (auto it : mp) {
			res = res * jc[it.second] % mod;
		}
		std::cout << res << '\n';
	}
}
int main() {
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}