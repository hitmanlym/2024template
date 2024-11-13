#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n, m, k;
	std::cin >> n >> m >> k;
	std::vector<std::array<int, 2> > e(m + 1);
	std::vector<std::vector<int> > t(k * 4 + 1);
	auto update = [&](auto self, int u, int l, int r, int x, int y, int id) -> void {
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
	for (int i = 1; i <= m; i ++) {
		std::cin >> e[i][0] >> e[i][1];
		int l, r;
		std::cin >> l >> r;
		update(update, 1, 1, k, l + 1, r, i); // 这个时间段内
	}
	std::vector<int> fa(2 * n + 1), height(2 * n + 1); // 扩展域并查集
	for (int i = 1; i <= 2 * n; i ++) {
		fa[i] = i;
		height[i] = 1;
	}
	std::vector<std::array<int, 3> > st;
	std::vector<int> ans(k + 1);
	auto find = [&](int u) -> int { // 秩
		while (u != fa[u]) u = fa[u];
		return fa[u];
	};
	auto merge = [&](int x, int y) -> void {
		int fx = find(x), fy = find(y);
		if (height[fx] > height[fy]) {
			std::swap(fx, fy);
		}
		st.push_back({fx, fy, height[fx] == height[fy]});
		fa[fx] = fy;
		if (height[fx] == height[fy]) {
			height[fy] ++;
		}
	};
	auto fuck = [&](auto self, int u, int l, int r) -> void {
		int op = 1;
		int p = st.size();
		for (int i = 0; i < t[u].size(); i ++) {
			int aa = e[t[u][i]][0], bb = e[t[u][i]][1];
			int a = find(aa);
			int b = find(bb);
			if (a == b) {
				// 非二分图
				op = 0;
				break;
			}
			merge(aa, bb + n);
			merge(bb, aa + n);
		}
		if (op) {
			if (l == r) ans[l] = 1;
			else {
				int mid = l + r >> 1;
				self(self, u << 1, l, mid);
				self(self, u << 1 | 1, mid + 1, r);
			}
		}
		while (st.size() > p) {
			auto it = st.back();
			st.pop_back();
			height[it[1]] -= it[2];
			fa[it[0]] = it[0];
		}
	};
	fuck(fuck, 1, 1, k);
	for (int i = 1; i <= k; i ++) {
		std::cout << (ans[i] ? "Yes" : "No") << '\n';
	}
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