#include<bits/stdc++.h>
using i64 = long long;
//最小费用最大流 - 最大费用最大流
// MCMF ： minimum cost maximum flow


int n, nm;
const int V = 2010;
const int E = 20100;
bool op[V];
int vw[V][V];
int from[V], multi[V];
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
		while (spfa()) {
			augment();
			for (int i = head[t]; ~i; i = e[i].nxt) {
				int v = e[i].v, w = e[i].f;
				if (w && ! op[v]) {
					op[v] = 1;
					int helper = from[v];
					multi[helper] ++;
					addedge(++ nm, t, 1, 0);

					from[nm] = helper;

					for (int j = 1; j <= n; j ++) {
						addedge(j, nm, 1, multi[helper] * vw[j][helper]);
					}
				}
			}
		}
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
	int m;
	std::cin >> n >> m;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			std::cin >> vw[i][j];
		}
	}
	nm = n + 1;
	int s = nm, t = V - 1;
	MinCostGraph<int> g;
	g.init(s, t, t);
	for (int i = 1; i <= n; i ++) {
		g.addedge(s, i, a[i], 0);
	}
	for (int j = 1; j <= m; j ++) {
		g.addedge(++ nm, t, 1, 0);
		from[nm] = j;
		multi[j] = 1;
		for (int i = 1; i <= n; i ++) {
			g.addedge(i, nm, 1, vw[i][j]);
		}
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