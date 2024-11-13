#include<bits/stdc++.h>
using i64 = long long;
// const int mod = 998244353;
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::set<int> st;
	for (int i = 0; i <= n; i ++) { // have hurt.
		st.insert(i);
	}
	int B = std::sqrt(n);
	std::vector<int> pos(n + 1), nxt(n + B * 2 + 1), w(n + B * 2 + 1);
	std::vector<int> f(n + B * 2 + 1), g(n + B * 2 + 1);
	for (int i = 0; i <= n; i ++) {
		pos[i] = i / B;
		nxt[i] = (pos[i] + 1) * B;
		f[i] = i + 1;
	}
	auto check = [&](int u) -> void {
		f[u] = u + k, g[u] = 1;
		int x = pos[u];
		int l = x * B, r = std::min((x + 1) * B - 1, n);
		for (int i = r; i >= l; i --) {
			if (f[i] > r) nxt[i] = f[i], w[i] = g[i];
			else nxt[i] = nxt[f[i]], w[i] = w[f[i]] + g[i];
		}
	};
	int mx = 0;
	for (int i = 1; i <= n; i ++) {
		int x;
		std::cin >> x;
		mx = std::max(mx, x);

		auto it = st.lower_bound(x - k);
		std::vector<int> del;
		while (it != st.end() && *it < x) {
			check(*it);
			del.push_back(*it);
			it ++;
		}
		for (auto it : del) {
			st.erase(it);
		}
		int u = 0, ans = 0;
		while (u < mx) {
			ans += w[u];
			u = nxt[u];
		}
		std::cout << ans << ' ';
	}
	std::cout << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}