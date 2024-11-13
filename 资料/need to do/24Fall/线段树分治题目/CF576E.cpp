#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<array>
using i64 = long long;
void solve() {
	int n, m, k, q;
	std::cin >> n >> m >> k >> q;
	std::vector<std::array<int, 2> > e(m + 1);
	std::vector<std::vector<int> > t(q * 4 + 1);
	auto update = [&](auto self, int u, int l, int r, int x, int y, int id) -> void {
		if (x > y) return ;
		if (x <= l && y >= r) {
			t[u].push_back(id);
			return ;
		}
		int mid = l + r >> 1;
		if (x <= mid) {
			self(self, u << 1, l, mid, x, y, id);
		} 
		if (y > mid) {
			self(self, u << 1 | 1, mid + 1, r, x, y, id);
		}
	};
	std::vector<int> pos(m + 1);
	for (int i = 1; i <= m; i ++) {
		std::cin >> e[i][0] >> e[i][1];
		pos[i] = q + 1;
	}
	std::vector<std::array<int, 2> > col(q + 1);
	for (int i = 1; i <= q; i ++) {
		std::cin >> col[i][0] >> col[i][1];
	}
	std::vector<std::vector<int> > 
		fa(k + 1, std::vector<int>(2 * n + 1)), 
		height(k + 1, std::vector<int>(2 * n + 1));
	for (int i = 1; i <= k; i ++) {
		for (int j = 1; j <= 2 * n; j ++) {
			fa[i][j] = j;
		}
	}
	for (int i = q; i >= 1; i --) {
		if (pos[col[i][0]] > i + 1) {
			update(update, 1, 1, q, i + 1, pos[col[i][0]] - 1, i);
		}
		pos[col[i][0]] = i;
	}
	std::vector<std::array<int, 4> > st;

	std::vector<int> pre(m + 1);

	auto find = [&](int c, int u) -> int { // 秩
		while (u != fa[c][u]) u = fa[c][u];
		return fa[c][u];
	};
	auto merge = [&](int c, int x, int y) -> void {
		int fx = find(c, x), fy = find(c, y);
		if (fx == fy) return ;
		if (height[c][fx] > height[c][fy]) {
			std::swap(fx, fy);
		}
		st.push_back({fx, fy, height[c][fx] == height[c][fy], c});
		fa[c][fx] = fy;
		if (height[c][fx] == height[c][fy]) {
			height[c][fy] ++;
		}
	};
	auto fuck = [&](auto self, int u, int l, int r) -> void {
		int p = st.size();
		for (auto i : t[u]) {
			int c = col[i][1], id = col[i][0];
			int aa = e[id][0], bb = e[id][1];
			int fa = find(c, aa), fb = find(c, bb);
			if (fa == fb) continue;
			merge(c, aa, bb + n);
			merge(c, bb, aa + n);
		}
		if (l == r) {
			if (find(col[l][1], e[col[l][0]][0]) == find(col[l][1], e[col[l][0]][1])) {
				std::cout << "NO\n";
				col[l][1] = pre[col[l][0]];
			} else {
				std::cout << "YES\n";
				pre[col[l][0]] = col[l][1];
			}
		} else {
			int mid = l + r >> 1;
			self(self, u << 1, l, mid);
			self(self, u << 1 | 1, mid + 1, r);
		}
		while (st.size() > p) {
			auto it = st.back();
			st.pop_back();
			int c = it[3];
			height[c][it[1]] -= it[2];
			fa[c][it[0]] = it[0];
		}
	};
	fuck(fuck, 1, 1, q);
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