#include<bits/stdc++.h>
using i64 = long long;
using db = long double;
using pii = std::array<int, 2>;
#define int i64
const int mod = 998244353;
struct SegmentTree {
    int n;
    struct node {
        int l, r, x;
        int sum, add, max, cnt;
    };
    std::vector<node> t;
    std::vector<int> a;
    SegmentTree() {}
    void init(int n) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0, 0});
        a.assign(n + 1, 0);
        build(1, 1, n);
    }
    void pushup(int u) {
        t[u].sum = t[u << 1].sum + t[u << 1 | 1].sum;
        t[u].max = std::min(t[u << 1].max, t[u << 1 | 1].max);
        t[u].cnt = 0;
        if (t[u].max == t[u << 1].max) {
            t[u].cnt += t[u << 1].cnt;
        }
        if (t[u].max == t[u << 1 | 1].max) {
            t[u].cnt += t[u << 1 | 1].cnt;
        }
    }
    node fill(node l, node r) {
        node res = (node){0, 0, 0, 0, 0, 0, 0};
        res.max = std::min(l.max, r.max);
        if (res.max == l.max) {
            res.cnt += l.cnt;
        }
        if (res.max == r.max) {
            res.cnt += r.cnt;
        }
        return res;
    }   
    void pushdown(int u) {
        if (! t[u].add) return ;
        t[u << 1].sum += (t[u << 1].r - t[u << 1].l + 1) * t[u].add;
        t[u << 1 | 1].sum += (t[u << 1 | 1].r - t[u << 1 | 1].l + 1) * t[u].add;
        t[u << 1].add += t[u].add, t[u << 1 | 1].add += t[u].add;
        t[u << 1].max += t[u].add, t[u << 1 | 1].max += t[u].add;
        t[u].add = 0;
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0, 0, 0, 0};
        if (l == r) {
            t[u] = {l, r, a[l], a[l], 0, a[l], 0};
            return ;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void add(int u, int l, int r, int val) {
        if (t[u].l >= l && t[u].r <= r) {
            t[u].sum += (t[u].r - t[u].l + 1) * val;
            t[u].max += val;
            t[u].add += val;
            return ;
        }
        pushdown(u);
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) add(u << 1, l, r, val);
        if (mid < r) add(u << 1 | 1, l, r, val);
        pushup(u);
    }
    void fix(int u, int pos, int val) {
        if (t[u].l == t[u].r && t[u].l == pos) {
            t[u].cnt = (t[u].cnt + val) % mod;
            return ;
        }
        pushdown(u);
        int mid = t[u].l + t[u].r >> 1;
        if (pos <= mid) fix(u << 1, pos, val);
        if (mid < pos) fix(u << 1 | 1, pos, val);
        pushup(u);
    }
    int query(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            return t[u].sum;
        }
        pushdown(u);
        int res = 0;
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) res += query(u << 1, l, r);
        if (mid < r) res += query(u << 1 | 1, l, r);
        return res;
    }
    int query_max(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            return t[u].max;
        }
        pushdown(u);
        int res = -1e9;
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) res = std::max(res, query_max(u << 1, l, r));
        if (mid < r) res = std::max(res, query_max(u << 1 | 1, l, r));
        return res;
    }
    node query_(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            return t[u];
        }
        pushdown(u);
        int mid = t[u].l + t[u].r >> 1;
        node L = (node){0, 0, 0, 0, 0, 0, 0}, R = (node){0, 0, 0, 0, 0, 0, 0};
        if (l <= mid) L = query_(u << 1, l, r);
        if (mid < r) R = query_(u << 1 | 1, l, r);
        node res = fill(L, R);
        return res;
    }
    void add(int l, int r, int val) {
        add(1, l, r, val);
    }
    int query(int l, int r) {
        return query(1, l, r);
    }
    int Max(int l, int r) {
        return query_max(1, l, r);
    }
    node query_(int l, int r) {
        return query_(1, l, r);
    }
    void fix(int pos, int _cnt) {
        fix(1, pos, _cnt);
    }
};
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    std::vector<int> b(m);
    for (int i = 0; i < m; i ++) {
        std::cin >> b[i];
    }
    std::sort(b.begin(), b.end());
    SegmentTree t;
    t.init(n + 2);
    std::vector<std::vector<int> > e(n + 1);
    for (int i = 1; i <= n; i ++) {
        e[i].push_back(0);
    }
    std::vector<int> dp(n + 3);
    
    const int y = 1;
    t.fix(0 + y, 1);

    for (int i = 1; i <= n; i ++) { // 先恢复，后更新
        int v = a[i], siz;
        siz = e[v].size();
        for (auto p : b) {
            if (siz - 1 < p) break;
            int l = e[v][siz - 1 - p], 
                r = e[v][siz - p] - 1;
            t.add(l + y, r + y, -1);
        }
        e[v].push_back(i);
        siz ++;
        for (auto p : b) {
            if (siz - 1 < p) break;
            int l = e[v][siz - 1 - p], 
                r = e[v][siz - p] - 1;
            t.add(l + y, r + y, 1);
        }

        auto it = t.query_(0 + y, i + y);
        if (it.max == 0) {
            dp[i] = (dp[i] + it.cnt) % mod;
        }
        t.fix(i + y, dp[i]);
    }
    std::cout << dp[n] << '\n';
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