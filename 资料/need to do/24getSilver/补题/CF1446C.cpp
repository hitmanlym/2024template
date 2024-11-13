#include<bits/stdc++.h>
using i64 = long long;
const int N = 3e6;
int b[N][2], f[N], tot = 0;
void insert(int x) {
	int u = 0;
	for (int i = 30; i >= 0; i --) {
		int p = x >> i & 1;
		if (! b[u][p]) b[u][p] = ++ tot;
		u = b[u][p];
	}
}
int dfs(int u) {
	if (! b[u][0] && ! b[u][1]) return 1;
	if (! b[u][0]) return dfs(b[u][1]);
	if (! b[u][1]) return dfs(b[u][0]);
	return std::max(dfs(b[u][0]), dfs(b[u][1])) + 1;
}
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		insert(a[i]);
	}
	int ans = n - dfs(0);
	std::cout << ans << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}