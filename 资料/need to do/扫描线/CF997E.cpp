#include <bits/stdc++.h>
using i64 = long long;
#define int i64
struct SegmentTree {
    int n;
    struct node {
        int l, r, x;
        int min, cnt, add, time, ans;
    };
    std::vector<node> t;
    std::vector<int> a;
    SegmentTree() {}
    void init(int n) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0, 0, 0});
        a.assign(n + 1, 0);
        build(1, 1, n);
    }
    void init(int n, std::vector<int> v) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0, 0, 0});
        a.assign(v.begin(), v.end());
        build(1, 1, n);
    }
    void pushup(int u) {
        int min = std::min(t[u << 1].min, t[u << 1 | 1].min);
        int cnt = 0;
        if (min == t[u << 1].min) cnt += t[u << 1].cnt;
        if (min == t[u << 1 | 1].min) cnt += t[u << 1 | 1].cnt;
        t[u].min = min;
        t[u].cnt = cnt;
        t[u].ans = t[u << 1].ans + t[u << 1 | 1].ans;
    }
    void pushdown(int u) {
        if (t[u].add) {
            t[u << 1].add += t[u].add, t[u << 1 | 1].add += t[u].add;
            t[u << 1].min += t[u].add, t[u << 1 | 1].min += t[u].add; 
            t[u].add = 0;
        }
        if (t[u].time) {
            // 注意pushdown 可能在运算ans 时才会进行，而我们在 r = i - 1 时的 tag 在 r = i 时
            // 父亲的值就不是 0 了，要按照 新的值 计算，但只要 儿子等于父亲， 
            // 就会继承父亲为 0 时所产生的解。
            // 维护了历史区间为 0 的值的和
            if (t[u << 1].min == t[u].min) {
                t[u << 1].time += t[u].time;
                t[u << 1].ans += t[u].time * t[u << 1].cnt;
            }
            if (t[u << 1 | 1].min == t[u].min) {
                t[u << 1 | 1].time += t[u].time;
                t[u << 1 | 1].ans += t[u].time * t[u << 1 | 1].cnt;
            }
            t[u].time = 0;
        }
        
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0, 0, 0, 0, 0};
        if (l == r) {
            t[u] = {l, r, l, l, 1, 0, 0, 0};
            return ;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void add(int u, int l, int r, int val) {
        if (t[u].l >= l && t[u].r <= r) {
            t[u].add += val;
            t[u].min += val;
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
            return t[u].ans;
        }
        pushdown(u);
        int res = 0;
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) res += query(u << 1, l, r);
        if (mid < r) res += query(u << 1 | 1, l, r);
        return res;
    }
    void tag(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            if (t[u].min == 0) {
                t[u].time ++;
                t[u].ans += t[u].cnt;
            }
            return ;
        }
        pushdown(u);
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) tag(u << 1, l, r);
        if (mid < r) tag(u << 1 | 1, l, r);
    }
    void add(int l, int r, int val) {
        add(1, l, r, val);
    }
    int query(int l, int r) {
        return query(1, l, r);
    }
    void tag(int l, int r) {
        tag(1, l, r);
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
    int m;
    std::cin >> m;
    std::vector<int> ans(m);
    std::vector<std::vector<std::array<int, 2> > >  e(n + 1);
    for (int i = 0; i < m; i ++) {
        int u, v;
        std::cin >> u >> v;
        e[v].push_back({u, i});
    }

    SegmentTree t;
    t.init(n);
    std::vector<int> max, min;
    for (int i = 1; i <= n; i ++) {
        t.add(1, n, -1); // r.
        // max - min + l - r = 0 cnts;
        while (max.size() && a[max.back()] < a[i]) {
            int u = max.back();
            max.pop_back();
            int v = 1;
            if (max.size()) v = max.back() + 1;
            t.add(v, u, a[i] - a[u]);
        }
        max.push_back(i);

        while (min.size() && a[min.back()] > a[i]) {
            int u = min.back();
            min.pop_back();
            int v = 1;
            if (min.size()) v = min.back() + 1;
            t.add(v, u, a[u] - a[i]);
        }
        min.push_back(i);

        t.tag(1, i);
        for (auto it : e[i]) {
            int l = it[0], id = it[1];
            ans[id] = t.query(l, i);
        }
    }
    for (auto it : ans) {
        std::cout << it << '\n';
    }
    return 0;
}