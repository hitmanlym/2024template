#include <bits/stdc++.h>
using i64 = long long;
#define int i64
struct SegmentTree {
    int n;
    struct node {
        int l, r, x;
        int sum, add, max;
    };
    std::vector<node> t;
    std::vector<int> a;
    SegmentTree() {}
    void init(int n) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, -1, 0});
        a.assign(n + 1, 0);
        build(1, 1, n);
    }
    void init(int n, std::vector<int> v) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, -1, 0});
        a.assign(v.begin(), v.end());
        build(1, 1, n);
    }
    void pushup(int u) {
        t[u].sum = t[u << 1].sum + t[u << 1 | 1].sum;
        t[u].max = std::max(t[u << 1].max, t[u << 1 | 1].max);
    }
    void pushdown(int u) {
        if (t[u].add == -1) return ;
        t[u << 1].sum = (t[u << 1].r - t[u << 1].l + 1) * t[u].add;
        t[u << 1 | 1].sum = (t[u << 1 | 1].r - t[u << 1 | 1].l + 1) * t[u].add;
        t[u << 1].add = t[u].add, t[u << 1 | 1].add = t[u].add;
        t[u << 1].max = t[u].add, t[u << 1 | 1].max = t[u].add;
        t[u].add = -1;
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0, -1, 0};
        if (l == r) {
            t[u] = {l, r, a[l], a[l], -1, a[l]};
            return ;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void add(int u, int l, int r, int val) {
        if (t[u].l >= l && t[u].r <= r) {
            t[u].sum = (t[u].r - t[u].l + 1) * val;
            t[u].max = val;
            t[u].add = val;
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
    void add(int l, int r, int val) {
        add(1, l, r, val);
    }
    int query(int l, int r) {
        return query(1, l, r);
    }
    int Max(int l, int r) {
        return query_max(1, l, r);
    }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    std::vector<int> premax(n + 1), premin(n + 1);

    std::vector<int> st;
    for (int i = 1; i <= n; i ++) {
        while (st.size() && a[st.back()] < a[i]) {
            st.pop_back();
        }
        int u = 0;
        if (st.size()) u = st.back();
        premax[i] = u;
        st.push_back(i);
    }
    st.clear();

    for (int i = 1; i <= n; i ++) {
        while (st.size() && a[st.back()] > a[i]) {
            st.pop_back();
        }
        int u = 0;
        if (st.size()) u = st.back();
        premin[i] = u;
        st.push_back(i);
    }
    SegmentTree t;
    t.init(n);
    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        if (premax[i] < i - 1) {
            t.add(premax[i] + 1, i - 1, 1);
        } else if (premin[i] < i - 1) {
            t.add(premin[i] + 1, i - 1, 0);
        }
        ans += t.query(1, n);
    }
    std::cout << ans << '\n';
    return 0;
}