#include<bits/stdc++.h>
using i64 = long long;
using db = long double;
using pii = std::array<int, 2>;
#define int i64
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
        t[u].max = std::max(t[u << 1].max, t[u << 1 | 1].max);
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
        res.max = std::max(l.max, r.max);
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
        t[u] = {l, r, 0, 0, 0, 0, 1};
        if (l == r) {
            t[u] = {l, r, a[l], a[l], 0, a[l], 1};
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
};
void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n + 1);
    std::vector<int> v;
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
        v.push_back(a[i]);
    }
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(),v.end()), v.end());
    std::vector<std::vector<int> > e(v.size() + 1);
    std::vector<int> now(n + 1);
    for (int i = 1; i <= v.size(); i ++) {
        e[i].push_back(0);
    }
    for (int i = 1; i <= n; i ++) {
        int it = std::lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        now[i] = e[it].size();
        e[it].push_back(i);
    }
    SegmentTree t;
    t.init(n + 2);
    i64 ans = 0;
    for (int i = 1; i <= n; i ++) {
        t.add(i, i, n);
        int it = std::lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        int pos = now[i];
        if (pos > 0) {
            t.add(e[it][pos - 1] + 1, i, -1);
        }
        //
        if (pos - k >= 0) {
            t.add(e[it][pos - k] + 1, e[it][pos - k + 1], 1);
        }
        if (pos - (k + 1) >= 0) {
            t.add(e[it][pos - (k + 1)] + 1, e[it][pos - k], -1);
        }
        auto io = t.query_(1, i);
        if (io.max == n) {
            ans += io.cnt;
        }
    }
    std::cout << ans << '\n';
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}