#include<bits/stdc++.h>
using i64 = long long;

//Dicnic
//-----------------------------------------
const int V = 1010;
const int E = 10100;
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

//-----------------------------------------
void solve(int n, int m, int x) {
	int s = n + m + 1, t = s + 1;
	FlowGraph<int> g;
	g.init(s, t, t);
	for (int i = 1; i <= x; i ++) {
		int a, b;
		std::cin >> a >> b;
		g.addedge(a, n + b, 1);
	}
	for (int i = 1; i <= n; i ++) {
		g.addedge(s, i, 1);
	}
	for (int i = 1; i <= m; i ++) {
		g.addedge(n + i, t, 1);
	}
	int ans = g.dicnic();
	std::cout << ans << ' ';
	for (int i = 1; i <= n; i ++) {
		if (! g.dis[i]) {
			std::cout << "r" << i << ' ';
		}
	}
	for (int i = n + 1; i <= n + m; i ++) {
		if (g.dis[i]) {
			std::cout << "c" << i - n << ' ';
		}
	}
	std::cout << '\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;int n, m, x;
	//std::cin >> t;
	while (std::cin >> n >> m >> x) {
		if (n == 0) break;
		solve(n, m, x);
	}
	return 0;
}