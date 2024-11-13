#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;
const int inf = 1e9 + 7;
const int V = 1010;
const int E = 10100;
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
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= k; i ++) {
        int x;
        std::cin >> x;
        a[x] = i;
    }
    FlowGraph<int> g;
    int s = 2 * n + k, t = s + 1;
    g.init(s, t, t);
    std::vector<int> get(n), lose(k + 1);
    int ans = 0;
    for (int i = 1; i < n; i ++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        if (a[u] && a[v]) {
            ans += 2 * w;
            lose[a[u]] += w;
            lose[a[v]] += w;
            g.addedge(s, k + i, w);
            g.addedge(k + i, a[u], inf);
            g.addedge(k + i, a[v], inf);
        }
    }
    for (int i = 1; i <= k; i ++) {
        g.addedge(i, t, lose[i]);
    }
    for (int i = 1; i < n; i ++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        if (a[u] && a[v]) {
            ans += w;
            g.addedge(s, k + n + i, w);
            g.addedge(k + n + i, a[u], inf);
            g.addedge(k + n + i, a[v], inf);
        }
    }
    // std::cout << ans << ' ';
    // std::cout << g.dicnic() << '\n';
    ans -= g.dicnic();
    std::cout << ans << '\n';
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