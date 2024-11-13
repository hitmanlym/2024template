#include<bits/stdc++.h>
using i64 = long long;
//最小费用最大流 - 最大费用最大流
// MCMF ： minimum cost maximum flow
#define int i64
const int V = 5010;
const int E = 50100;
const int inf = 1e9 + 7;
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

	void print(int id, int u, int m) {
		if (u == m + m) {
			return ;
		}
		for (int i = head[u]; ~i; i = e[i].nxt) {
			int v = e[i].v;
			if (v >= 1 && v <= m && e[i ^ 1].f) {
				e[i ^ 1].f -= 1;
				//std::cout << m <<  ' ' << '*' << u << ' ' << v << '\n';
				if (v == u - m + 1) {
					std::cout << id << ' ' << 1 << '\n';
				} else {
					std::cout << id << ' ' << 0 << '\n';
				}
				print(id, v + m, m);
				break ;
			}
		}
	}
};

void solve() {
	int n;
	std::cin >> n;
	int p, q;
	std::cin >> p >> q;
	int m = p * q;
	int s = m * 2 + 1, t = s + 1;
	MinCostGraph<int> g;
	g.init(s, t, t);
	for (int i = 1; i <= q; i ++) {
		for (int j = 1; j <= p; j ++) {
			int x, u = (i - 1) * p + j;
			std::cin >> x;
			if (u == 1) {
				if (x != 1) {
					g.addedge(s, 1, n, 0);
				}
			}
			if (u == m) {
				if (x != 1) {
					g.addedge(m + m, t, n, 0);
				}
			}

			g.addedge(u, u + m, inf, 0);
			
			if (x != 1) {
				if (j > 1) {
					g.addedge((i - 1) * p + j - 1 + m, u, inf, 0);
				}
				if (i > 1) {
					g.addedge((i - 2) * p + j + m, u, inf, 0);
				}
			}
			if (x == 2) {
				g.addedge(u, u + m, 1, -1);
			}
		}
	}
	auto it = g.solve();
	for (int i = 1; i <= it[0]; i ++) {
		g.print(i, 1 + m, m);
	}
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