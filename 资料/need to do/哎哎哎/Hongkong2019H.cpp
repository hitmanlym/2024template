#include<bits/stdc++.h>
using i64 = long long;
const int inf = 1e9 + 10;
struct Block {
	int n, b;
	std::vector<int> blo, a;
	std::vector<std::vector<int> > v;
	void init(int n) {
		this -> n = n;
		this -> b = (int) std::pow(n, 0.5);
		blo.assign(n + 1, 0);
		v.assign(n + 1, {});
		a.assign(n + 1, 0);
		//st.assign(n + 1, {});
		for (int i = 1; i <= n; i ++) {
			blo[i] = (i - 1) / b + 1;
		}
	}
	void add(int x, int c) {
		int p = blo[x];
		//v[p].insert(c);
		a[x] = c;
		int l = v[p].size();
		v[p].push_back(c);

		while (l > 0 && v[p][l - 1] > v[p][l]) {
			std::swap(v[p][l - 1], v[p][l]);
			l --;
		}
		//st[p].insert(x);
	}
	int query(int l, int r, int c) {
		int res = inf, p = blo[l], q = blo[r];
		for (int i = l; i <= std::min(r, p * b); i ++) {
			if (a[i]) {
				res = std::min(res, std::abs(a[i] - c));
			}
		}
		if (p == q) return res;
		for (int i = (q - 1) * b + 1; i <= r; i ++) {
			if (a[i]) {
				res = std::min(res, std::abs(a[i] - c));
			}
		}

		for (int i = p + 1; i < q; i ++) {
			int l = v[i].size();
			if (! l) continue;
			auto it = std::lower_bound(v[i].begin(), v[i].end(), c) - v[i].begin();
			if (it != l) {
				res = std::min(res, v[i][it] - c);
			}
			if (it != 0) {
				res = std::min(res, c - v[i][it - 1]);
			}
		}
		return res;
	}
};

int read(){
    int red=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') f=-f;ch=getchar();}
    while(ch>='0'&&ch<='9') red=red*10+ch-48,ch=getchar();
    return red*f;
}
void solve() {
	int n, m;
	n = read();
	m = read();
	Block t;
	t.init(n);
	while (m --) {
		int op;
		//std::cin >> op;
		op = read();
		if (op & 1) {
			int l, r, v;
			//std::cin >> l >> r >> v;
			l = read();
			r = read();
			v = read();
			int res = t.query(l, r, v);
			if (res == inf) {
				res = -1;
			}
			std::cout << res << '\n';
		} else {
			int x, v;
			//std::cin >> x >> v;
			x = read();
			v = read();
			t.add(x, v);
		}
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	t = read();
	while (t --) {
		solve();
	}
	return 0;
}