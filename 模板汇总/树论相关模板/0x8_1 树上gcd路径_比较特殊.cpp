#include<bits/stdc++.h>
using i64 = long long;
const int M = 2e5;
struct TreeDicider {
	int n;
	std::vector<std::vector<int>> fact, muti, e;
	std::vector<int> dep, fa;
	std::vector<int> a;
	std::vector<i64> dp;
	TreeDicider() {}
	void init(int n, std::vector<int> b) {
		this -> n = n;
		fact.assign(M + 1, {});
		muti.assign(M + 1, {});
		dp.assign(M + 1, 0);
		a.assign(b.begin(), b.end());
		e.assign(n + 1, {});
		dep.assign(n + 1, 0);
		fa.assign(n + 1, 0);
		Pre();
	}
	void Pre() {
		for (int i = 1; i <= M; i ++) {
			for (int j = i; j <= M; j += i) {
				fact[j].push_back(i);
			}
		}

		for (int i = 1; i <= n; i ++) {
			for (auto x : fact[a[i]]) {
				muti[x].push_back(i);
			}
		}
	}
	void addEdge(int u, int v) {
		e[u].push_back(v);
		e[v].push_back(u);
	}

	void Treedfs(int u, int p) {
		fa[u] = p;
		if (p == 0) dep[u] = 1;
		else dep[u] = dep[p] + 1;
		for (auto v : e[u]) {
			if (v == p) {
				continue;
			} 
			Treedfs(v, u);
		}
	}
	void work() {
		int ans = 0;
		std::vector<int> in(n + 1, 0), siz(n + 1, 0);
		for (int i = 2; i <= M; i ++) {
			std::sort(muti[i].begin(), muti[i].end(), [&](int x, int y) {
				return dep[x] > dep[y];
			});
			for (auto u : muti[i]) {
				in[u] = 1;
				siz[u] = 1;
			}

			for (auto u : muti[i]) {
				if (fa[u] == 0) continue;
				ans = std::max(ans, siz[u] + siz[fa[u]]);
				if (in[fa[u]]) {
					siz[fa[u]] = std::max(siz[fa[u]], 1 + siz[u]), siz[u] = 0;
				}
			}
			for (auto u : muti[i]) {
				ans = std::max(ans, siz[u]);
			}

			for (auto u : muti[i]) {
				in[u] = 0;
				siz[u] = 0;
			}
		}
		std::cout << ans << '\n';
	}
};
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> v(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> v[i];
	}
	TreeDicider t;
	t.init(n, v);
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		t.addEdge(u, v);
	}
	t.Treedfs(1, 0);
	t.work();
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}