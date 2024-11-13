#include<bits/stdc++.h>
using i64 = long long;
#define int i64
std::mt19937_64 rng(std::random_device{}()); // 好像 _64 更快

struct FHQTreap{
	struct node {
		int x, rnd, size;
		int lc, rc;
		int add, rev, sum, max;
	};
	std::vector<node> t;
	int tot, root;

	FHQTreap() {}
	void init() {
		tot = 0, root = 0;
		t.assign({});
		t.push_back((node){0, 0, 0, 0, 0, 0, 0, 0, 0});
	}

	int newNode(int x) {
		t.push_back((node){x, (int)rng(), 1, 0, 0, 0, 0, 0, 0});
		return ++ tot;
	}
	void pushup(int u) {
		t[u].size = t[t[u].lc].size + t[t[u].rc].size + 1;
		t[u].sum = t[t[u].lc].sum + t[t[u].rc].sum + t[u].x;

		t[u].max = t[u].x;
		if (t[u].lc) { t[u].max = std::max(t[u].max, t[t[u].lc].max); };
		if (t[u].rc) { t[u].max = std::max(t[u].max, t[t[u].rc].max); };
	}
	void pushdown(int u) {
		t[t[u].lc].sum += (t[t[u].lc].size * t[u].add);
		t[t[u].rc].sum += (t[t[u].rc].size * t[u].add);
		t[t[u].lc].add += t[u].add, t[t[u].rc].add += t[u].add;
		t[t[u].lc].max += t[u].add, t[t[u].rc].max += t[u].add;
		t[t[u].lc].x += t[u].add, t[t[u].rc].x += t[u].add;
		t[u].add = 0;
		if (! t[u].rev) return ;
		std::swap(t[u].lc, t[u].rc);
		t[u].rev ^= 1;
		if (t[u].lc) t[t[u].lc].rev ^= 1;
		if (t[u].rc) t[t[u].rc].rev ^= 1;
	}
	void split_val(int u, int val, int &x, int &y) {
		if (! u) { x = y = 0; return ; }
		pushdown(u);
		if (t[u].x <= val) {
			x = u;
			split_val(t[u].rc, val, t[x].rc, y);
		} else {
			y = u;
			split_val(t[u].lc, val, x, t[y].lc);
		}
		pushup(u);
	}
	void split_size(int u, int size, int &x, int &y) {
		if (! u) { x = y = 0; return ; }
		pushdown(u);
		if (t[t[u].lc].size < size) {
			x = u;
			split_size(t[u].rc, size - (t[t[u].lc].size + 1), t[x].rc, y);
		} else {
			y = u;
			split_size(t[u].lc, size, x, t[y].lc);
		}
		pushup(u);
	}
	int merge(int x, int y) {
		if (! x || ! y) { return x + y; }
		if (t[x].rnd < t[y].rnd) {
			pushdown(x);
			t[x].rc = merge(t[x].rc, y);
			pushup(x);
			return x;
		} else {
			pushdown(y);
			t[y].lc = merge(x, t[y].lc);
			pushup(y);
			return y;
		}
	}

	void insert(int x) {
		int l, r;
		split_val(root, x, l, r);
		root = merge(merge(l, newNode(x)), r);
	}
	void del(int x) {
		int l, r, xx, yy;
		split_val(root, x, l, r);
		split_val(l, x - 1, xx, yy);
		yy = merge(t[yy].lc, t[yy].rc); // only erase one
		root = merge(merge(xx, yy), r);
	}
	int getrank_by_val(int x) {
		int l, r;
		split_val(root, x - 1, l, r);
		int res = t[l].size + 1;
		root = merge(l, r);
		return res;
	}
	int getval_by_Rank(int u, int k) {
		int p = t[t[u].lc].size + 1;
		if (p == k) { return t[u].x; }
		if (p < k) return getval_by_Rank(t[u].rc, k - p);
		return getval_by_Rank(t[u].lc, k);
	}
	int getval_by_rank(int k) {
		return getval_by_Rank(root, k);
	}
	int getpre(int x) {
		int l, r;
		split_val(root, x - 1, l, r);
		int res = getval_by_Rank(l, t[l].size);
		root = merge(l, r);
		return res;
	}
	int getnxt(int x) {
		int l, r;
		split_val(root, x, l, r);
		int res = getval_by_Rank(r, 1);
		root = merge(l, r);
		return res;
	}
	void add(int l, int r, int val) {
		int x, y, xx, yy;
		split_size(root, l - 1, x, y);
		split_size(y, r - l + 1, xx, yy);
		t[xx].sum += (t[xx].size * val);
		t[xx].add += val;
		t[xx].x += val;
		y = merge(xx, yy);
		root = merge(x, y);
	}
	void reverse(int l, int r) {
		int x, y, xx, yy;
		split_size(root, l - 1, x, y);
		split_size(y, r - l + 1, xx, yy);
		t[xx].rev ^= 1;
		y = merge(xx, yy);
		root = merge(x, y);
	}
	int max(int l, int r) {
		int x, y, xx, yy;
		split_size(root, l - 1, x, y);
		split_size(y, r - l + 1, xx, yy);
		int res = t[xx].max;
		y = merge(xx, yy);
		root = merge(x, y);
		return res;
	}
	void print(int u) {
		if (! u) return ;
		pushdown(u);
		print(t[u].lc);
		std::cout << t[u].x << ' ';
		print(t[u].rc);
	}
	void insertque(int x, std::vector<int> v) {
		int l, r, ll, rr;
		split_size(root, x - 1, l, r);
		int temp = 0;
		for (auto it : v) {
			temp = merge(temp, newNode(it));
		}
		root = merge(merge(l, temp), r);
	}
};

void solve() {
	FHQTreap t;
	t.init();
	int n, m;
	std::cin >> n >> m;
	for (int i = 1; i <= n; i ++) {
		t.insert(0);
	}
	while (m --) {
		int l, r, x, y, op;
		std::cin >> op;
		if (op == 1) {
			std::cin >> l >> r >> x;
			t.add(l, r, x);
		} else {
			std::cin >> l >> r;
			if (op == 2) {
				t.reverse(l, r);
			} else {
				std::cout << t.max(l, r) << '\n';
			}
		}
	}
}
signed main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}