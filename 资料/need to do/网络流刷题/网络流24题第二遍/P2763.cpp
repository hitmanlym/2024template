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
	int k, n;
	std::cin >> k >> n;
	int s = n + k + 1;
	int t = n + k + 2;
	int sum = 0;
	FlowGraph<int> g;
	g.init(s, t, t);
	for (int i = 1; i <= k; i ++) {
		int x;
		std::cin >> x;
		sum += x;
		g.addedge(n + i, t, x);
	}
	for (int i = 1; i <= n; i ++) {
		int x;
		std::cin >> x;
		g.addedge(s, i, 1);
		for (int j = 0; j < x; j ++) {
			int y;
			std::cin >> y;
			g.addedge(i, y + n, 1);
		}
	}
	int res = g.dicnic();
	if (res != sum) {
		std::cout << "No Solution!\n";
		return ;
	}
	for (int i = n + 1; i <= n + k; i ++) {
		std::cout << i - n <<  ": ";
		for (int j = g.head[i]; ~j; j = g.e[j].nxt) {
			int v = g.e[j].v, w = g.e[j].f;
			if (v <= n && w) {
				std::cout << v << ' ';
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