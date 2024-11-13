#include <bits/stdc++.h>
using i64 = long long;
#define int i64
struct SegmentTree {
    int n;
    struct node {
        int l, r, len;
        int sum, add, max; // x = len, sum = times, add = delt
    };
    // 考虑改变线段树存值的方式，因为 a[3] - a[1] -->
    // a[1 -- 2] + a[3 -- 3] 而 3 -- 3 nothing.
    // 
    std::vector<node> t;
    std::vector<int> a;
    SegmentTree() {}
    void init(int n) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0});
        a.assign(n + 1, 0);
        build(1, 1, n);
    }
    void init(int n, std::vector<int> v) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0});
        a.assign(v.begin(), v.end());
        build(1, 1, n);
    }
    void pushup(int u) { // ub大集合!
        if (t[u].sum) {
            t[u].len = a[t[u].r] - a[t[u].l - 1];
        } else {
            if (t[u].l != t[u].r)
                t[u].len = t[u << 1].len + t[u << 1 | 1].len;
            else t[u].len = 0;
        }
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0, 0, 0};
        if (l == r) {
            return ;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }
    void add(int u, int l, int r, int val) {
        if (t[u].l >= l && t[u].r <= r) {
            t[u].sum += val;
            pushup(u);
            return ;
        }
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) add(u << 1, l, r, val);
        if (mid < r) add(u << 1 | 1, l, r, val);
        pushup(u);
    }
    void add(int l, int r, int val) {
        add(1, l, r, val);
    }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // 扫描线. 
    // 点对
    int n;
    std::cin >> n;
    std::vector<int> v(n + 1), pre(n + 1), nxt(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> v[i];
    }
    std::vector<int> pos1(n + 1), pos2(n + 1, n + 1);
    for (int i = 1; i <= n; i ++) {
        pre[i] = pos1[v[i]];
        pos1[v[i]] = i;
    }
    for (int i = n; i >= 1; i --) {
        nxt[i] = pos2[v[i]];
        pos2[v[i]] = i;
    }
    std::vector<std::array<int, 4> > e(n * 2);
    std::vector<int> X;
    for (int i = 1; i <= n; i ++) {
        int x1 = pre[i], y1 = i, x2 = i, y2 = nxt[i];
        X.push_back(x1);
        X.push_back(x2);
        e[i * 2 - 2] = {x1, x2, y1, 1};
        e[i * 2 - 1] = {x1, x2, y2, -1};
    }
    std::sort(X.begin(), X.end());
    X.erase(std::unique(X.begin(), X.end()), X.end());
    int m = X.size();
    std::vector<int> a(m);
    for (int i = 1; i < m; i ++) {
        a[i] = X[i] - X[i - 1];
    }
    m --;
    for (int i = 1; i <= m; i ++) {
        a[i] += a[i - 1];
    }
    std::sort(e.begin(), e.end(), [&](auto a, auto b) {
        return a[2] < b[2];
    });

    SegmentTree t;
    t.init(m, a);
    int ans = 0;
    for (int i = 0; i < 2 * n; i ++) {
        int l = std::lower_bound(X.begin(), X.end(), e[i][0]) - X.begin() + 1;
        int r = std::lower_bound(X.begin(), X.end(), e[i][1]) - X.begin() + 1;
        t.add(l, r - 1, e[i][3]);
        if (i + 1 < 2 * n) ans += t.t[1].len * (e[i + 1][2] - e[i][2]);
    }
    std::cout << ans << '\n';
    return 0;
}