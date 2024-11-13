#include<bits/stdc++.h>
using i64 = long long;
// dsu


// bright new dsu;trick !!!
// split big son and other, save more weight value
void solve() {
	// just one odd -> ok.
	std::vector<int> ok(23);
	for (int i = 0; i < 22; i ++) {
		ok[i] = 1 << i;
	}
	ok[22] = 0;

	int n;
	std::cin >> n;
	std::vector<std::vector<std::array<int, 2>> > e(n + 1);
	for (int i = 2; i <= n; i ++) {
		int u;
		char c;
		std::cin >> u >> c;
		e[u].push_back({i, 1 << (c - 'a')});
	}
	//
	std::vector<int> Xor(n + 1), dep(n + 1), L(n + 1), R(n + 1), rev(n + 1), son(n + 1), siz(n + 1);
	int idx = 0;
	auto get = [&](auto self, int u, int p) -> void {
		siz[u] = 1;
		L[u] = ++ idx;
		rev[idx] = u;
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			Xor[v] = Xor[u] ^ w;
			dep[v] = dep[u] + 1;
			self(self, v, u);
			siz[u] += siz[v];
			if (siz[v] > siz[son[u]]) {
				son[u] = v;
			}
		}
		R[u] = idx;
	};	
	get(get, 1, 0);
	std::vector<int> ans(n + 1);
	std::vector<int> res(1 << 23);
	auto dfs = [&](auto self, int u, int p) -> void {
		int max = 0;
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			if (v == son[u]) continue;
			self(self, v, 0);
			max = std::max(max, ans[v]);
		}
		if (son[u]) {
			self(self, son[u], 1);
			max = std::max(max, ans[son[u]]);
		}
		//--------------------------------------------------------
		for (int i = 0; i <= 22; i ++) {
			if (res[Xor[u] ^ ok[i]]) {
				max = std::max(max, res[Xor[u] ^ ok[i]] - dep[u]);
			}
		}
		res[Xor[u]] = std::max(res[Xor[u]], dep[u]);
		//--------------------------------------------------------
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			if (v == son[u]) continue;
			for (int j = L[v]; j <= R[v]; j ++) {
				for (int i = 0; i <= 22; i ++) {
					if (res[Xor[rev[j]] ^ ok[i]]) {
						max = std::max(max, res[Xor[rev[j]] ^ ok[i]] + dep[rev[j]] - 2 * dep[u]);
					}
				}
			}
			for (int j = L[v]; j <= R[v]; j ++) {
				res[Xor[rev[j]]] = std::max(res[Xor[rev[j]]], dep[rev[j]]);
			}
		}

		if (! p) {
			for (int i = L[u]; i <= R[u]; i ++) {
				res[Xor[rev[i]]] = 0;
			}
		}

		ans[u] = max;
	};
	dfs(dfs, 1, 1);
	for (int i = 1; i <= n; i ++) {
		std::cout << ans[i] << ' ';
	}
	std::cout << '\n';
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