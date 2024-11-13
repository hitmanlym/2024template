#include<bits/stdc++.h>
using i64 = long long;

//Dicnic
//-----------------------------------------
const int V = 5010;
const int E = 50100;
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
	int n;
	std::cin >> n;
	std::vector<int> v(n + 1), dp(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> v[i];
		dp[i] = 1;
		for (int j = 1; j < i; j ++) {
			if (v[i] >= v[j]) {
				dp[i] = std::max(dp[i], dp[j] + 1);
			}
		}
	}
	if (n == 1) {
		std::cout << "1\n1\n1\n";
		return ;
	}
	int max = 0;
	for (int i = 1; i <=  n; i ++) {
		max = std::max(max, dp[i]);
	}
	std::cout << max << '\n';

	int s = n * 2 + 1, t = s + 1;
	FlowGraph<int> g;
	g.init(s, t, t);
	for (int i = 1; i <= n; i ++) {
		g.addedge(i, n + i, 1);
		if (dp[i] == 1) {
			g.addedge(s, i, 1);
		}
		if (dp[i] == max) {
			g.addedge(n + i, t, 1);
		}
		for (int j = i + 1; j <= n; j ++) {
			if (dp[j] == dp[i] + 1 && v[j] >= v[i]) {
				g.addedge(n + i, j, 1);
			}
		}
	}
	int ans = g.dicnic();
	std::cout << ans << '\n';
	
	g.addedge(s, 1, inf);
	g.addedge(1, 1 + n, inf);
	g.addedge(n, n + n, inf);
	if (dp[n] == max) {
		g.addedge(n + n, t, inf);
	}

	int res = g.dicnic();
	std::cout << ans + res << '\n';
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