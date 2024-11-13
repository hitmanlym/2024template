#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 998244353;
int qmi(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) {
			res = 1ll * res * a % mod;
		}
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return res;
}
void solve() {
	int n, m, k;
	std::cin >> n >> m >> k;
	int o = std::max(n, m);
	std::vector<int> rev(o + 1);
	auto Rev = [&](int x) -> int {
		int res = 0;
		while (x) {
			res = res * 10 + x % 10;
			x /= 10;
		}
		return res;
	};	
	for (int i = 1; i <= o; i ++) {
		rev[i] = Rev(i);
	}
	// what...
	int ans = -1, x = -1, y = -1;
	std::map<int, int> mp_B, mp_A;
	for (int i = 1; i <= m; i ++) { // b.
		int v = 1ll * rev[i] * qmi(i, mod - 2) % mod;
		mp_B[v] ++;
	}
	int r = m;
	int now = 0;
	for (int i = 1; i <= n; i ++) {
		int u = 1ll * i * qmi(rev[i], mod - 2) % mod;
		now += mp_B[u];
		mp_A[u] ++;
		while (true) {
			if (r < 1) break;
			int v = 1ll * rev[r] * qmi(r, mod - 2) % mod;
			if (now - mp_A[v] >= k) {
				now -= mp_A[v];
				mp_B[v] --;
				r --;
			} else {
				break;
			}
		}
		// std::cout << now << ' ' << i << ' ' << r << ' ' << ans << '\n';
		if (now >= k) {
			if (ans == -1) {
				ans = i * r;
				x = i;
				y = r;
			} else if (i * r < ans) {
				ans = i * r;
				x = i;
				y = r;
			}
		}
	}
	if (ans == -1) {
		std::cout << -1 << '\n';
	} else {
		std::cout << x << ' ' << y << '\n';
	}
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}
/*
*/