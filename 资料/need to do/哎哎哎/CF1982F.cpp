#include <bits/stdc++.h>
using i64 = long long;
const int inf = 1e9;
struct SegmentTree {
    int n;
    struct node {
        int l, r;
        int add;
        int max, min;
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
        t[u].max = std::max(t[u << 1].max, t[u << 1 | 1].max);
        t[u].min = std::min(t[u << 1].min, t[u << 1 | 1].min);
    }
    void pushdown(int u) {
        if (! t[u].add) return ;
        t[u << 1].add += t[u].add, t[u << 1 | 1].add += t[u].add;
        t[u << 1].max += t[u].add, t[u << 1 | 1].max += t[u].add;
        t[u << 1].min += t[u].add, t[u << 1 | 1].min += t[u].add;
        t[u].add = 0;
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0};
        if (l == r) {
            t[u] = {l, r, 0, a[l], a[l]};
            return ;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void add(int u, int l, int r, int val) {
        if (t[u].l >= l && t[u].r <= r) {
            t[u].max += val;
            t[u].min += val;
            t[u].add += val;
            return ;
        }
        pushdown(u);
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) add(u << 1, l, r, val);
        if (mid < r) add(u << 1 | 1, l, r, val);
        pushup(u);
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
    int query_min(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            return t[u].min;
        }
        pushdown(u);
        int res = inf;
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) res = std::min(res, query_min(u << 1, l, r));
        if (mid < r) res = std::min(res, query_min(u << 1 | 1, l, r));
        return res;
    }
    void add(int l, int r, int val) {
        add(1, l, r, val);
    }
    int Max(int l, int r) {
        if (l > r) {
            return -inf;
        }
        return query_max(1, l, r);
    }
    int Min(int l, int r) {
        if (l > r) {
            return inf;
        }
        return query_min(1, l, r);
    }
};

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 2);
    a[0] = -inf;
    a[n + 1] = inf;
    std::set<int> st;
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
        if (i > 1 && a[i - 1] > a[i]) {
            st.insert(i - 1);
        }
    }
    SegmentTree t;
    t.init(n, a);
    int q;
    std::cin >> q;
    auto work = [&]() {
        if (! st.size()) {
            std::cout << -1 << ' ' << -1 << '\n';
            return ;
        }
        int L = *st.begin(), R = *st.rbegin() + 1;
        int min = t.Min(L, R), max = t.Max(L, R);
        int l = 0, r = n + 1, ansl = L, ansr = R;
        //std::cout << "## " << L << ' ' << R << '\n';
        L --;
        while (l <= L) {
            int mid = l + L >> 1;
            //if (t.Max(1, mid) <= min) {
            if (a[mid] <= std::min(a[mid + 1], min)) {
                ansl = mid + 1;
                l = mid + 1;
            } else {
                L = mid - 1;
            }
        }
        R ++;
        while (R <= r) {
            int mid = R + r >> 1;
            //if (t.Min(mid, n) >= max) {
            if (a[mid] >= std::max(a[mid - 1], max)) {
                ansr = mid - 1;
                r = mid - 1;
            } else {
                R = mid + 1;
            }
        }
        std::cout << ansl << ' ' << ansr << '\n';
        /*int ansl = t.askl(1, 1, L - 1, min) + 1;
        int ansr = t.askr(1, R + 1, n, max) - 1;*/
    };
    work();
    while (q --) {
        int x, y;
        std::cin >> x >> y;
        if (a[x - 1] > a[x] && a[x - 1] <= y) {
            st.erase(x - 1);
        }
        if (a[x - 1] <= a[x] && a[x - 1] > y) {
            st.insert(x - 1);
        }
        if (a[x] > a[x + 1] && y <= a[x + 1]) {
            st.erase(x);
        }
        if (a[x] <= a[x + 1] && y > a[x + 1]) {
            st.insert(x);
        }
        t.add(x, x, y - a[x]);
        a[x] = y;
        work();
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