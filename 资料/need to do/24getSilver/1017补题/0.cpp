#include<bits/stdc++.h>
using i64 = long long;
const int inf = 1e9 + 7;
struct RollTree {
	int idx, n;
	struct node {
		int lc, rc, min;
	};
	std::vector<node> t;
	RollTree() {}
	int init(int n) {
		this -> n = n;
		t.assign(n * 30 + 1, (node){0, 0, inf});
		idx = 0;
		int res = 0;
		build(res, 1, n);
		return res;
	}
	void make(int &p) {
		p = ++ idx;
	}
	void pushup(int p) {
		t[p].min = std::min(t[t[p].lc].min, t[t[p].rc].min);
	}
	void build(int &p, int l, int r) {
		make(p);
		if (l == r) {
			// t[p].min = inf;
			return ;
		}
		int mid = l + r >> 1;
		build(t[p].lc, l, mid);
		build(t[p].rc, mid + 1, r);
		pushup(p);
	}
	void reput(int &p, int pre, int l, int r, int x, int v) { 
		make(p);
		t[p] = t[pre];
		// t[p].min = std::min(t[p].min, v);
		if (l == r) {
			t[p].min = v;
			return ;
		}
		int mid = l + r >> 1;
		if (x <= mid) {
			reput(t[p].lc, t[pre].lc, l, mid, x, v);
		} else {
			reput(t[p].rc, t[pre].rc, mid + 1, r, x, v);
		}
		pushup(p);
	}
	int query_sum(int p, int l, int r, int x, int y) {
		if (l >= x && r <= y) {
			return t[p].min;
		}
		int mid = l + r >> 1;
		int ans = inf;
		if (x <= mid) {
			ans = std::min(ans, query_sum(t[p].lc, l, mid, x, y));
		}
		if (y > mid) {
			ans = std::min(ans, query_sum(t[p].rc, mid + 1, r, x, y));
		}
		return ans;
	}
	void Reput(int &p, int pre, int x, int v) {     // 单点修改
		reput(p, pre, 1, n, x, v);
	}
	int Query_sum(int p, int x, int y) {
		return query_sum(p, 1, n, x, y);
	}
}; // 放在dfn序上...

void solve() {
	int n, rt;
	std::cin >> n >> rt;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	std::vector<std::vector<int> > e(n + 1);
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	std::vector<int> dfn(n + 1), rev(n + 1), siz(n + 1, 1), dep_u(n + 1);
	std::vector<std::vector<int> > dep(n + 1);
	int dn = 0;
	auto dfs = [&](auto self, int u, int p, int deep) -> void {
		dep[deep].push_back(u);
		dep_u[u] = deep;
		dfn[u] = ++ dn;
		rev[dn] = u;
		for (auto v : e[u]) {
			if (v == p) continue;
			self(self, v, u, deep + 1);
			siz[u] += siz[v];
		}
	};
	dfs(dfs, rt, 0, 1);
	RollTree t;
	std::vector<int> rtt(n + 1);
	rtt[0] = t.init(n);
	for (int i = 1; i <= n; i ++) {
		int u = rtt[i - 1], v = rtt[i- 1];
		for (auto it : dep[i]) {
			t.Reput(v, u, dfn[it], a[it]);
			u = v;
		}
		rtt[i] = v;
	}
	int q;
	std::cin >> q;
	int res = 0;
	while (q --) {
		int p, k;
		std::cin >> p >> k;
		p = (p + res) % n + 1;
		k = (k + res) % n;
		int d = std::min(n, dep_u[p] + k); // rtt[this]
		int l = dfn[p], r = l + siz[p] - 1;
		res = t.Query_sum(rtt[d], l, r);
		std::cout << res << '\n';
	}
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
/*
*/