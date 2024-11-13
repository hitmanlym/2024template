#include <bits/stdc++.h>
using i64 = long long;
#define int i64
struct SegmentTree {
    int n;
    struct node {
        int l, r, x;
        int sum, add, max, tag;
    };
    std::vector<node> t;
    std::vector<int> a;
    SegmentTree() {}
    void init(int n) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0, -1});
        a.assign(n + 1, 0);
        build(1, 1, n);
    }
    void init(int n, std::vector<int> v) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0, -1});
        a.assign(v.begin(), v.end());
        build(1, 1, n);
    }
    void pushup(int u) {
        t[u].sum = t[u << 1].sum + t[u << 1 | 1].sum;
        t[u].max = std::max(t[u << 1].max, t[u << 1 | 1].max);
    }
    void pushdown(int u) {
        if (t[u].tag != -1) {
            t[u << 1].sum = (t[u << 1].r - t[u << 1].l + 1) * t[u].tag;
            t[u << 1 | 1].sum = (t[u << 1 | 1].r - t[u << 1 | 1].l + 1) * t[u].tag;
            t[u << 1].add = 0, t[u << 1 | 1].add = 0;
            t[u << 1].max = t[u].tag, t[u << 1 | 1].max = t[u].tag;
            t[u << 1].tag = t[u].tag, t[u << 1 | 1].tag = t[u].tag;
            t[u].tag = -1;
        }
        if (! t[u].add) return ;
        t[u << 1].sum += (t[u << 1].r - t[u << 1].l + 1) * t[u].add;
        t[u << 1 | 1].sum += (t[u << 1 | 1].r - t[u << 1 | 1].l + 1) * t[u].add;
        t[u << 1].add += t[u].add, t[u << 1 | 1].add += t[u].add;
        t[u << 1].max += t[u].add, t[u << 1 | 1].max += t[u].add;
        t[u].add = 0;
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0, 0, 0, -1};
        if (l == r) {
            t[u] = {l, r, a[l], a[l], 0, a[l], -1};
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
    void fix(int u, int l, int r, int val) {
        if (t[u].l >= l && t[u].r <= r) {
            t[u].sum = (t[u].r - t[u].l + 1) * val;
            t[u].max = val;
            t[u].add = 0;
            t[u].tag = val;
            return ;
        }
        pushdown(u);
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) fix(u << 1, l, r, val);
        if (mid < r) fix(u << 1 | 1, l, r, val);
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
    void add(int l, int r, int val) {
        add(1, l, r, val);
    }
    void fix(int l, int r, int val) {
        fix(1, l, r, val);
    }
    int query(int l, int r) {
        return query(1, l, r);
    }
    int Max(int l, int r) {
        return query_max(1, l, r);
    }
};
const int inf = 1e9;
void solve() {
    int n, m, k;
    std::cin >> n >> k >> m;

    std::multiset<int> val;
    std::map<int, int> cnt;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
        a[i] = a[i] - i;
        val.insert(0);
    }
    for (int i = 1; i <= k; i ++) {
        val.erase(val.find(cnt[a[i]]));
        cnt[a[i]] ++;
        val.insert(cnt[a[i]]);
    }
    std::vector<int> c(n + 1, inf);
    for (int i = 1; i <= n - k + 1; i ++) {
        c[i] = k - *val.rbegin();
        val.erase(val.find(cnt[a[i]]));
        cnt[a[i]] --;
        val.insert(cnt[a[i]]);
        if (i + k <= n) {
            val.erase(val.find(cnt[a[i + k]]));
            cnt[a[i + k]] ++;
            val.insert(cnt[a[i + k]]);
        }
    }
    std::vector<std::array<int, 3> > q(m);
    std::vector<int> ans(m);
    for (int i = 0; i < m; i ++) {
        std::cin >> q[i][0] >> q[i][1];
        q[i][2] = i;
    } 
    std::sort(q.begin(), q.end(), [&](auto x, auto y) {
        return x[0] > y[0];
    });
    int u = 0;
    // <--- 单调栈
    std::vector<std::array<int, 2> > st;
    st.push_back({-1, n + 1});
    SegmentTree t;
    t.init(n);
    for (int i = n; i >= 1; i --) {
        while (st.size() && c[i] <= st.back()[0]) {
            st.pop_back();
        }
        // 区间覆盖.
        t.fix(i, st.back()[1] - 1, c[i]);
        st.push_back({c[i], i});
        while (u < m && q[u][0] == i) {
            int len = q[u][1] - q[u][0] + 1 - k + 1;
            ans[q[u][2]] = t.query(i, i + len - 1);
            u ++;
        }
    }

    for (auto it : ans) {
        std::cout << it << '\n';
    }
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