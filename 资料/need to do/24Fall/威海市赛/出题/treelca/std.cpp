#include <bits/stdc++.h>
using i64 = long long;
struct LCA {
    int n, rt, dn, num;
    std::vector<std::vector<int> > ff;
    std::vector<int> dfn, h;
    struct edge { int to, nxt; };
    std::vector<edge> e;
    LCA() {}
    void init(int n) {
        this -> n = n;
        rt = 1, num = 0, dn = 0;
        ff.resize(20);
        for (int i = 0; i < 20; i ++) ff[i].assign(n + 1, 0);
        dfn.assign(n + 1, 0);
        e.resize(2 * n);
        h.assign(n + 1, 0);
    }
    void addEdge(int a, int b) {
        e[++ num] = {b, h[a]}; h[a] = num;
        e[++ num] = {a, h[b]}; h[b] = num;
    }
    void dfs(int u, int p) {
        ff[0][dfn[u] = ++ dn] = p;
        for (int  i = h[u]; i; i = e[i].nxt) {
            if (e[i].to == p) continue;
            dfs(e[i].to, u);
        }
    }
    int get(int x, int y) {
        if (dfn[x] < dfn[y]) return x;
        else return y;
    }
    void work() {
        dfs(rt, 0);
        for (int i = 1; i <= std::__lg(n); i ++) { //RMQ deep less
            for (int j = 1; j + (1 << i) - 1 <= n; j ++) {
                ff[i][j] = get(ff[i - 1][j], ff[i - 1][j + (1 << i - 1)]);
            }
        }
    }
    int lca(int u, int v) {
        if (u == v) return u;
        if ((u = dfn[u]) > (v = dfn[v])) std::swap(u, v);
        int d = std::__lg(v - u);
        return get(ff[d][++ u], ff[d][v - (1 << d) + 1]);
    }
};
struct SegmentTree {
    int n;
    struct node { int l, r, add, max; };
    std::vector<node> t;
    std::vector<int> a;
    SegmentTree() {}
    void init(int n) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0});
        a.assign(n + 1, 0);
        build(1, 1, n);
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0};
        if (l == r) {
            t[u] = {l, r, 0, a[l]};
            return ;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void pushup(int u) {
        t[u].max = std::min(t[u << 1].max, t[u << 1 | 1].max);
    }
    void pushdown(int u) {
        if (! t[u].add) return ;
        t[u << 1].add += t[u].add, t[u << 1 | 1].add += t[u].add;
        t[u << 1].max += t[u].add, t[u << 1 | 1].max += t[u].add;
        t[u].add = 0;
    }
    void add(int u, int l, int r, int val) {
        if (t[u].l >= l && t[u].r <= r) {
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
    int query_max(int u, int x) {
        if (t[u].l >= x && t[u].r <= x) {
            return t[u].max;
        }
        pushdown(u);
        int mid = t[u].l + t[u].r >> 1;
        if (x <= mid) return query_max(u << 1, x);
        if (mid < x) return query_max(u << 1 | 1, x);
    }
    void add(int l, int r, int val) {
        add(1, l, r, val);
    }
    int query_max(int x) {
        return query_max(1, x);
    }
};
void solve() {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::vector<int> > e(n + 1);
    LCA t;
    t.init(n);
    for (int i = 1; i < n; i ++) {
        int u, v;
        std::cin >> u >> v;
        t.addEdge(u, v);
    }
    t.work();
    std::vector<int> b(1);
    std::vector<std::array<int, 3> > query;
    int cnt = 0;
    for (int i = 1; i <= q; i ++) {
        int op;
        std::cin >> op;
        if (op & 1) {
            int num, x;
            std::cin >> num >> x;
            int min = x, max = x;
            for (int j = 1; j < num; j ++) {
                std::cin >> x;
                if (t.dfn[x] < t.dfn[min]) min = x;
                if (t.dfn[x] > t.dfn[max]) max = x;
            }   
            b.push_back(t.lca(min, max));
        } else {
            int l, r;
            std::cin >> l >> r;
            //std::cout << "??? : " << l << ' ' << r << '\n';
            query.push_back({l, r, ++ cnt});
        }
    }
    std::vector<bool> ans(cnt + 1);
    std::sort(query.begin(), query.end(), [&](auto x, auto y) {
        return x[1] < y[1];
    });
    int m = b.size();
    SegmentTree tr;

    tr.init(m);
    std::vector<std::vector<int> > occur(n + 1);
    for (int i = 1; i <= n; i ++) {
        occur[i].push_back(0);
    }
    int u = 1;
    for (auto it : query) {
        int L = it[0], R = it[1], id = it[2];
        while (u <= R) {
            int v = b[u], siz;
            siz = occur[v].size();

            if (siz - 1 >= 2) {

                int l = occur[v][siz - 1 - 2] + 1,
                    r = occur[v][siz - 2];
                //std::cout << u << ' ' << "&&& : " << l + y << ' ' << r + y << '\n';
                tr.add(l, r, -1);
            }
            occur[v].push_back(u);
            siz ++;
            if (siz - 1 >= 2) {
                
                int l = occur[v][siz - 1 - 2] + 1,
                    r = occur[v][siz - 2];
                //std::cout << u << ' ' << "### : " << l + y << ' ' << r + y << '\n';
                tr.add(l, r, 1);
            }
            u ++;
        }
        if (tr.query_max(L) == 0) {
            //std::cout << "!!! : " << L << " " << R << '\n';
            ans[id] = 1;
        }
    }
    for (int i = 1; i <= cnt; i ++) {
        if (ans[i]) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t--) {
        solve();
    }
}
/*
// rooted with 1
11 7
1 2
1 3
1 9
2 4
2 5
3 7
7 8
4 6
5 10
5 11
1 3 6 10 5
1 2 4 11
1 2 7 2
2 1 3
1 3 6 8 9
2 2 3
2 2 4

NO
YES
NO


5 9
1 2
1 3
2 4
2 5
1 3 4 5 1
1 2 4 5
1 2 4 2
1 2 5 3
1 3 2 4 5
1 2 2 5
2 1 2
2 2 6
2 3 5

YES
YES
NO
*/