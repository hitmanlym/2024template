#include <bits/stdc++.h>
using i64 = long long;
#define int i64
struct SegmentTree {
    int n;
    struct node {
        int l, r, x;
        int Lsum, Rsum;
    };
    std::vector<node> t;
    std::vector<int> a;
    SegmentTree() {}
    void init(int n) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0});
        a.assign(n + 1, 0);
        build(1, 1, n);
    }
    void init(int n, std::vector<int> v) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0});
        a.assign(v.begin(), v.end());
        build(1, 1, n);
    }
    void pushup(int u) {
        t[u].Lsum = t[u << 1].Lsum + t[u << 1 | 1].Lsum - std::min(t[u << 1].Lsum, t[u << 1 | 1].Rsum);
        t[u].Rsum = t[u << 1].Rsum + t[u << 1 | 1].Rsum - std::min(t[u << 1].Lsum, t[u << 1 | 1].Rsum); 
    }
    node merge(node a, node b) {
        node res = (node){0, 0, 0, 0, 0};
        res.Lsum = a.Lsum + b.Lsum - std::min(a.Lsum, b.Rsum);
        res.Rsum = a.Rsum + b.Rsum - std::min(a.Lsum, b.Rsum); 
        return res;
    }
    void build(int u, int l, int r) { // 
        t[u] = {l, r, 0, 0, 0};
        if (l == r) {
            t[u] = {l, r, 0, a[l], a[l] ^ 1};
            return ;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    node query(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            return t[u];
        }
        node res = (node){0, 0, 0, 0, 0};
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) res = merge(res, query(u << 1, l, r));
        if (mid < r) res = merge(res, query(u << 1 | 1, l, r));
        return res;
    }
    int query(int l, int r) {
        int res = r - l + 1;
        auto it = query(1, l, r);
        return res - it.Lsum - it.Rsum;
    }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;
    int n = s.size();
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        if (s[i - 1] == '(') a[i] = 1;
    }
    SegmentTree t;
    t.init(n, a);
    int m;
    std::cin >> m;
    while (m --) {
        int l, r;
        std::cin >> l >> r;
        int ans = t.query(l, r);
        std::cout << ans << '\n';
    }
    return 0;
}