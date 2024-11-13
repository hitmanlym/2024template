#include<bits/stdc++.h>
using i64 = long long;
//Dicnic
//-----------------------------------------
const int V = 500010;
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
    int n, m;
    std::cin >> n >> m;

    FlowGraph<i64> g;
    int s = n + m + 1, t = s + 1;
    g.init(s, t, t);

    std::vector<i64> a(n + 1), b(n + 1);
    bool f = 1;
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i] >> b[i];
    }
    i64 fuck = 0, A_need = b[1];
    std::vector<std::array<int, 3> > e(m + 1);
    for (int i = 1; i <= m; i ++) {
        std::cin >> e[i][0] >> e[i][1] >> e[i][2];
        fuck += e[i][2];
        if (e[i][0] == 1 || e[i][1] == 1) {
            A_need += e[i][2];
        }
    }
    A_need = std::min(A_need, a[1]);
    for (int i = 1; i <= n; i ++) {
        i64 it = std::min(A_need - (i != 1), a[i]) - b[i];
        if (it < 0) {
            f = 0;
        }
        g.addedge(s, i, it);
    }
    for (int i = 1; i <= m; i ++) {
        int u = e[i][0], v = e[i][1], w = e[i][2];
        g.addedge(u, n + i, w);
        g.addedge(v, n + i, w);
        g.addedge(n + i, t, w);
    }
    i64 res = g.dicnic();
    if (! f || res != fuck) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
    }
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