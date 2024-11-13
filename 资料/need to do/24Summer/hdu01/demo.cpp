#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
using i64 = long long;

#define ull unsigned long long
const int N = 1e6 + 10;
struct Dinamic_SegmentTree {
	int idx;
	struct node {
		int lc, rc;
		ull xsum, ysum, num;
	};
	std::vector<node> t;
	Dinamic_SegmentTree() {}
	void init() {
		t.push_back({0, 0, 0, 0, 0});
		idx = 0;
	}
	void make(int &p) {
		if (p) return ;
		p = ++ idx;
		t.push_back({0, 0, 0, 0, 0});
	}
	void insert(int &p, int l, int r, ull pos) {
		make(p);
		t[p].num ++;
		t[p].xsum += pos;
		t[p].ysum += pos * pos;

		if (l == r) return ;
		int mid = l + r >> 1;
		if (pos <= mid) insert(t[p].lc, l, mid, pos);
		else insert(t[p].rc, mid + 1, r, pos);
	}
	ull queryX(int p, int l, int r, int ll, int rr) { 
		if (! p) return 0;
		if (l >= ll && r <= rr) {
			return t[p].xsum;
		}
		int mid = l + r >> 1;
		ull res = 0;
		if (ll <= mid && t[p].lc != 0) {
			res += queryX(t[p].lc, l, mid, ll, rr);
		}
		if (rr > mid && t[p].rc != 0) {
			res += queryX(t[p].rc, mid + 1, r, ll, rr);
		}
		return res;
	}	
	ull queryY(int p, int l, int r, int ll, int rr) { 
		if (! p) return 0;
		if (l >= ll && r <= rr) {
			return t[p].ysum;
		}
		int mid = l + r >> 1;
		ull res = 0;
		if (ll <= mid && t[p].lc != 0) {
			res += queryY(t[p].lc, l, mid, ll, rr);
		}
		if (rr > mid && t[p].rc != 0) {
			res += queryY(t[p].rc, mid + 1, r, ll, rr);
		}
		return res;
	}	
	ull queryN(int p, int l, int r, int ll, int rr) { 
		if (! p) return 0;
		if (l >= ll && r <= rr) {
			return t[p].num;
		}
		int mid = l + r >> 1;
		ull res = 0;
		if (ll <= mid && t[p].lc != 0) {
			res += queryN(t[p].lc, l, mid, ll, rr);
		}
		if (rr > mid && t[p].rc != 0) {
			res += queryN(t[p].rc, mid + 1, r, ll, rr);
		}
		return res;
	}	
};
int n;
std::vector<std::vector<int> > e(N);
std::vector<int> a(N);
std::vector<int> siz(N);
std::vector<std::vector<int> > xy(N);
std::vector<ull> fuck(N); 

Dinamic_SegmentTree son;
int rt = 0;

ull ans = 0;
void dfs(int u, int p) {
	siz[u] = 1;
	Dinamic_SegmentTree t;
	t.init();
	int r = 0;
	t.insert(r, 1, N, a[u]);
	xy[u].push_back(a[u]);
	for (auto v : e[u]) {
		if (v == p) continue;
		dfs(v, u);
		fuck[u] += fuck[v];
		if (siz[v] > siz[u]) {
			//std::cout << "???\n";
			std::swap(xy[u], xy[v]);
			std::swap(son, t);
			std::swap(rt, r);
		}
		for (auto it : xy[v]) {/*
			ull lnum = t.queryN(r, 1, N, 1, it);
			ull lsum = t.queryX(r, 1, N, 1, it);
			ull rsum = t.queryX(r, 1, N, it + 1, N);
			ull rY = t.queryY(r, 1, N, it + 1, N);*/
			//ull rnum = t.queryN(r, 1, N, it + 1, N);
			//std::cout << "WTF??? " << it << ' ' << rnum << '\n';

			//std::cout << "!!! " << it << ' ' << lnum << ' ' << lsum << ' ' << rsum << ' ' << rY << '\n';

			fuck[u] += (1ull * it * (it * lnum - lsum) + rY - it * rsum) * 2;
		}
		for (auto it : xy[v]) {
			xy[u].push_back(it);
			t.insert(r, 1, N, it);
		}
		siz[u] += siz[v];
	}
	ans ^= fuck[u];
	//std::cout << u << ' ' << fuck[u] << '\n';

	std::swap(son, t);
	std::swap(rt, r);
}

void solve() {
	std::cin >> n;
	son.init();
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	dfs(1, 0);
	std::cout << ans << '\n';
}
// x, x_sum, x^2, x^2_sum, 1, num_sum
int main() { 
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}