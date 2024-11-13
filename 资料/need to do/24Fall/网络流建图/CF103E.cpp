#include<bits/stdc++.h>
using i64 = long long;

//Dicnic
//-----------------------------------------
const int V = 6010;
const int E = 40000;
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
const i64 inf = 1e16 + 7, lim = 1e18;
//-----------------------------------------
void solve() {
	int n;
	std::cin >> n;
	std::vector<i64> a(n + 1);
	FlowGraph<i64> g;
	std::map<int, int> rev;
	int cnt = n + 1;
	std::vector<std::vector<int> > e(n + 1);
	for (int i = 1; i <= n; i ++) {
		int num;
		std::cin >> num;
		e[i].resize(num);
		for (int j = 0; j < num; j ++) {
			std::cin >> e[i][j];
			if (! rev.count(e[i][j])) {
				rev[e[i][j]] = cnt ++;
			}
		}
	}
	int s = cnt, t = s + 1;
	g.init(s, t, t);
	i64 ans = 0;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		a[i] = -a[i];
		ans += a[i];
		g.addedge(s, i, inf + a[i]);
	}
	for (int i = n + 1; i < cnt; i ++) {
		g.addedge(i, t, inf);
	}
	for (int i = 1; i <= n; i ++) {
		for (auto it : e[i]) {
			g.addedge(i, rev[it], lim);
		}
	}
	ans -= g.dicnic() - inf * n;
	std::cout << -ans << '\n';
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