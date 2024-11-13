#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;

#define fi first
#define se second
#define mp make_pair

const int N = 5005, M = 50005;
const int INF = ~0u >> 1;

int n, m, s, t;
int tot = -1, head[N], cur[N];
struct Edge {
    int p, nxt, c, w;
    Edge(int p = 0, int nxt = 0, int c = 0, int w = 0) : p(p), nxt(nxt), c(c), w(w) {}
} edge[M * 2];
inline void Add_Edge(int u, int v, int c, int w) {
    edge[++tot] = Edge(v, head[u], c, w);
    head[u] = tot;
    return;
}

int h[N], d[N];
priority_queue<PII> pq;

bool Dijkstra(int s, int t) {
    fill(d + 1, d + n + 1, INF);
    pq.push(mp(d[s] = 0, s));
    while (!pq.empty()) {
        PII cur = pq.top();
        pq.pop();
        int u = cur.se;
        if (-cur.fi > d[u]) continue;
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].p, c = edge[i].c, w = edge[i].w + h[u] - h[v];
            if (c && d[v] > d[u] + w) pq.push(mp(-(d[v] = d[u] + w), v));
        }
    }
    return d[t] < INF;
}

int v[N];

int DFS(int u, int c, int t) {
    if (u == t) return c;
    int r = c;
    v[u] = 1;
    for (int &i = cur[u]; ~i && r; i = edge[i].nxt) {
        int v = edge[i].p, c = edge[i].c, w = edge[i].w + h[u] - h[v];
        if (!::v[v] && c && d[u] + w == d[v]) {
            int x = DFS(v, min(r, c), t);
            r -= x;
            edge[i].c -= x;
            edge[i ^ 1].c += x;
        }
    }
    v[u] = 0;
    return c - r;
}
const int inf = 1e9;
void solve() {
  // int n;
  std::cin >> n;
  // MinCostGraph<int> g;

  std::vector<int> a(n + 1);
  std::vector<int> v;
  // std::vector<std::vector<int> > e(n + 1);
  for (int i = 1; i <= n; i ++) {
    std::cin >> a[i];
    for (int j = 1; 1ll * j * j <= a[i]; j ++) {
      if (a[i] % j == 0) {
        // e[i].push_back(j);
        v.push_back(j);
        if (j * j == a[i]) break;
        // e[i].push_back(a[i] / j);
        v.push_back(a[i] / j);
      }
    }
  }
  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());
  int M = v.size();

  s = n + M + 1, t = s + 1;

  // g.init(s, t, t);
  for (int i = 1; i <= n; i ++) {
    Add_Edge(s, i, 1, 0);
    Add_Edge(i, s, 0, 0);
  }
  for (int i = 1; i <= n; i ++) {
    int id = std::lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    Add_Edge(i, n + id, 1, 0);
    Add_Edge(n + id, i, 0, 0);
  }
  for (int i = 1; i <= M; i ++) {
    int o = v[i - 1];
    for (int j = 2; 1ll * j * j <= o; j ++) {
      if (o % j == 0) {
        int id = std::lower_bound(v.begin(), v.end(), v[i - 1] / j) - v.begin() + 1;
        Add_Edge(n + i, n + id, inf, -1);
        Add_Edge(n + id, n + i, 0, 1);
        while (o % j == 0) {
          o /= j;
        }
      }
    }
    if (o != 1) {
      int id = std::lower_bound(v.begin(), v.end(), v[i - 1] / o) - v.begin() + 1;
      Add_Edge(n + i, n + id, inf, -1);
      Add_Edge(n + id, n + i, 0, 1);
    }
  }
  for (int i = 1; i <= M; i ++) {
    Add_Edge(n + i, t, 1, 0);
    Add_Edge(t, n + i, 0, 0);
  }
  int mf = 0, mc = 0;
    while (Dijkstra(s, t)) {
        memcpy(cur, head, sizeof(cur));
        int c = DFS(s, INF, t);
        for (int i = 1; i <= n; ++i)
            if (d[i] < INF) h[i] += d[i];
        mf += c;
        mc += c * h[t];
    }
  // std::cout << it[0] << ' '  << it[1] << '\n';
  std::cout << -mc << '\n';
}

int main() {
    memset(head, -1, sizeof(head));
    solve();
    return 0;
}
