#include <bits/stdc++.h>
using i64 = long long;

struct Block {
	int n, b;
	std::vector<int> blo, a, add;
	std::vector<std::vector<int> > v;
	void init(int n, std::vector<int> it) {
		this -> n = n;
		this -> b = std::sqrt(n);
		blo.assign(n + 1, 0);
		v.assign(n + 1, {});
		add.assign(n + 1, 0);

		a.assign(it.begin(), it.end());
		for (int i = 1; i <= n; i ++) {
			blo[i] = (i - 1) / b + 1;
			v[blo[i]].push_back(a[i]);
		}
	}
	void pre() {
		for (int i = 1; i <= blo[n]; i ++) {
			std::sort(v[i].begin(), v[i].end());
		}
	}
	void resort(int x) { // 还能降，必然连续段加, 用类似归并排序
		v[x].clear();
		for (int i = (x - 1) * b + 1; i <= std::min(x * b, n); i ++) {
			v[x].push_back(a[i]);
		}
		std::sort(v[x].begin(), v[x].end());
	}
	void addq(int l, int r, int c) {
		int p = blo[l], q = blo[r];
		for (int i = l; i <= std::min(r, p * b); i ++) {
			a[i] += c;
		}
		resort(p);

		if (p == q) return ;

		for (int i = (q - 1) * b + 1; i <= r; i ++) {
			a[i] += c;
		}
		resort(q);

		for (int i = p + 1; i < q; i ++) {
			add[i] += c;
		}
	}
	int query(int l, int r, int c) {
		int res = -1, p = blo[l], q = blo[r];
		for (int i = l; i <= std::min(r, p * b); i ++) {
			if (a[i] + add[p] < c) res = std::max(res, a[i] + add[p]);
		}

		if (p == q) return res;

		for (int i = (q - 1) * b + 1; i <= r; i ++) {
			if (a[i] + add[q] < c) res = std::max(res, a[i] + add[q]);
		}

		for (int i = p + 1; i < q; i ++) {
			int p = std::lower_bound(v[i].begin(), v[i].end(), c - add[i]) - v[i].begin();
			if (p == 0 || v[i][p - 1] + add[i] >= c) continue;
			res = std::max(res, v[i][p - 1] + add[i]);
		}
		return res;
	}
};
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	Block t;
	t.init(n, a);
	t.pre();
	int m = n;
	while (m --) {
		int op, l, r, c;
		std::cin >> op >> l >> r >> c;
		if (! op) {
			t.addq(l, r, c);
		} else {
			std::cout << t.query(l, r, c) << '\n';
		}
	}
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    // std::cin >> t;
    while (t --) {
    	solve ();
    }
	return 0;
}
