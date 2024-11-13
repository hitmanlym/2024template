#include<iostream>
#include<array>
#include<vector>
#include<set>
#include<deque>
using i64 = long long;
const int inf = 1e9;
const int N = 1e5 + 10;
int f[N + 1], g[N + 1], tocir[N + 1], inner[N + 1], ans[N + 1], othertoleaf[N + 1];
int dfn[N + 1], onloop[N + 1], loop[N * 2 + 1], fa[N + 1];
std::vector<std::vector<int> > e(N + 1);
int timer, cnt;
int n;
void dfs(int u, int p) {
    dfn[u] = ++ timer;
    for (auto v : e[u]) {
        if (v == p) continue;
        if (dfn[v]) {
            if (dfn[v] < dfn[u]) continue;
            loop[++ cnt] = v;
            onloop[v] = 1;
            while (v != u) {
                loop[++ cnt] = fa[v];
                onloop[fa[v]] = 1;
                v = fa[v];
            }
        } else {
            fa[v] = u;
            dfs(v, u);
        }
    }
}
void getsubTree(int u, int p, int deep) {
    for (auto v : e[u]) {
        if (v == p || onloop[v]) continue;
        getsubTree(v, u, deep + 1);
        if (f[v] + 1 > f[u]) {
            g[u] = f[u];
            f[u] = f[v] + 1;
        } else if (f[v] + 1 > g[u]) {
            g[u] = f[v] + 1;
        }
    }
    tocir[u] = deep + f[u];
    inner[u] = f[u] + g[u];
}
void solsubTree(int u, int p, int val) {
    ans[u] = std::max(inner[u], tocir[u] + val);
    for (auto v : e[u]) {
        if (v == p || onloop[v]) continue;
        solsubTree(v, u, val);
    }
}
void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; i ++) {
        ans[i] = 0;
        f[i] = 0;
        g[i] = 0;
        e[i].clear();
        onloop[i] = 0;
        othertoleaf[i] = 0;
        dfn[i] = 0;
    }
    timer = 0;
    cnt = 0;
    for (int i = 1; i <= n; i ++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= cnt; i ++) { 
        getsubTree(loop[i], 0, 0);
        loop[i + cnt] =  loop[i];
    }
    // 做两遍罢了, 处理绝对值
    std::deque<std::array<int, 2> > q1;
    for (int i = 1; i <= cnt * 2; i ++) {
        while (q1.size() && q1.back()[0] <= i - cnt) {
            q1.pop_back();
        }
        if (q1.size()) {
            int op = i > cnt ? i - cnt : i;
            othertoleaf[op] = std::max(othertoleaf[op], q1.back()[1] + i);
        }
        while (q1.size() && q1.front()[1] <= f[loop[i]] - i) {
            q1.pop_front();
        }
        q1.push_front({i, f[loop[i]] - i});
    }
    std::deque<std::array<int, 2> > q2;
    for (int i = cnt * 2; i >= 1; i --) {
        while (q2.size() && q2.back()[0] >= i + cnt) {
            q2.pop_back();
        }
        if (q2.size()) {
            int op = i > cnt ? i - cnt : i;
            othertoleaf[op] = std::max(othertoleaf[op], q2.back()[1] - i);
        }
        while (q2.size() && q2.front()[1] <= f[loop[i]] + i) {
            q2.pop_front();
        }
        q2.push_front({i, f[loop[i]] + i});
    }
    for (int i = 1; i <= cnt; i ++) {
        solsubTree(loop[i], 0, othertoleaf[i]);
    }

    std::vector<int> pre(n + 1, -inf), suf(n + 2, -inf);
    for (int i = 1; i <= cnt; i ++) {
        pre[i] = std::max(pre[i - 1], f[loop[i]] - i);
    }
    for (int i = cnt; i >= 1; i --) {
        suf[i] = std::max(suf[i + 1], f[loop[i]] + i);
    }
    for (int i = 1; i <= cnt; i ++) {
        ans[loop[i]] = std::max(ans[loop[i]], pre[i] + suf[i + 1]);
        ans[loop[i]] = std::max(ans[loop[i]], pre[i - 1] + suf[i]);
    }
    int maxi = -inf, maxj = -inf;
    for (int i = 1; i <= cnt; i ++) {
        maxj = std::max(maxj, maxi + f[loop[i]] + cnt - i);
        maxi = std::max(maxi, f[loop[i]] + i);
        ans[loop[i]] = std::max(ans[loop[i]], maxj);
    }
    maxi = -inf, maxj = -inf;
    for (int i = cnt; i >= 1; i --) {
        maxj = std::max(maxj, maxi + f[loop[i]] + i);
        maxi = std::max(maxi, f[loop[i]] + cnt - i);
        ans[loop[i]] = std::max(ans[loop[i]], maxj);
    }
    for (int i = 1; i <= n; i ++) {
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';
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