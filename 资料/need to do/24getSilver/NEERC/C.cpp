#include<bits/stdc++.h>
using i64 = long long;
const int N = 1e6 + 10;
const int M = 5e6 + 10;
struct Sgt {
	int idx;
	struct node {
		int lc, rc, x;
		i64 sum;
		i64 cnt;
	};
	std::vector<node> t;
	Sgt() {}
	void init() {
		t.assign(M, (node){0, 0, 0, 0ll, 0});
		idx = 0;
	}
	void make(int &p) {
		if (p) return ;
		p = ++ idx;
	}
	void insert(int &p, int l, int r, int pos, int v) { // times
		make(p);
		t[p].cnt += v;
		t[p].sum += 1ll * pos * v;
		if (l == r) return ;
		int mid = l + r >> 1;
		if (pos <= mid) {
			insert(t[p].lc, l, mid, pos, v);
		} else {
			insert(t[p].rc, mid + 1, r, pos, v);
		}
	}
	i64 query(int p, int l, int r, int num) {
		if (! p) return 0ll;
		if (l == r) {
			return 1ll * l * std::min(t[p].cnt, (i64)num);
		}
		int mid = l + r >> 1;
		if (t[t[p].lc].cnt >= num) {
			return query(t[p].lc, l, mid, num);
		} else {
			return query(t[p].rc, mid + 1, r, num - t[t[p].lc].cnt) + t[t[p].lc].sum;
		}
	}
};
void solve() {
	int n, k, m;
	std::cin >> n >> k >> m;
	Sgt t;
	t.init();
	int rt = 0;
	std::vector<std::vector<std::array<int, 2> > > a(n + 2);
	for (int i = 1; i <= m; i ++) {
		int l, r, c, p;
		std::cin >> l >> r >> c >> p; // 先删后加
		a[l].push_back({p, c});
		a[r + 1].push_back({p, -c});
	}
	i64 ans = 0;
	for (int i = 1; i <= n; i ++) {
		for (auto it : a[i]) {
			t.insert(rt, 1, N, it[0], it[1]);
		}
		ans += t.query(rt, 1, N, k);
	}
	std::cout << ans << '\n';
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