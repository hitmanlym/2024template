#include<bits/stdc++.h>
using i64 = long long;
// const int V = 50010;
// const int E = 20000010;
// struct FlowGraph {
// 	int s, t, vtot, etot, head[V], dis[V], cur[V];
// 	struct edge {
// 		int v, nxt;
// 		int f;
// 	} e[E * 2];
// 	void addedge(int u, int v, int f) {
// 		e[etot] = {v, head[u], f}; head[u] = etot ++;
// 		e[etot] = {u, head[v], 0}; head[v] = etot ++;
// 	}
// 	bool bfs() {
// 		for (int i = 1; i <= vtot; i ++) {
// 			dis[i] = 0;
// 			cur[i] = head[i];
// 		}
// 		std::queue<int> q;
// 		q.push(s);
// 		dis[s] = 1;
// 		while (! q.empty()) {
// 			int u = q.front(); q.pop();
// 			for (int i = head[u]; ~i; i = e[i].nxt) {
// 				if (e[i].f && ! dis[e[i].v]) {
// 					int v = e[i].v;
// 					dis[v] = dis[u] + 1;
// 					if (v == t) return true;
// 					q.push(v);
// 				}
// 			}
// 		}
// 		return false;
// 	}
// 	int dfs(int u, int m) {
// 		if (u == t) return m;
// 		int flow = 0;
// 		for (int i = cur[u]; ~i; cur[u] = i = e[i].nxt) {
// 			if (e[i].f && dis[e[i].v] == dis[u] + 1) {
// 				int f = dfs(e[i].v, std::min(m, e[i].f));
// 				e[i].f -= f;
// 				e[i ^ 1].f += f;
// 				m -= f;
// 				flow += f;
// 				if (! m) break;
// 			}
// 		}
// 		if (! flow) dis[u] = -1;
// 		return flow;
// 	}
// 	int dicnic() {
// 		int flow = 0;
// 		while (bfs()) {
// 			flow += dfs(s, std::numeric_limits<int>::max());
// 		}
// 		return flow;
// 	}
// 	void init(int _s, int _t, int _vtot) {
// 		s = _s;
// 		t = _t;
// 		vtot = _vtot;
// 		for (int i = 1; i <= vtot; i ++) {
// 			head[i] = -1;
// 		}
// 	}
// };
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::vector<int> > a(n + 1, std::vector<int>(n + 1)),
							b(n + 1, std::vector<int>(n + 1));
	std::vector<int> sumX(n + 1), sumY(n + 1), aimX(n + 1), aimY(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::string s;
		std::cin >> s;
		for (int j = 1; j <= n; j ++) {
			if (s[j - 1] == '+') {
				a[i][j] = 1;
				sumX[i] ++;
				sumY[j] ++;
			} else {
				a[i][j] = 0;
			}
		}
	}
	std::vector<int> opx(n + 1), opy(n + 1);
	std::vector<std::array<int, 2> > io(n + 1);
	bool f = 1;
	for (int i = 1; i <= n; i ++) {
		std::cin >> aimX[i];
		if (aimX[i] > sumX[i]) f = 0;
		opx[i] = sumX[i] - aimX[i];
		io[i] = {opx[i], i};
	}
	std::sort(io.begin() + 1, io.end(), [&](auto x, auto y) {
		return x[0] > y[0];
	});
	std::priority_queue<std::array<int, 2> > q;
	for (int i = 1; i <= n; i ++) {
		std::cin >> aimY[i];
		if (aimY[i] > sumY[i]) f = 0;
		opy[i] = sumY[i] - aimY[i];
		if (opy[i] > 0) {
			q.push({opy[i], i});
		}
	}
	for (int i = 1; i <= n; i ++) {
		int num = io[i][0];
		// std::cout << num << ' ' << q.size() << '\n';
		if (q.size() < num) {
			std::cout << "No\n";
			return ;
		}
		std::vector<std::array<int, 2> > ls;
		while (num --) {
			auto it = q.top();
			q.pop();
			b[io[i][1]][it[1]] = 1;
			// std::cout << i << ' ' << it[1] << ' ' << it[0] << '\n';
			it[0] --;
			if (it[0] > 0) {
				ls.push_back(it);
			}
		}
		for (auto it : ls) {
			q.push(it);
		}
	}
	if (q.size() || ! f) {
		std::cout << "No\n";
		return ;
	}


	// FlowGraph g;
	// int s = n * 2 + 1, t = s + 1;
	// g.init(s, t, t);
	// int opX = 0, opY = 0;
	// std::vector<bool> lx(n + 1), ly(n + 1);
	// for (int i = 1; i <= n; i ++) {
	// 	int num = sumX[i] - aimX[i];
	// 	opX += num;
	// 	if (num > 0) {
	// 		g.addedge(s, i, num);
	// 		lx[i] = 1;
	// 	}
 	// }
 	// for (int i = 1; i <= n; i ++) {
 	// 	int num = sumY[i] - aimY[i];
 	// 	opY += num;
 	// 	if (num > 0) {
 	// 		g.addedge(n + i, t, num);
 	// 		ly[i] = 1;
 	// 	}
 	// }
 	// for (int i = 1; i <= n; i ++) {
 	// 	for (int j = 1; j <= n; j ++) {
 	// 		if (lx[i] && ly[j])
 	// 		g.addedge(i, n + j, 1);
 	// 	}
 	// }
 	// if (opX != opY) {
 	// 	std::cout << "No\n";
 	// 	return ;
 	// }
 	// auto it = g.dicnic();
 	// if (it != opX) {
 	// 	std::cout << "No\n";
 	// 	return ;
 	// }
 	// for (int i = 1; i <= n; i ++) {
 	// 	for (int j = g.head[i]; ~j; j = g.e[j].nxt) {
 	// 		if (g.e[j].v != g.s && ! g.e[j].f) {
 	// 			b[i][g.e[j].v - n] = 1;
 	// 		}
 	// 	}
 	// }
 	std::cout << "Yes\n";
 	for (int i = 1; i <= n; i ++) {
 		for (int j = 1; j <= n; j ++) {
 			std::cout << (a[i][j] ^ b[i][j]);
 		}
 		std::cout << '\n';
 	}
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}