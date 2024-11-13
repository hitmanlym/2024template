#include<bits/stdc++.h>
using i64 = long long;
//最小费用最大流 - 最大费用最大流
// MCMF ： minimum cost maximum flow

const int V = 2010;
const int E = 10100;
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
};

int q[V][V];
void solve() {
	int m, n;
	std::cin >> m >> n;
	int o = m + n - 1;
	int N = n * o;
	int s = N * 2 + 1, t = s + 1;
	MinCostGraph<int> g, h, k;
	g.init(s, t, t);
	h.init(s, t, t);
	k.init(s, t, t);
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m + i - 1; j ++) {
			std::cin >> q[i][j];
		}
	}
	for (int i = 1; i <= m; i ++) {
		g.addedge(s, i, 1, -q[1][i]);
		h.addedge(s, i, 1, -q[1][i]);
		k.addedge(s, i, 1, -q[1][i]);
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m + i - 1; j ++) {
			int u = (i - 1) * o + j;
			g.addedge(u, u + N, 1, 0);
			h.addedge(u, u + N, inf, 0);
			k.addedge(u, u + N, inf, 0);
			if (i < n) {
				int x = i * o + j, y = i * o + j + 1;
				g.addedge(u + N, x, 1, -q[i + 1][j]);
				g.addedge(u + N, y, 1, -q[i + 1][j + 1]);
				h.addedge(u + N, x, 1, -q[i + 1][j]);
				h.addedge(u + N, y, 1, -q[i + 1][j + 1]);
				k.addedge(u + N, x, inf, -q[i + 1][j]);
				k.addedge(u + N, y, inf, -q[i + 1][j + 1]);
			}
		}
	}
	for (int i = 1; i <= m + n - 1; i ++) {
		g.addedge((n - 1) * o + i + N, t, 1, 0);
		h.addedge((n - 1) * o + i + N, t, inf, 0);
		k.addedge((n - 1) * o + i + N, t, inf, 0);
	}
	auto ans1 = g.solve();
	std::cout << -ans1[1] << '\n';
	auto ans2 = h.solve();
	std::cout << -ans2[1] << '\n';
	auto ans3 = k.solve();
	std::cout << -ans3[1] << '\n';
	//-----------------------------------------------------
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