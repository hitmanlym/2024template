#include <bits/stdc++.h>
using i64 = long long;

const int M = 1e5+5;
int n, m;
i64 a[M];

struct SegmentTree {
    int l, r;
    
    int b, lb, rb, mb;
    int c, lc, rc, mc;
    int len, tag, rev;

}t[M << 2];
void update(int p) {
    t[p].b = t[p << 1].b + t[p << 1 | 1].b;
    t[p].lb = t[p << 1].c ? t[p << 1].lb : t[p << 1].b + t[p << 1 | 1].lb;
    t[p].rb = t[p << 1 | 1].c ? t[p << 1 | 1].rb : t[p << 1 | 1].b + t[p << 1].rb;
    t[p].mb = std::max({t[p << 1].mb, t[p << 1 | 1].mb, t[p << 1].rb + t[p << 1 | 1].lb});

    t[p].c = t[p << 1].c + t[p << 1 | 1].c;
    t[p].lc = t[p << 1].b ? t[p << 1].lc : t[p << 1].c + t[p << 1 | 1].lc;
    t[p].rc = t[p << 1 | 1].b ? t[p << 1 | 1].rc : t[p << 1 | 1].c + t[p << 1].rc;
    t[p].mc = std::max({t[p << 1].mc, t[p << 1 | 1].mc, t[p << 1].rc + t[p << 1 | 1].lc});

}
void update(SegmentTree &a, SegmentTree b, SegmentTree c) {
    a.b = b.b + c.b;
    a.lb = b.c ? b.lb : b.b + c.lb;
    a.rb = c.c ? c.rb : c.b + b.rb;
    a.mb = std::max({b.mb, c.mb, b.rb + c.lb});

    a.c = b.c + c.c;
    a.lc = b.b ? b.lc : b.c + c.lc;
    a.rc = c.b ? c.rc : c.c + b.rc;
    a.mc = std::max({b.mc, c.mc, b.rc + c.lc});
}
void pd(int p, int k) {
    if (k == 0) {
        t[p].b = t[p].lb = t[p].rb = t[p].mb = 0;
        t[p].c = t[p].lc = t[p].rc = t[p].mc = t[p].len;
        t[p].tag = 0;
        t[p].rev = 0;
    } 
    if (k == 1) {
        //std::cout << t[p].len << " YES\n";
        t[p].b = t[p].lb = t[p].rb = t[p].mb = t[p].len;
        t[p].c = t[p].lc = t[p].rc = t[p].mc = 0;
        t[p].tag = 1;
        t[p].rev = 0;
    }
    if (k == 2) {
        std::swap(t[p].b, t[p].c);
        std::swap(t[p].lb, t[p].lc);
        std::swap(t[p].rb, t[p].rc);
        std::swap(t[p].mb, t[p].mc);
        t[p].rev ^= 1;
    }
}
void pushdown(int p) {
    if (t[p].tag == 0) {
        pd(p << 1, 0), pd(p << 1 | 1, 0);
    } 
    if (t[p].tag == 1) {
        pd(p << 1, 1), pd(p << 1 | 1, 1);
    }
    if (t[p].rev) {
        pd(p << 1, 2), pd(p << 1 | 1, 2);
    }
    t[p].tag = -1;
    t[p].rev = 0;
}
void build(int p, int l, int r) {
    int tt = a[l];
    t[p] = {
        l, r, tt, tt, tt, tt, tt ^ 1, tt ^ 1, tt ^ 1, tt ^ 1, r - l + 1, -1, 0
    };
    if (l == r) {
        return ;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    update(p);
}
void change(int p, int l, int r, int k) {
    if (t[p].l >= l && t[p].r <= r) {
        pd(p, k);
        return ;
    }
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) change(p << 1, l, r, k);
    if (r > mid) change(p << 1 | 1, l, r, k);
    update(p);
}
SegmentTree query(int p, int l, int r) {
    if (t[p].l >= l && t[p].r <= r) {
        return t[p];
    }
    pushdown(p);
    SegmentTree res, t1 = {}, t2 = {};
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) t1 = query(p << 1, l, r);
    if (r > mid) t2 = query(p << 1 | 1, l, r);
    update(res, t1, t2);
    return res;
}
void solve() {
    int n, m, k;
    std::cin >> n >> k >> m;
    std::vector<int> b(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> b[i];
    }
    for (int i = n; i >= 1; i --) {
        if (b[i] == b[i - 1] + 1) a[i] = 1;
        else a[i] = 0;
    }
    build(1, 1, n);/*
    for (int i = 1; i <= n; i ++) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';*/

    while (m --) {
        int l, r;
        std::cin >> l >> r;
        int state = query(1, l, l).b; // 1 ? 
        change(1, l, l, 0);
        auto res = query(1, l, r);
        //std::cout << l << ' ' << r << ' ' << res.c << ' ' << res.mb << '\n';
        change(1, l, l, state);
        std::cout << r - l + 1 - (res.mb + 1) << '\n';
    }
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