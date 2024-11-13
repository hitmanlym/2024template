#include<bits/stdc++.h>
using i64 = long long;
const int V = 210;
const int E = 5100;
template<typename T>
struct FlowGraph {
	int s, t, vtot, etot, head[V], dis[V], cur[V];
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
					if (v == t) return true;
					q.push(v);
				}
			}
		}
		return false;
	}
	T dfs(int u, T m) {
		if (u == t) return m;
		T flow = 0;
		for (int i = cur[u]; ~i; cur[u] = i = e[i].nxt) {
			if (e[i].f && dis[e[i].v] == dis[u] + 1) {
				T f = dfs(e[i].v, std::min(m, e[i].f));
				e[i].f -= f;
				e[i ^ 1].f += f;
				m -= f;
				flow += f;
				if (! m) break;
			}
		}
		if (! flow) dis[u] = -1;
		return flow;
	}
	T dicnic() {
		T flow = 0;
		while (bfs()) {
			flow += dfs(s, std::numeric_limits<T>::max());
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
	int n, m;
	std::cin >> n >> m;
	int s = n * 2 + 1, t = s + 1;
	FlowGraph<int> g;
	g.init(s, t, t);
	for (int i = 1; i <= m; i ++) {
		int u, v;
		std::cin >> u >> v;
		g.addedge(n + u, v, inf);
	}
	std::vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		g.addedge(s, i, a[i]);
	}
	for (int i = 1; i <= n; i ++) {
		std::cin >> b[i];
		g.addedge(i, i + n, b[i]);
	}
	int X;
	std::cin >> X;
	g.addedge(X + n, t, inf);
	int ans = g.dicnic();
	std::cout << ans << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	while (t --) {
		solve();
	}
	return 0;
}
/*
5 5
1 2
1 3
2 4
4 5
3 5
3 5 7 9 11
5 5 5 50 50
5

30

4 4
1 2
1 3
2 4
3 4
3 5 7 9
5 10 15 30
4

24


*/