#include<bits/stdc++.h>
using i64 = long long;
const int V = 100010;
const int E = 1000100;
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
void solve() {
	int n, m, k;
	std::cin >> n >> m >> k;
	std::vector<std::vector<int> > e(n + 1);
	std::vector<std::array<int, 2> > E(m + 1);
	std::vector<int> d(n + 1);
	std::vector<int> ans(m + 1);
	FlowGraph<int> g;
	int s = n + m + 1, t = s + 1;
	g.init(s, t, t);
	for (int i = 1; i <= m; i ++) {
		std::cin >> E[i][0] >> E[i][1];
		e[E[i][0]].push_back(E[i][1]);
		e[E[i][1]].push_back(E[i][0]);
		d[E[i][0]] ++;
		d[E[i][1]] ++;
		g.addedge(E[i][0], n + i, 1);
		g.addedge(E[i][1], n + i, 1);
		g.addedge(n + i, t, 1);
	}
	auto fail = [&]() -> void {
		for (int i = 1; i <= m; i ++) {
			std::cout << 0 << ' ';
		}
		return ;
	};
	int num = 0;
	for (int i = 1; i <= n; i ++) {
		if (d[i] <= k) continue;
		if (d[i] > 2 * k) {
			fail();
			return ;
		}
		int f = (d[i] - k) * 2;
		num += f;
		g.addedge(s, i, f);
	}
	int get = g.dicnic();
	if (get == num) {
		int col = 0;
		for (int i = 1; i <= n; i ++) {
			std::vector<int> node;
			for (int j = g.head[i]; ~j; j = g.e[j].nxt) {
				if (! g.e[j].f && g.e[j].v != s) {
					node.push_back(g.e[j].v - n);
				}
			}
			for (int i = 0; i < node.size(); i += 2) {
				ans[node[i]] = ans[node[i + 1]] = ++ col;
			}
		}
		for (int i = 1; i <= m; i ++) {
			if (! ans[i]) ans[i] = ++ col;
		}
		for (int i = 1; i <= m; i ++) {
			std::cout << ans[i] << ' ';
		}
		std::cout << '\n';
	} else {
		fail();
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}