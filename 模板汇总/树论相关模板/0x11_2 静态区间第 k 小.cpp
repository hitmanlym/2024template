#include<bits/stdc++.h> // 静态区间第 k 小
using i64 = long long;

struct RollTree {
	int idx, n;
	struct node {
		int lc, rc;
		int val;
	};
	std::vector<node> t;
	std::vector<int> a;
	RollTree() {}
	int init(int n) {
		this -> n = n;
		t.assign(n * 32 + 1, (node){0, 0, 0});
		a.assign(n + 1, 0);
		idx = 0;
		int res = 0;
		build(res, 1, n);
		return res;
	}
	void make(int &p) {
		p = ++ idx;
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
	}
	void insert(int &p, int pre, int l, int r, int x) {
		make(p);
		t[p] = t[pre];
		t[p].val ++;
		if (l == r) return ;
		int mid = l + r >> 1;
		if (x <= mid) insert(t[p].lc, t[pre].lc, l, mid, x);
		else insert(t[p].rc, t[pre].rc, mid + 1, r, x);
	}
	int query_kth(int L, int R, int l, int r, int k) {
		if (l >= r) return l;
		int num = t[t[R].lc].val - t[t[L].lc].val;
		int mid = l + r >> 1;
		if (num >= k) {
			return query_kth(t[L].lc, t[R].lc, l, mid, k);
		} else {
			return query_kth(t[L].rc, t[R].rc, mid + 1, r, k - num);
		}
	}
	void Insert(int &p, int pre, int x) {
		insert(p, pre, 1, n, x);
	}
	int Query_kth(int L, int R, int k) {
		return query_kth(L, R, 1, n, k); // 小
	}
};

void solve() {
	int n, q;
	std::cin >> n >> q;
	std::vector<int> a(n + 1), v;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		v.push_back(a[i]);
	}
	std::sort(v.begin(), v.end());
	v.erase(std::unique(v.begin(), v.end()), v.end());
	std::vector<int> rt(n + 1);
	RollTree t;
	rt[0] = t.init(n);
	for (int i = 1; i <= n; i ++) {
		int k = std::lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
		t.Insert(rt[i], rt[i - 1], k);
	}
	while (q --) {
		int l, r, k;
		std::cin >> l >> r >> k;
		int op = t.Query_kth(rt[l - 1], rt[r], k);
		std::cout << v[op - 1] << '\n';
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