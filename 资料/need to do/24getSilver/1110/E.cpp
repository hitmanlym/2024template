#include<bits/stdc++.h>
using i64 = long long;
#define int i64

const int mod = 998244353;
int qmi(int a, int b = mod - 2) {
    if (a == 0) return 0;
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
	int n;
	std::cin >> n;
	std::vector<std::vector<int> > e(n + 1);
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	std::vector<int> deep(n + 1), fa(n + 1), leaf;
	auto dfs = [&](auto self, int u, int p) -> void {
		fa[u] = p;
		deep[u] = deep[p] + 1;
		for (auto v : e[u]) {
			if (v == p) continue;
			self(self, v, u);
		}
		if (e[u].size() == 1 && u != 1) {
			leaf.push_back(u);
		}
	};
	dfs(dfs, 1, 0);
	std::sort(leaf.begin(), leaf.end(), [&](auto x, auto y) {
		return deep[x] < deep[y];
	});
	std::vector<int> ans(n + 1), vis(n + 1);
	ans[1] = 1;
	vis[1] = 1;
	for (auto o : leaf) {
		int now = o;
		std::vector<int> link;
		while (! vis[now]) {
			link.push_back(now);
			now = fa[now];
		}
		int N = link.size(), x = 1;
		while (link.size()) {
			int u = link.back();
			vis[u] = 1;
			// std::cout << u << ' ';
			ans[u] = (N - x) * qmi(N - x + 1) % mod * ans[fa[u]] % mod;
			link.pop_back();
			x ++;
		}
		// std::cout << '\n';
	}
	for (int i = 1; i <= n; i ++) {
		std::cout << ans[i] << ' ';
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