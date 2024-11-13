#include<bits/stdc++.h>
using i64 = long long;
//最小费用最大流 - 最大费用最大流
// MCMF ： minimum cost maximum flow

const int V = 20010;
const int E = 200100;
const int inf = 1e9 + 7;

std::map<std::string, int> mp;
std::map<int, std::string> inv;

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
	bool o[V];
	void print1(int x) {
		int n = (s - 1) / 2;
		std::cout << inv[x - n] << '\n';
		o[x - n] = 1;
		
		for (int i = head[x]; ~i; i = e[i].nxt) {
			int v = e[i].v, w = e[i].f;
			if (v <= n && w == 0 && ! o[v]) {
				print1(v + n);
				break;
			}
		}
	}

	void print2(int x) {
		int n = (s - 1) / 2;
		o[x - n] = 1;
		
		for (int i = head[x]; ~i; i = e[i].nxt) {
			int v = e[i].v, w = e[i].f;
			if (v <= n && w == 0 && ! o[v]) {
				print2(v + n);
			}
		}
		std::cout << inv[x - n] << '\n';
	}
};

void solve() {
	std::string a, b;
	int n, m;
	std::cin >> n >> m;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a;
		mp[a] = i;
		inv[i] = a;
	}
	int s = n * 2 + 1, t = s + 1;
	MinCostGraph<int> g;
	g.init(s, t, t);

	g.addedge(s, 1, 2, 0);
	g.addedge(n + n, t, 2, 0);
	g.addedge(1, 1 + n, 2, 0);
	g.addedge(n, n + n, 2, 0);
	for (int i = 2; i < n; i ++) {
		g.addedge(i, i + n, 1, 0);
	}

	bool check = 0;
	for (int i = 1; i <= m; i ++) {
		std::cin >> a >> b;
		int u = mp[a], v = mp[b];
		if (u > v) {
			std::swap(u, v);
		}
		if (u == 1 && v == n) {
			check = 1;
		}
		g.addedge(u + n, v, 1, -1);
	}
	auto it = g.solve();
	if (it[0] == 1 && check) {
		std::cout << 2 << "\n" << inv[1] << "\n" << inv[n] << '\n' << inv[1] << '\n';
		return ;
	}
	if (it[0] != 2) {
		std::cout << "No Solution!\n";
		return ;
	}
	std::cout << -it[1] << '\n';

	g.print1(1 + n);
	g.print2(1 + n);
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