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
struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n + 1);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};

//-----------------------------------------
void solve() {
	int n, m, k;
	std::cin >> n >> m >> k;
	n += 2;
	DSU T(n);
	int sum = 0;
	std::vector<int> w(m + 1);
	std::vector<std::vector<int> > station(m + 1);
	for (int i = 1; i <= m; i ++) {
		std::cin >> w[i];
		int x;
		std::cin >> x;
		station[i].resize(x + 1);
		station[i][0] = x;
		for (int j = 1; j <= x; j ++) {
			std::cin >> station[i][j];
			station[i][j] += 2;
			if (j > 1) {
				int u = station[i][j - 1], v = station[i][j];
				if (! T.same(u, v)) {
					T.merge(u, v);
				}
			}
			// earth - 2
			// moon  - 1
		}
	}
	if (! T.same(1, 2)) {
		std::cout << 0 << '\n';
		return ;
	}
	int time = 0;

	int s = V - 2, t = V - 1;
	FlowGraph<int> g;
	g.init(s, t, t);
	while (true) {
		g.addedge(s, time * n + 2, inf);
		g.addedge(time * n + 1, t, inf);

		if (time) {
			for (int i = 1; i <= n; i ++) {
				g.addedge((time - 1) * n + i, time * n + i, inf);
			}
			for (int i = 1; i <= m; i ++) {
				int u = station[i][(time - 1) % station[i][0] + 1], 
					v = station[i][(time) % station[i][0] + 1];
				g.addedge((time - 1) * n + u, time * n + v, w[i]);
			}
		}
		sum += g.dicnic();
		if (sum >= k) {
			std::cout << time << '\n';
			return ;
		}
		time ++;
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