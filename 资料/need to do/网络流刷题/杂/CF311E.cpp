#include<bits/stdc++.h>
using i64 = long long;

//Dicnic
//-----------------------------------------
const int V = 1010;
const int E = 10100;
const int inf = 1e9 + 7;
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
void solve() {
	int n, m, h;
	std::cin >> n >> m >> h;
	int s = n + m + 1, t = s + 1;
	FlowGraph<int> g;
	g.init(s, t, t);

	std::vector<int> b(n + 1), v(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> b[i];
	}
	for (int i = 1; i <= n; i ++) {
		std::cin >> v[i];
		if (b[i] == 0) {
			g.addedge(s, i, v[i]);
		} else {
			g.addedge(i, t, v[i]);
		}
	}
	int sum = 0;

	for (int i = 1; i <= m; i ++) {
		int o, w, k;
		std::cin >> o >> w >> k;
		sum += w;
		for (int j = 1; j <= k; j ++) {
			int u;
			std::cin >> u;
			if (o) {
				g.addedge(u, n + i, inf);
			} else {
				g.addedge(n + i, u, inf);
			}
		}
		int q;
		std::cin >> q;
		if (o) {
			g.addedge(n + i, t, w + q * h);
		} else {
			g.addedge(s, n + i, w + q * h);
		}
	}

	int ans = g.dicnic();
	std::cout << sum - ans << '\n';
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