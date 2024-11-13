#include <bits/stdc++.h>
using i64 = long long;
#define int i64
struct SegmentTreeBeat {
    int n;
    struct node {
        int l, r;
        int sum;
        int maxa, maxb, se, cnt;
        int add1, add2, add3, add4;
    };
    std::vector<node> t;
    std::vector<int> a;
    SegmentTreeBeat() {}
    void init(int n) {
        this -> n = n;
        t.resize(4 * n + 1);
        a.assign(n + 1, 0);
        build(1, 1, n);
    }
    void init(int n, std::vector<int> v) {
        this -> n = n;
        t.resize(4 * n + 1);
        a.assign(v.begin(), v.end());
        build(1, 1, n);
    }
    void pushup(int p) {
        t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
        t[p].maxa = std::max(t[p << 1].maxa, t[p << 1 | 1].maxa);
        t[p].maxb = std::max(t[p << 1].maxb, t[p << 1 | 1].maxb);

        if (t[p << 1].maxa == t[p << 1 | 1].maxa) {
            t[p].se = std::max(t[p << 1].se, t[p << 1 | 1].se);
            t[p].cnt = t[p << 1].cnt + t[p << 1 | 1].cnt;
        } else if (t[p << 1].maxa > t[p << 1 | 1].maxa) {
            t[p].se = std::max(t[p << 1].se, t[p << 1 | 1].maxa);
            t[p].cnt = t[p << 1].cnt;
        } else {
            t[p].se = std::max(t[p << 1].maxa, t[p << 1 | 1].se);
            t[p].cnt = t[p << 1 | 1].cnt;
        }
    }
    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r;
        if (l == r) {
            t[p].sum = t[p].maxa = t[p].maxb = a[l];
            t[p].cnt = 1;
            t[p].se = -2e9;
            return ;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void change(int p, int k1, int k2, int k3, int k4) {
        t[p].sum += k1 * t[p].cnt + k2 * (t[p].r - t[p].l + 1 - t[p].cnt);
        t[p].maxb = std::max(t[p].maxb, t[p].maxa + k3);
        t[p].maxa += k1;

        if (t[p].se != -2e9) {
            t[p].se += k2;
        }

        t[p].add3 = std::max(t[p].add3, t[p].add1 + k3);
        t[p].add4 = std::max(t[p].add4, t[p].add2 + k4);
        t[p].add1 += k1, t[p].add2 += k2;
    }
    void pushdown(int p) {
        if (t[p].add1 == 0 && t[p].add2 == 0 && t[p].add3 == 0 && t[p].add4 == 0) {
            return ;
        }
        int maxn = std::max(t[p << 1].maxa, t[p << 1 | 1].maxa);
        if (t[p << 1].maxa == maxn) {
            change(p << 1, t[p].add1, t[p].add2, t[p].add3, t[p].add4);
        } else {
            change(p << 1, t[p].add2, t[p].add2, t[p].add4, t[p].add4);
        }

        if (t[p << 1 | 1].maxa == maxn) {
            change(p << 1 | 1, t[p].add1, t[p].add2, t[p].add3, t[p].add4);
        } else {
            change(p << 1 | 1, t[p].add2, t[p].add2, t[p].add4, t[p].add4);
        }
        t[p].add1 = t[p].add2 = t[p].add3 = t[p].add4 = 0;
    }
    void update_add(int p, int l, int r, int k) {
        if (l <= t[p].l && r >= t[p].r) {
            t[p].sum += (t[p].r - t[p].l + 1) * k;
            t[p].maxa += k;
            t[p].maxb = std::max(t[p].maxb, t[p].maxa);
            if (t[p].se != -2e9) t[p].se += k;
            t[p].add1 += k;
            t[p].add2 += k;
            t[p].add3 = std::max(t[p].add3, t[p].add1);
            t[p].add4 = std::max(t[p].add4, t[p].add2);
            return ;
        }
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if (l <= mid) update_add(p << 1, l, r, k);
        if (mid < r) update_add(p << 1 | 1, l, r, k);
        pushup(p);
    }
    void update_min(int p, int l, int r, int v) {
        if (v >= t[p].maxa) return;
        if (l <= t[p].l && r >= t[p].r && t[p].se < v) {
            int k = t[p].maxa - v;
            t[p].sum -= t[p].cnt * k;
            t[p].maxa = v;
            t[p].add1 -= k;
            return ;
        }
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if (l <= mid) update_min(p << 1, l, r, v);
        if (mid < r) update_min(p << 1 | 1, l, r, v);
        pushup(p);
    }

    int query_sum(int p, int l, int r) {
        if (l <= t[p].l && r >= t[p].r) {
            return t[p].sum;
        }
        int res = 0;
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if (l <= mid) res += query_sum(p << 1, l, r);
        if (mid < r) res += query_sum(p << 1 | 1, l, r);
        return res;
    }
    int query_maxa(int p, int l, int r) {
        if (l <= t[p].l && r >= t[p].r) {
            return t[p].maxa;
        }
        int res = -2e9;
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if (l <= mid) res = std::max(res, query_maxa(p << 1, l, r));
        if (mid < r) res = std::max(res, query_maxa(p << 1 | 1, l, r));
        return res;
    }
    int query_maxb(int p, int l, int r) {
        if (l <= t[p].l && r >= t[p].r) {
            return t[p].maxb;
        }
        int res = -2e9;
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if (l <= mid) res = std::max(res, query_maxb(p << 1, l, r));
        if (mid < r) res = std::max(res, query_maxb(p << 1 | 1, l, r));
        return res;
    }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    SegmentTreeBeat t;
    t.init(n, a);

    while (m --) {
        int op, l, r;
        std::cin >> op >> l >> r;
        if (op == 1) {
            int k;
            std::cin >> k;
            t.update_add(1, l, r, k); // 区间加
        }
        if (op == 2) {
            int v;
            std::cin >> v;
            t.update_min(1, l, r, v); // 区间变min{v, 最小值}
        }
        if (op == 3) {
            std::cout << t.query_sum(1, l, r) << '\n'; // 区间和
        }
        if (op == 4) {
            std::cout << t.query_maxa(1, l, r) << '\n'; // 区间 max_A
        }
        if (op == 5) {
            std::cout << t.query_maxb(1, l, r) << '\n'; // 区间 max_B
        }
        // B <-- max{B, A} // 历史最值
    }
    return 0;
}