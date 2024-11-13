#include<bits/stdc++.h>
using i64 = long long;
//Dicnic
//-----------------------------------------
const int V = 50010;
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
    std::vector<std::array<int, 4> > e(m + 1);
    std::vector<int> d(n + 1);
    int l = n, r = 0;
    for (int i = 1; i <= m; i ++) {
        std::cin >> e[i][0] >> e[i][1] >> e[i][2] >> e[i][3];
        l = std::min({l, e[i][2], e[i][3]});
        r = std::max({r, e[i][2], e[i][3]});
        d[e[i][0]] ++;
        d[e[i][1]] ++;
    }
    for (int i = 1; i <= n; i ++) {
        if (d[i] & 1) {
            std::cout << "NIE\n";
            return ;
        }
    }
    int ans = -1;
    std::vector<std::vector<std::array<int, 2> > > E(n + 1);
    auto check = [&](int lim) -> bool {
        FlowGraph<int> g;
        int s = n + m + 1, t = s + 1;
        g.init(s, t, t);
        for (int i = 1; i <= m; i ++) {
            g.addedge(s, i, 1);
            if (e[i][2] <= lim) {
                g.addedge(i, m + e[i][0], 1);
            }
            if (e[i][3] <= lim) {
                g.addedge(i, m + e[i][1], 1);
            }
        }
        for (int i = 1; i <= n; i ++) {
            g.addedge(m + i, t, d[i] / 2);
        }
        int res = g.dicnic();
        if (res != m) {
            return false;
        }
        for (int i = 1; i <= n; i ++) {
            E[i].clear();
        }
        for (int u = 1; u <= m; u ++) { // 出边是谁
            for (int i = g.head[u]; ~i; i = g.e[i].nxt) {
                int v = g.e[i].v, f = g.e[i].f;
                if (! f && v != s) {
                    if (v - m == e[u][0]) {
                        E[e[u][0]].push_back({e[u][1], u});
                    } else {
                        E[e[u][1]].push_back({e[u][0], u});
                    }
                }
            }
        }
        return true;
    };  
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if (ans == -1) {
        std::cout << "NIE\n";
        return ;
    }
    check(ans);
    std::cout << ans << '\n';
    std::vector<int> res;
    std::vector<int> cur(n + 1);
    auto dfs = [&](auto self, int u) -> void {
        for (int &i = cur[u]; i < E[u].size(); ) {
            auto op = E[u][i ++];
            self(self, op[0]);
            res.push_back(op[1]);
        }
    };
    dfs(dfs, 1);
    std::reverse(res.begin(), res.end());
    for (auto it : res) {
        std::cout << it << ' ';
    }   
    std::cout << '\n';
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