#include <bits/stdc++.h>
using i64 = long long;


int addnum = 0; // 定期重构
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

	}
	void rebuild(int o) {
		a.assign(1, 0);
		for (int i = 1; i <= blo[n]; i ++) {
			for (auto it : v[i]) {
				a.push_back(it);
			}
		}
		this -> n = o;
		this -> b = std::sqrt(n);
		blo.assign(n + 1, 0);
		add.assign(n + 1, 0);
		v.assign(n + 1, {});

		for (int i = 1; i <= n; i ++) {
			blo[i] = (i - 1) / b + 1;
			v[blo[i]].push_back(a[i]);
		}
	}
	void insert(int l, int r) {
		int k = 1;
		while (l > v[k].size()) {
			l -= v[k].size();
			k ++;
		}

		v[k].insert(v[k].begin() + l - 1, r);

		if (addnum >= b) {
			rebuild(n + addnum);
			addnum = 0;
		}
	}
	int query(int r) {
		int k = 1;
		while (r > v[k].size()) {
			r -= v[k].size();
			k ++;
		}
		return v[k][r - 1];
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
		if (! op) { // l 前插入 r
			t.insert(l, r);
			addnum ++;
		} else { // 第 r 个位置的数
			std::cout << t.query(r) << '\n';
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
