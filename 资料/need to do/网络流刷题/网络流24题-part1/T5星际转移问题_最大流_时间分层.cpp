#include<bits/stdc++.h>
using i64 = long long;

//Dicnic
//-----------------------------------------
const int V = 50010;
const int E = 5000100;
const int inf = 1e9 + 7;
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
	int n, m, k;
	std::cin >> n >> m >> k;
	n += 2;
	std::vector<int> p(n + 1);
	for (int i = 1; i <= n; i ++) {
		p[i] = i;
	}
	auto find = [&](auto self, int x) -> int {
		return p[x] == x ? x : p[x] = self(self, p[x]);
	};
	std::vector<int> turn(m), w(m);
	std::vector<std::vector<int> > ship(m);
	for (int i = 0; i < m; i ++) {
		std::cin >> w[i] >> turn[i];
		ship[i].resize(turn[i] + 1);
		for (int j = 1; j <= turn[i]; j ++) {
			std::cin >> ship[i][j];
			ship[i][j] += 2;
			if (j != 1) {
				int x = find(find, ship[i][j - 1]), y = find(find, ship[i][j]);
				if (x != y) {
					p[x] = y;
				}
			}
		}
	}
	if (find(find, 1) != find(find, 2)) {
		std::cout << 0 << '\n';
		return ;
	}
	int sum = 0, now = 0;
	int s = V - 2, t = V - 1;
	FlowGraph<int> g;
	g.init(s, t, V - 1);
	int time = 0;
	while (sum < k) {
		time ++;
		g.addedge(s, now * n + 2, inf);
		g.addedge(now * n + 1, t, inf);
		if (now) {
			for (int i = 1; i <= n; i ++) { // planet
				g.addedge((now - 1) * n + i, now * n + i, inf);
			}
			for (int i = 0; i < m; i ++) {
				int x = ship[i][(now - 1) % turn[i] + 1];
				int y = ship[i][now % turn[i] + 1];
				g.addedge((now - 1) * n + x, now * n + y, w[i]);
			}
		}
		sum += g.dicnic();
		if (sum >= k) {
			std::cout << now << '\n';
			return ;
		}
		now ++;
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