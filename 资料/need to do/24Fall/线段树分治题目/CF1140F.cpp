#include<bits/stdc++.h>
using i64 = long long;
const int N = 3e5 + 10;
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::array<int, 2> > e(1);
	std::vector<std::vector<int> > t(n * 4 + 1);
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
	std::map<std::array<int, 2>, std::array<int, 2> > tim;
	for (int i = 1; i <= n; i ++) {
		int x, y;
		std::cin >> x >> y;
		if (tim.count({x, y})) {
			update(update, 1, 1, n, tim[{x, y}][0], i - 1, tim[{x, y}][1]);
			//std::cout << x << ' ' << y << ' ' << tim[{x, y}][0] << ' ' << i - 1 << '\n';
			tim.erase({x, y});
		} else {
			tim[{x, y}] = {i, (int)e.size()};
			e.push_back({x, y});
		}
	}
	for (auto it : tim) {
		update(update, 1, 1, n, (it.second)[0], n, (it.second)[1]);
		//std::cout << (it.first)[0] << ' ' << (it.first)[1] << ' ' << (it.second)[0] << ' ' << n << '\n';
	}
	i64 nowans = 0;
	std::vector<int> fa(2 * N + 1), height(2 * N + 1); // 扩展域并查集
	std::vector<std::array<int, 2> > cnt(N * 2 + 1);
	for (int i = 1; i <= 2 * N; i ++) {
		fa[i] = i;
		height[i] = 1;
	}
	for (int i = 1; i <= N; i ++) {
		cnt[i][0] ++;
		cnt[i + N][1] ++;
	}
	std::vector<std::array<int, 3> > st;
	std::vector<i64> ans(n + 1);
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
		nowans -= 1ll * cnt[fy][0] * cnt[fy][1];
		nowans -= 1ll * cnt[fx][0] * cnt[fx][1];
		cnt[fy][0] += cnt[fx][0];
		cnt[fy][1] += cnt[fx][1];

		nowans += 1ll * cnt[fy][0] * cnt[fy][1];
		if (height[fx] == height[fy]) {
			height[fy] ++;
		}
	};
	auto fuck = [&](auto self, int u, int l, int r) -> void {
		int p = st.size();
		for (int i = 0; i < t[u].size(); i ++) {
			int aa = e[t[u][i]][0], bb = e[t[u][i]][1];
			int a = find(aa);
			int b = find(bb + N);
			if (a == b) continue;
			merge(aa, bb + N);
		}
		if (l == r) {
			ans[l] = nowans;
		} else {
			int mid = l + r >> 1;
			self(self, u << 1, l, mid);
			self(self, u << 1 | 1, mid + 1, r);
		}
		while (st.size() > p) {
			auto it = st.back();
			st.pop_back();
			height[it[1]] -= it[2];
			fa[it[0]] = it[0];
			nowans -= 1ll * cnt[it[1]][0] * cnt[it[1]][1];
			cnt[it[1]][0] -= cnt[it[0]][0];
			cnt[it[1]][1] -= cnt[it[0]][1];
			nowans += 1ll * cnt[it[0]][0] * cnt[it[0]][1];
			nowans += 1ll * cnt[it[1]][0] * cnt[it[1]][1];
		}
	};
	fuck(fuck, 1, 1, n);
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