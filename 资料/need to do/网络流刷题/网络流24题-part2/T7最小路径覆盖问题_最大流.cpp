#include<bits/stdc++.h>
using i64 = long long;

//Dicnic
//-----------------------------------------
const int V = 1010;
const int E = 10100;
int pre[V], h[V];
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
				if (f && u != s && e[i].v != t && u <= (t - 2) / 2) { // 要保证正确！
					h[(e[i].v - (t - 2) / 2)] = 1;
					pre[u] = (e[i].v - (t - 2) / 2);
				}
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
void solve() {
	int n, m;
	std::cin >> n >> m;
	int s = 2 * n + 1, t = 2 * n + 2;
	FlowGraph<int> g;
	g.init(s, t, t);
	for (int i = 1; i <= n; i ++) {
		g.addedge(s, i, 1);
		g.addedge(i + n, t, 1);
	}
	for (int i = 1; i <= m; i ++) {
		int u, v;
		std::cin >> u >> v;
		g.addedge(u, v + n, 1);
	}
	int res = g.dicnic();
	

	std::vector<bool> vis(n + 1);
	for (int i = 1; i <= n; i ++) {
		if (! h[i]) {
			for (int u = i; u; u = pre[u]) {
				vis[u] = 1;
				std::cout << u << ' ';
			}
			std::cout << '\n';
		}
	}
	std::cout << n - res << '\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}