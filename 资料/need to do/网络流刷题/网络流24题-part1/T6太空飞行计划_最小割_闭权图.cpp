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
struct Reader {
  	std::string s = "";
  	int p = 0;
  	bool block = false;
  	int in() {
	    if (block) {
	    	block = false;
	    	return -1;
	    }
	    if (p == s.size()) std::getline(std::cin, s), p = 0, s += '\n';
	    int res = -1;
	    bool flg = false;
	    while (p < s.size()) {
	      	if (s[p] >= '0' && s[p] <= '9') {
	        	if (res == -1) res = s[p] - '0';
	        	else res = res * 10 + s[p] - '0';
	        	flg = true;
	      	} else if (flg) {
	        	if (s[p] == '\n') block = true;
	        	p++;
	        	return res;
	      	}
	      	p++;
	    }
	    return res;
  	}
} reader;
void solve() {
	int m, n;
	std::cin >> m >> n;
	int s = m + n + 1, t = m + n + 2;
	FlowGraph<int> g;
	g.init(s, t, t);
	int sum = 0;
	for (int i = 1; i <= m; i ++) {
		int x;
		std::cin >> x;
		sum += x;
		g.addedge(s, i, x);
		int num = reader.in();
		while (num != -1) {
			g.addedge(i, num + m, inf);
			num = reader.in();
		}
	}
	for (int i = 1; i <= n; i ++) {
		int x;
		std::cin >> x;
		g.addedge(i + m, t, x);
	}
	int res = g.dicnic();
	for (int i = 1; i <= m; i ++) {
		if (g.dis[i] != 0) {
			std::cout << i << ' ';
		}
	}
	std::cout << '\n';
	for (int i = 1; i <= n; i ++) {
		if (g.dis[i + m] != 0) {
			std::cout << i << ' ';
		}
	}
	std::cout << '\n';
	std::cout << sum - res << '\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	//freopen("000.txt", "r", stdin);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}