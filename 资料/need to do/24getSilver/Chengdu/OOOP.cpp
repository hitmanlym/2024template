#include <algorithm>
#include<bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <queue>
constexpr int INF = 0x3f3f3f3f;
using namespace std;
const int N = 900000;
struct edge {
  int v, f, c, next;
} e[N];

struct node {
  int v, e;
} p[N];

struct mypair {
  int dis, id;

  bool operator<(const mypair& a) const { return dis > a.dis; }

  mypair(int d, int x) { dis = d, id = x; }
};

int head[N], dis[N], vis[N], h[N];
int n, m, s, t, cnt = 1, maxf, minc;

void addedge(int u, int v, int f, int c) {
  e[++cnt].v = v;
  e[cnt].f = f;
  e[cnt].c = c;
  e[cnt].next = head[u];
  head[u] = cnt;
}

bool dijkstra() {
  priority_queue<mypair> q;
  for (int i = 1; i <= n; i++) dis[i] = INF;
  // memset(vis, 0, sizeof(vis));
  dis[s] = 0;
  q.push(mypair(0, s));
  while (!q.empty()) {
    int u = q.top().id;
    q.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next) {
      int v = e[i].v, nc = e[i].c + h[u] - h[v];
      if (e[i].f && dis[v] > dis[u] + nc) {
        dis[v] = dis[u] + nc;
        p[v].v = u;
        p[v].e = i;
        if (!vis[v]) q.push(mypair(dis[v], v));
      }
    }
  }
  return dis[t] != INF;
}

void spfa() {
  queue<int> q;
  memset(h, 63, sizeof(h));
  h[s] = 0, vis[s] = 1;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = 0;
    for (int i = head[u]; i; i = e[i].next) {
      int v = e[i].v;
      if (e[i].f && h[v] > h[u] + e[i].c) {
        h[v] = h[u] + e[i].c;
        if (!vis[v]) {
          vis[v] = 1;
          q.push(v);
        }
      }
    }
  }
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
    addedge(s, i, 1, 0);
    addedge(i, s, 0, 0);
  }
  for (int i = 1; i <= n; i ++) {
    int id = std::lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    addedge(i, n + id, 1, 0);
    addedge(n + id, i, 0, 0);
  }
  for (int i = 1; i <= M; i ++) {
    int o = v[i - 1];
    for (int j = 2; 1ll * j * j <= o; j ++) {
      if (o % j == 0) {
        int id = std::lower_bound(v.begin(), v.end(), v[i - 1] / j) - v.begin() + 1;
        addedge(n + i, n + id, inf, -1);
        addedge(n + id, n + i, 0, 1);
        while (o % j == 0) {
          o /= j;
        }
      }
    }
    if (o != 1) {
      int id = std::lower_bound(v.begin(), v.end(), v[i - 1] / o) - v.begin() + 1;
      addedge(n + i, n + id, inf, -1);
      addedge(n + id, n + i, 0, 1);
    }
  }
  for (int i = 1; i <= M; i ++) {
    addedge(n + i, t, 1, 0);
    addedge(t, n + i, 0, 0);
  }
  spfa();  // 先求出初始势能
  while (dijkstra()) {
    int minf = INF;
    for (int i = 1; i <= n; i++) h[i] += dis[i];
    for (int i = t; i != s; i = p[i].v) minf = min(minf, e[p[i].e].f);
    for (int i = t; i != s; i = p[i].v) {
      e[p[i].e].f -= minf;
      e[p[i].e ^ 1].f += minf;
    }
    maxf += minf;
    minc += minf * h[t];
  }
  // std::cout << it[0] << ' '  << it[1] << '\n';
  std::cout << -minc << '\n';
}

int main() {
  solve();
  return 0;
}