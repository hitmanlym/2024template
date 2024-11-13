#include<bits/stdc++.h>
using i64 = long long;
#define int i64
//Dicnic
//-----------------------------------------
const int inf = 1e9 + 7;
const int V = 1010; // 100010
const int E = 10010; // 500010
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
    FlowGraph<int> g;
    int N = n * k;
    int s = N * 2 + 1, t = s + 1;
    g.init(s, t, t);
    std::vector<std::array<int, 2> > e(m);
    std::vector<int> in(n + 1), out(n + 1);
    for (int i = 0; i < m; i ++) {
        std::cin >> e[i][0] >> e[i][1];
        in[e[i][1]] ++;
        out[e[i][0]] ++;
    }
    for (int i = 1; i <= n; i ++) { // 2, 3, ..., k 这 k - 1 的通路被切
        for (int j = 1; j <= k; j ++) {
            if (! in[i]) {
                g.addedge(s, N + (j - 1) * n + i, inf);
            }
            else if (! out[i]) {
                g.addedge((j - 1) * n + i, t, inf);
            }
            else {
                g.addedge((j - 1) * n + i, N + (j - 1) * n + i, 1);
                if (j + 1 <= k) {
                    g.addedge((j - 1) * n + i, N + j * n + i, inf);
                }
            }
        }
    }
    for (int i = 0; i < m; i ++) {
        int u = e[i][0], v = e[i][1];
        for (int j = 1; j <= k; j ++) {
            int U = N + n * (j - 1) + u, V = n * (j - 1) + v;
            g.addedge(U, V, inf);
        }
    }
    auto f = g.dicnic();
    if (f > m) {
        std::cout << -1 << '\n';
        return ;
    }
    std::vector<int> is(n + 1), ans;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= k; j ++) {
            int u = (j - 1) * n + i, v = N + u;
            /*for (int y = g.head[u]; ~y; y = g.e[y].nxt) { // 
                if (g.e[y].v == v && ! g.e[y].f) {
                    std::cout << i << '\n';
                }
            }*/
            if (g.dis[u] && ! g.dis[v]) {
                is[i] = 1;
            }
        }
    }
    for (int i = 1; i <= n; i ++) {
        if (is[i]) {
            ans.push_back(i);
        }
    }
    std::cout << ans.size() << '\n';
    for (auto it : ans) {
        std::cout << it << ' ';
    }
    std::cout << '\n';
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}