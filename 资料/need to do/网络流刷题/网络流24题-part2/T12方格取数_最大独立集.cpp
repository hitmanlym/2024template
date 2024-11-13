#include<bits/stdc++.h>
using i64 = long long;

//Dicnic
//-----------------------------------------
const int V = 5010;
const int E = 50100;
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
	int n, m;
	std::cin >> n >> m;
	int s = n * m + 1, t = n * m + 2;
	std::vector<std::vector<int> > e(n + 1, std::vector<int>(m + 1));
	FlowGraph<i64> g;
	g.init(s, t, t);
	i64 sum = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			std::cin >> e[i][j];
			sum += e[i][j];
			if ((i + j) & 1) {
				g.addedge(s, (i - 1) * m + j, e[i][j]);
				if (i > 1) g.addedge((i - 1) * m + j, (i - 2) * m + j, inf);
				if (i < n) g.addedge((i - 1) * m + j, i * m + j, inf);
				if (j > 1) g.addedge((i - 1) * m + j, (i - 1) * m + j - 1, inf);
				if (j < m) g.addedge((i - 1) * m + j, (i - 1) * m + j + 1, inf);
			} else {
				g.addedge((i - 1) * m + j, t, e[i][j]);
			}
		}
	}
	std::cout << sum - g.dicnic() << '\n';
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