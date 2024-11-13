#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::array<int, 2> > e(m + 1);
	for (int i = 1; i <= m; i ++) {
		std::cin >> e[i][0] >> e[i][1];
	}
	int k;
	std::cin >> k;
	std::vector<std::vector<int> > t(k * 4 + 1);
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
	std::vector<std::vector<int> > br(m + 1);	
	for (int i = 1; i <= m; i ++) {
		br[i].push_back(0);
	}
	for (int i = 1; i <= k; i ++) {
		int c;
		std::cin >> c;
		while (c --) {
			int id;
			std::cin >> id;
			br[id].push_back(i);
		}
	}
	for (int i = 1; i <= m; i ++) {
		br[i].push_back(k + 1);
	}
	for (int i = 1; i <= m; i ++) {
		for (int j = 1; j < br[i].size(); j ++) {
			update(update, 1, 1, k, br[i][j - 1] + 1, br[i][j] - 1, i);
		}
	}

	std::vector<int> fa(n + 1), height(n + 1), siz(n + 1); // 扩展域并查集
	for (int i = 1; i <= n; i ++) {
		fa[i] = i;
		height[i] = 1;
		siz[i] = 1;
	}
	std::vector<std::array<int, 4> > st;
	std::vector<int> ans(k + 1, 1);
	auto find = [&](int u) -> int { // 秩
		while (u != fa[u]) u = fa[u];
		return fa[u];
	};
	auto merge = [&](int x, int y) -> bool {
		int fx = find(x), fy = find(y);
		if (fx == fy) return false;
		if (height[fx] > height[fy]) {
			std::swap(fx, fy);
		}
		st.push_back({fx, fy, height[fx] == height[fy], siz[fx]});
		fa[fx] = fy;
		siz[fy] += siz[fx];
		if (height[fx] == height[fy]) {
			height[fy] ++;
		}
		if (siz[fy] == n) {
			return true;
		}
		return false;
	};
	auto fuck = [&](auto self, int u, int l, int r) -> void {
		int op = 0;
		int p = st.size();
		for (int i = 0; i < t[u].size(); i ++) {
			int aa = e[t[u][i]][0], bb = e[t[u][i]][1];
			if (merge(aa, bb)) {
				op = 1;
				break;
			}
		}
		if (! op) {
			if (l == r) {
				ans[l] = 0;
			}
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
			siz[it[1]] -= it[3];
			fa[it[0]] = it[0];
		}
	};
	fuck(fuck, 1, 1, k);
	for (int i = 1; i <= k; i ++) {
		std::cout << (ans[i] ? "Connected" : "Disconnected") << '\n';
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