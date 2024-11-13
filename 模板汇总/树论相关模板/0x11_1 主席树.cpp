#include<bits/stdc++.h>
using i64 = long long;

struct RollTree {
	int idx, n;
	struct node {
		int lc, rc;
		i64 val;
		i64 tag;
	};
	std::vector<node> t;
	std::vector<int> a;
	RollTree() {}
	int init(int n, std::vector<int> op) {
		this -> n = n;
		t.assign(n * 25 + 1, (node){0, 0, 0ll, 0ll});
		a.assign(op.begin(), op.end());
		idx = 0;
		int res = 0;
		build(res, 1, n);
		return res;
	}
	void make(int &p) {
		p = ++ idx;
	}
	void pushup(int p) {
		t[p].val = t[t[p].lc].val + t[t[p].rc].val;
	}
	void build(int &p, int l, int r) {
		make(p);
		if (l == r) {
			t[p].val = a[l];
			return ;
		}
		int mid = l + r >> 1;
		build(t[p].lc, l, mid);
		build(t[p].rc, mid + 1, r);
		pushup(p);
	}
	void add(int &p, int pre, int l, int r, int x, int y, i64 v) {
		make(p);
		t[p] = t[pre];
		t[p].val += 1ll * v * (std::min(r, y) - std::max(l, x) + 1);
		if (l >= x && r <= y) {
			t[p].tag += v;
			return ;
		}  // 标记永久化.
		int mid = l + r >> 1;
		if (x <= mid) {
			add(t[p].lc, t[pre].lc, l, mid, x, y, v);
		}
		if (y > mid) {
			add(t[p].rc, t[pre].rc, mid + 1, r, x, y, v);
		}
	}

	void reput(int &p, int pre, int l, int r, int x, i64 v) { 
		make(p);
		t[p] = t[pre];
		if (l == r) {
			t[p].val = v;
			return ;
		}
		int mid = l + r >> 1;
		if (x <= mid) {
			reput(t[p].lc, t[pre].lc, l, mid, x, v);
		} else {
			reput(t[p].rc, t[pre].rc, mid + 1, r, x, v);
		}
	}
	int query_val(int p, int l, int r, int x) {
		if (l == r) {
			return t[p].val;
		}
		int mid = l + r >> 1;
		if (x <= mid) {
			return query_val(t[p].lc, l, mid, x);
		} else {
			return query_val(t[p].rc, mid + 1, r, x);
		}
	}
	i64 query_sum(int p, int l, int r, int x, int y) {
		if (l >= x && r <= y) {
			return t[p].val;
		}
		int mid = l + r >> 1;
		i64 ans = 0;
		if (x <= mid) {
			ans += query_sum(t[p].lc, l, mid, x, y);
		}
		if (y > mid) {
			ans += query_sum(t[p].rc, mid + 1, r, x, y);
		}
		return ans + 1ll * t[p].tag * (std::min(r, y) - std::max(l, x) + 1);
	}
	void Reput(int &p, int pre, int x, int v) {     // 单点修改
		reput(p, pre, 1, n, x, v);
	}
	int Query_val(int p, int x) {					// 版本单点查询
		return query_val(p, 1, n, x);
	}
	void Add(int &p, int pre, int x, int y, int v) {
		add(p, pre, 1, n, x, y, v);
	}
	i64 Query_sum(int p, int x, int y) {
		return query_sum(p, 1, n, x, y);
	}
};

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	RollTree t;
	std::vector<int> rt(m + 1), rev(m + 1);
	rt[0] = t.init(n, a);
	int pick = 0, now = 0;
	for (int i = 1; i <= m; i ++) {
		char op;
		std::cin >> op;
		if (op == 'Q') {
			int l, r;
			std::cin >> l >> r;
			std::cout << t.Query_sum(rt[pick], l, r) << '\n';
		} else if (op == 'C') {
			int l, r, d;
			std::cin >> l >> r >> d;
			rev[++ now] = ++ pick;
			t.Add(rt[pick], rt[pick - 1], l, r, d);
		} else if (op == 'H') {
			int l, r, ti;
			std::cin >> l >> r >> ti;
			std::cout << t.Query_sum(rt[rev[ti]], l, r) << '\n';
		} else if (op == 'B') {
			std::cin >> now;
			rt[++ pick] = rt[rev[now]];
		}
	}
}

signed main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}