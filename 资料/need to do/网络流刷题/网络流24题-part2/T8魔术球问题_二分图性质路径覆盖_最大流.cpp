#include<bits/stdc++.h>
using i64 = long long;

//Dicnic
//-----------------------------------------
const int V = 10010;
const int E = 100100;
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
				if (f && u != s && e[i].v != t) {
					pre[u / 2] = e[i].v / 2;
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
	int n;
	std::cin >> n;
	FlowGraph<int> g;
	int s = 1, t = 10000;
	g.init(s, t, t);
	int it = 0, num = 0;
	while (it <= n) {
		num ++;
		g.addedge(s, num * 2, 1);
		g.addedge(num * 2 + 1, t, 1);
		for (int i = std::sqrt(num) + 1; i * i < (num * 2); i ++) {
			g.addedge((i * i - num) * 2, num * 2 + 1, 1); // small -> big
		}
		int res = g.dicnic();
		if (! res) {
			h[++ it] = num;
		}
	}
	std::cout << num - 1 << '\n';
	std::vector<bool> vis(num + 1);
	for (int i = 1; i <= n; i ++) {
		if (! vis[h[i]]) {
			for (int u = h[i]; u; u = pre[u]) {
				vis[u] = 1;
				std::cout << u << ' ';
			}
			std::cout << '\n';
		}
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