#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 1e9 + 7;
int qmi(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) {
			res = res * a % mod;
		}
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::vector<int> > e(n + 1);
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	std::vector<int> a(n + 1), p(n + 1);
	int sum = 0;
	for (int i = 1; i <= n; i ++) {
		int u, v;
		std::cin >> a[i] >> u >> v;
		p[i] = u * qmi(v, mod - 2) % mod;
		sum += a[i];
	}
	for (int i = 1; i <= n; i ++) {
		a[i] = a[i] * qmi(sum, mod - 2) % mod;
	}
	std::vector<int> ans(n + 1);
	std::vector<std::vector<int> > np(n + 1, std::vector<int>(n + 1));
	
	// auto dfs = [&](auto self, int u, int p) -> void {
		
	// };
	// for (int i = 1; i <= n; i ++) {
	// 	dfs(dfs, i, 0);
	// 	for (int j = 1; j <= n; j ++) {
	// 		ans[j] = (ans[j] + np[])
	// 	}
	// }
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