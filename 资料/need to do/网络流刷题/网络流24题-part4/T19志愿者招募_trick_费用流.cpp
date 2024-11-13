#include<bits/stdc++.h>
using i64 = long long;
//最小费用最大流 - 最大费用最大流
// MCMF ： minimum cost maximum flow

const int V = 2010;
const int E = 20100;
const i64 inf = 1e12 + 1;
template<typename T>
struct MinCostGraph {
	int s, t, vtot, etot, cur[V], head[V], pre[V];
	T dis[V], flow, cost;
	bool vis[V];

	struct edge {
		int v, nxt;
		T f, c;
	} e[E * 2];
	void addedge(int u, int v, T f, T c, T f2 = 0) {
		e[etot] = {v, head[u], f, c}; head[u] = etot ++;
		e[etot] = {u, head[v], f2, -c}; head[v] = etot ++;
	}
	bool spfa() {
		T inf = std::numeric_limits<T>::max() / 2;
		for (int i = 1; i <= vtot; i ++) {
			dis[i] = inf;
			vis[i] = false;
			pre[i] = -1;
		}
		dis[s] = 0, vis[s] = true;
		std::queue<int> q; q.push(s);
		while (! q.empty()) {
			int u = q.front();
			for (int i = head[u]; ~i; i = e[i].nxt) {
				int v = e[i].v;
				if (e[i].f && dis[v] > dis[u] + e[i].c) {
					dis[v] = dis[u] + e[i].c;
					pre[v] = i;
					if (! vis[v]) {
						vis[v] = 1;
						q.push(v);
					}
				}
			}
			q.pop();
			vis[u] = false;
		}
		return dis[t] != inf;
	}

	void augment() {
		int u = t;
		T f = std::numeric_limits<T>::max();
		while (~ pre[u]) {
			f = std::min(f, e[pre[u]].f);
			u = e[pre[u] ^ 1].v;
		}
		flow += f;
		cost += f * dis[t];
		u = t;
		while (~ pre[u]) {
			e[pre[u]].f -= f;
			e[pre[u] ^ 1].f += f;
			u = e[pre[u] ^ 1].v;
		}
	}

	std::array<T, 2> solve() {
		flow = 0;
		cost = 0;
		while (spfa()) augment();
		return {flow, cost};
	}

	void init(int _s, int _t, int _vtot) {
		s = _s;
		t = _t;
		vtot = _vtot;
		etot = 0;
		for (int i = 1; i <= vtot; i ++) {
			head[i] = -1;
		}
	}
};

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> v(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> v[i];
	}
	int s = n + 2, t = n + 3;
	MinCostGraph<i64> g;
	g.init(s, t, t);
	
	g.addedge(s, 1, inf, 0);
	g.addedge(n + 1, t, inf, 0);
	for (int i = 1; i <= n; i ++) {
		g.addedge(i, i + 1, inf - v[i], 0);
	}
	for (int i = 0; i < m; i ++) {
		int x, y, z;
		std::cin >> x >> y >> z;
		g.addedge(x, y + 1, inf, z);
	}
	auto it = g.solve();
	std::cout << it[1] << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}