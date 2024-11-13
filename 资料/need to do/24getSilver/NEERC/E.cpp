#include<bits/stdc++.h>
using i64 = long long;
//#define int i64
struct Sgt {
	int n;
	struct node {
		int l, r;
		i64 sum;
		int cnt;
	};
	std::vector<node> t;
	Sgt(){}
	void init(int n) {
		this -> n = n;
		t.assign(4 * n + 1, (node){0, 0, 0ll, 0});
		build(1, 1, n);
	}
	void build(int u, int l, int r) {
		t[u] = {l, r, 0ll, 0};
		if (l == r) return ;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
	}
	void pushup(int u) {
		t[u].sum = t[u << 1].sum + t[u << 1 | 1].sum;
		t[u].cnt = t[u << 1].cnt + t[u << 1 | 1].cnt;
	}
	void add(int u, int l, int r, int val) {
		if (t[u].l >= l && t[u].r <= r) {
			t[u].sum += 1ll * (t[u].r - t[u].l + 1) * val;
			t[u].cnt = 1;
			return ;
		}
		int mid = t[u].l + t[u].r >> 1;
		if (l <= mid) {
			add(u << 1, l, r, val);
		} else {
			add(u << 1 | 1, l, r, val);
		}
		pushup(u);
	}
	i64 query(int u, int l, int r) {
		if (t[u].l >= l && t[u].r <= r) {
			return t[u].sum;
		}
		i64 res = 0;
		int mid = t[u].l + t[u].r >> 1;
		if (l <= mid) {
			res += query(u << 1, l, r);
		} 
		if (mid < r) {
			res += query(u << 1 | 1, l, r);
		}
		return res;
	}
	int num(int u, int l, int r) {
		if (t[u].l >= l && t[u].r <= r) {
			return t[u].cnt;
		}
		int res = 0;
		int mid = t[u].l + t[u].r >> 1;
		if (l <= mid) {
			res += num(u << 1, l, r);
		} 
		if (mid < r) {
			res += num(u << 1 | 1, l, r);
		}
		return res;
	}
	void add(int x, int val) {
		add(1, x, x, val);
	}
	i64 sum(int x) {
		if (x < 1) return 0ll;
		return query(1, 1, x);
	}
	int num(int x) {
		if (x < 1) return 0;
		return num(1, 1, x);
	}
};
void solve() {
	int n, m;
	i64 T;
	std::cin >> n >> m >> T;
	std::map<int, std::vector<int> > a;
	for (int i = 1; i <= n; i ++) {
		int x;
		std::cin >> x;
		a[x].push_back(i);
	}
	int max = 0, d = 1;
	Sgt t;
	t.init(n);
	for (auto it : a) {
		for (auto v : it.second) {
			t.add(v, it.first);
		}
		int l = 1, r = n, res = 0;
		while (l <= r) {
			int mid = l + r >> 1;
			if (2ll * t.sum(mid) <= T) {
				l = mid + 1;
				res = mid;
			} else {
				r = mid - 1;
			}
		}
		// if (! res) continue;

		int Num = t.num(res);
		Num -= Num % m;
		l = 1, r = res;
		int op = 0; // 第 Num 个。
		while (l <= r) {
			int mid = l + r >> 1;
			if (t.num(mid) <= Num) {
				l = mid + 1;
				op = mid;
			} else {
				r = mid - 1;
			}
		}
		i64 SUM = t.sum(op);

		l = op + 1, r = n;
		int ANS = op;
		while (l <= r) {
			int mid = l + r >> 1;
			if (t.sum(mid) + SUM <= T && t.num(mid) - Num <= m) {
				ANS = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		int fuck = t.num(ANS);
		// std::cout << res << ' ' << Num << ' ' << op << " " << SUM << ' ' << ANS << " " << fuck << '\n';
		
		if (fuck > max) {
			max = fuck;
			d = it.first;
		}
		// [1 -- res]
	}
	std::cout << max << ' ' << d << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}