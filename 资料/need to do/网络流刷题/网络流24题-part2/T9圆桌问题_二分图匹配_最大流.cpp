#include<bits/stdc++.h>
using i64 = long long;

//Dicnic
//-----------------------------------------
const int V = 5010;
const int E = 50100;
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
				T f = dfs(e[i].v, std::min(m, e[i].f)); // 虽然最终可以得到，但 vector 添加会保留中间退流
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
	int m, n;
	std::cin >> m >> n;
	std::vector<int> op(m + 1);
	int s = m + n + 1, t = m + n + 2;
	FlowGraph<int> g;
	g.init(s, t, t);
	int sum = 0;
	for (int i = 1; i <= m; i ++) {
		int x;
		std::cin >> x;
		op[i] = x;
		sum += x;
		g.addedge(s, i, x);
	}
	for (int i = 1; i <= n; i ++) {
		int x;
		std::cin >> x;
		g.addedge(i + m, t, x);
	}
	for (int i = 1; i <= m; i ++) {
		for (int j = 1; j <= n; j ++) {
			g.addedge(i, j + m, 1);
		}
	}
	int res = g.dicnic();
	if (res != sum) {
		std::cout << 0 << '\n';
		return ;
	}
	std::cout << 1 << '\n';
	for (int i = 1; i <= m; i ++) {
		for (int j = g.head[i]; ~j; j = g.e[j].nxt) {
			if (g.e[j].v > m && g.e[j].v != s && ! g.e[j].f) {
				std::cout << g.e[j].v - m << ' ';
			}
		}
		std::cout << '\n';
	}
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