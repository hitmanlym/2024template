#include<bits/stdc++.h>
using i64 = long long;
//Dicnic
//-----------------------------------------
const int V = 300010;
const int E = 1000100;
template<typename T>
struct FlowGraph {
	int s, t, vtot, etot, head[V], dis[V], cur[V], pre[V], pre_edge[V];
	struct edge {
		int v, nxt;
		T f;
	} e[E * 2];
	void addedge(int u, int v, T f) {
		e[etot] = {v, head[u], f}; head[u] = etot ++;
		e[etot] = {u, head[v], 0}; head[v] = etot ++;
	}
	bool bfs() {
		for (int i = 1; i <= vtot; i ++) {
			dis[i] = 0;
			cur[i] = head[i];
		}
		std::queue<int> q;
		q.push(s); dis[s] = 1;
		while (! q.empty()) {
			int u = q.front(); q.pop();
			for (int i = head[u]; ~i; i = e[i].nxt) {
				if (e[i].f && ! dis[e[i].v]) {
					int v = e[i].v;
					dis[v] = dis[u] + 1;
					pre[v] = u;
					pre_edge[v] = i;
					if (v == t) return true;
					q.push(v);
				}
			}
		}
		return false;
	}
	T dicnic() {
		T flow = 0;
		while (bfs()) {
			flow ++;
			int x = t;
			while (x != s) {
				int i = pre_edge[x];
				e[i].f -= 1;
				e[i ^ 1].f += 1;
				x = pre[x];
			}
		}
		return flow;
	}
	void init(int _s, int _t, int _vtot) {
		s = _s;
		t = _t;
		vtot = _vtot;
		for (int i = 1; i <= vtot; i ++) {
			head[i] = -1;
		}
	}
};
const int inf = 1e9 + 7;
void solve() {
	int n, m, a, b, d, c;
	std::cin >> n >> m >> a >> b >> c >> d;
	std::vector<std::array<int, 2> > x(n + 1), y(m + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> x[i][0] >> x[i][1];
	}
	FlowGraph<int> g;
	int s = n * 2 + m + 1, t = s + 1;
	g.init(s, t, t);
	for (int i = 1; i <= n; i ++) {
		g.addedge(s, i, c - d);
		g.addedge(s, i + n, d); // vel
	}
	auto dis = [&](auto l, auto r) -> int {
		//return std::abs(l[0] - r[0]) + std::abs(l[1] - r[1]);
		return 1ll * (l[0] - r[0]) * (l[0] - r[0]) + 1ll * (l[1] - r[1] ) * (l[1] - r[1]);
	};
	for (int i = 1; i <= m; i ++) {
		std::cin >> y[i][0] >> y[i][1];
	}
	int res = 0;
	for (int i = 1; i <= m; i ++) {
		int u = y[i][0], v = y[i][1];
		for (int j = 1; j <= n; j ++) {
			int op = dis((std::array<int, 2>){u, v}, x[j]);
			if (op <= 1ll * a * a) {
				g.addedge(j, n * 2 + i, 1);
			} 
			if (op <= 1ll * b * b) {
				g.addedge(j + n, n * 2 + i, 1);
			}
		}
		g.addedge(n * 2 + i, t, 1);
		res += g.dicnic();
		if (res != i) {
			std::cout << i << '\n';
			return ;
		}
	}
	std::cout << -1 << '\n';
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