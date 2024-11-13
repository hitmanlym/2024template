#include<bits/stdc++.h>
using i64 = long long;
const int M = 1e7 + 10;
const int N = 1e9;
struct Dinamic_SegmentTree {
	int idx;
	struct node {
		int lc, rc, x;
		i64 sum;
		int cnt;
	};
	std::vector<node> t;
	Dinamic_SegmentTree() {}
	void init() {
		t.assign(M, (node){0, 0, 0, 0ll, 0});
		idx = 0;
	}
	void make(int &p) {
		if (p) return ;
		p = ++ idx;
	}
	void insert(int &p, int l, int r, int pos, i64 v) {
		make(p);
		t[p].cnt += v;
		t[p].sum += 1ll* pos * v;
		if (l == r) return ;
		int mid = l + r >> 1;
		if (pos <= mid) insert(t[p].lc, l, mid, pos, v);
		else insert(t[p].rc, mid + 1, r, pos, v);
	}
	int query(int p, int l, int r, i64 val) { 
		if (! p) return 0;
		if (l == r) {
			return std::min(1ll * t[p].cnt, val / l);
		}
		int mid = l + r >> 1;
		if (t[t[p].lc].sum >= val) {
			return query(t[p].lc, l, mid, val);
		} else {
			return t[t[p].lc].cnt + query(t[p].rc, mid + 1, r, val - t[t[p].lc].sum);
		}
	}	
};
void solve() {
	Dinamic_SegmentTree t;
	t.init();
	int rt = 0;
	i64 lim = 0;
	int n, q;
	std::cin >> n >> q;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		if (a[i] <= 0) lim -= a[i];
		else t.insert(rt, 1, N, a[i], 1);
	}
	
	for (int i = 1; i <= q; i ++) {
		int x, v;
		std::cin >> x >> v;
		if (a[x] <= 0) {
			lim += a[x];
		} else {
			t.insert(rt, 1, N, a[x], -1);
		}
		a[x] = v;
		if (a[x] <= 0) {
			lim -= a[x];
		} else {
			t.insert(rt, 1, N, a[x], 1);
		}
		std::cout << t.query(rt, 1, N, lim) + 1 << '\n';
	}
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