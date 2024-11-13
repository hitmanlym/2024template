#include <bits/stdc++.h>
using i64 = long long;
#define int i64
const int inf = 1e18;
using pii = std::array<int, 2>;
struct SegmentGraph { // buildGraph
    int n, T, src, cnt;
    std::vector<std::vector<pii> > e;
    std::vector<int> rev, d;
    std::vector<bool> vis;
    SegmentGraph() {}
    void init(int n) {
    	this -> n = n;
    	this -> T = 4 * n;
    	this -> cnt = T * 2; // ++newNode, push_bcak
    	rev.assign(n + 1, 0);
    	d.assign(T * 2 + 1, inf);
    	e.assign(T * 2 + 1, {});
    	vis.assign(T * 2 + 1, 0);
    	build(1, 1, n);
    	for (int i = 1; i <= n; i ++) {
    		e[rev[i]].push_back({rev[i] + T, 0});
    		e[rev[i] + T].push_back({rev[i], 0});
    	}
    }
    int newNode() {
    	d.push_back(inf);
    	e.push_back({});
    	vis.push_back(0);
    	return ++ cnt;
    }
    void build(int u, int l, int r) {
    	if (l == r) {
    		rev[l] = u;
    		return ;
    	}
    	int mid = l + r >> 1;
    	e[u].push_back({u << 1, 0});
    	e[u].push_back({u << 1 | 1, 0});
    	e[(u << 1) + T].push_back({u + T, 0});
    	e[(u << 1 | 1) + T].push_back({u + T, 0});
    	build(u << 1, l, mid);
    	build(u << 1 | 1, mid + 1, r);
    }
    void pointToPoint(int x, int y, int z) {
    	e[x + T].push_back({y, z});
    }
    void segToPoint(int u, int l, int r, int L, int R, int x, int z) {
    	if (l >= L && r <= R) {
    		e[u + T].push_back({x, z});
    		return ;
    	}
    	int mid = l + r >> 1;
    	if (L <= mid) {
    		segToPoint(u << 1, l, mid, L, R, x, z);
    	} 
    	if (R > mid) {
    		segToPoint(u << 1 | 1, mid + 1, r, L, R, x, z);
    	}
    }
    void pointToSeg(int u, int l, int r, int x, int L, int R, int z) {
    	if (l >= L && r <= R) {
    		e[x].push_back({u, z});
    		return ;
    	}
    	int mid = l + r >> 1;
    	if (L <= mid) {
    		pointToSeg(u << 1, l, mid, x, L, R, z);
    	} 
    	if (R > mid) {
    		pointToSeg(u << 1 | 1, mid + 1, r, x, L, R, z);
    	}
    }

    void PTP(int x, int y, int z) {
    	pointToPoint(rev[x], rev[y], z);
    }
    void STP(int l, int r, int x, int z) {
    	segToPoint(1, 1, n, l, r, rev[x], z);
    }
    void PTS(int x, int l, int r, int z) {
    	pointToSeg(1, 1, n, rev[x] + T, l, r, z);
    }
    void STS(int x, int y, int p, int q, int z) {
    	// d, e, vis
    	int o = newNode();
    	segToPoint(1, 1, n, x, y, o, z);
    	pointToSeg(1, 1, n, o, p, q, z);
    }
    std::vector<int> DJ(int s) {
    	src = rev[s] + T;

    	d[src] = 0;
    	std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
    	q.push({0, src});
    	while (! q.empty()) {
    		auto it = q.top();
    		q.pop();
    		int u = it[1];
    		if (vis[u]) continue;
    		vis[u] = 1;
    		for (auto op : e[u]) {
    			int v = op[0], w = op[1];
    			if (d[v] > d[u] + w) {
    				d[v] = d[u] + w;
    				q.push({d[v], v});
    			}
    		}
    	}
    	return d;
    }
};

void solve() {
	int n, m, s;
	std::cin >> n >> m >> s;
	SegmentGraph t;
	t.init(n);
	for (int i = 1; i <= m; i ++) {
		int op;
		std::cin >> op;
		if (op == 1) {
			int x, y, z;
			std::cin >> x >> y >> z;
			t.PTP(x, y, z * 2);
		} 
		if (op == 2) {
			int x, l, r, w;
			std::cin >> x >> l >> r >> w;
			t.PTS(x, l, r, w * 2);
		}
		if (op == 3) {
			int x, l, r, w;
			std::cin >> x >> l >> r >> w;
			t.STP(l, r, x, w * 2);
		}
		if (op == 4) { // 将点到点，点到区间 权值 * 2， 最后一起 / 2 即可。
			int a, b, c, d, w;
			std::cin >> a >> b >> c >> d >> w;
			t.STS(a, b, c, d, w);
		}
	}
	auto it = t.DJ(s);
	for (int i = 1; i <= n; i ++) {
		int d = it[t.rev[i]];
		if (d == inf) d = -2;
		std::cout << d / 2 << ' ';
	}
	std::cout << '\n';
/*
	int n, m, s;			 
	std::cin >> n >> m >> s;
	SegmentGraph t;
	t.init(n);
	for (int i = 1; i <= m; i ++) {
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		t.STS(a, b, c, d, 1);
		t.STS(c, d, a, b, 1);
	}
	auto it = t.DJ(s);
	for (int i = 1; i <= n; i ++) {
		int d = it[t.rev[i]];
		std::cout << d / 2 << '\n';
	}*/
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
