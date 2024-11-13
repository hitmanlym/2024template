#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;

#define int i64
const int inf = 1e18;
struct SegmentTree {
    int n;
    struct node {
        int l, r;
        int max, min;
    };
    std::vector<node> t;
    std::vector<int> a;
    SegmentTree() {}
    void init(int n, std::vector<int> v) {
        this -> n = n;
        t.resize(4 * n + 1);
        a.assign(v.begin(), v.end());
        build(1, 1, n);
    }
    void pushup(int u) {
        t[u].max = std::max(t[u << 1].max, t[u << 1 | 1].max);
        t[u].min = std::min(t[u << 1].min, t[u << 1 | 1].min);
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, -inf, inf};
        if (l == r) {
            t[u] = {l, r, a[l], a[l]};
            return ;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void addd(int u, int x, int val) {
        if (t[u].l >= x && t[u].r <= x) {
            t[u].max += val;
            t[u].min += val;
            return ;
        }
        int mid = t[u].l + t[u].r >> 1;
        if (x <= mid) addd(u << 1, x, val);
        if (mid < x) addd(u << 1 | 1, x, val);
        pushup(u);
    }
    
    int query_max(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            return t[u].max;
        }
        int res = -inf;
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) res = std::max(res, query_max(u << 1, l, r));
        if (mid < r) res = std::max(res, query_max(u << 1 | 1, l, r));
        return res;
    }
    int query_min(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            return t[u].min;
        }
        int res = inf;
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) res = std::min(res, query_min(u << 1, l, r));
        if (mid < r) res = std::min(res, query_min(u << 1 | 1, l, r));
        return res;
    }


    void add(int l, int r, int val) {
        addd(1, l, val);
        if (r + 1 <= n) addd(1, r + 1, -val);
    }


    int Min(int l, int r) {
        return query_min(1, l, r);
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
    for (int i = n; i >= 1; i --) {
        a[i] -= a[i - 1];
    }/*
    for (int i = 1; i <= n; i ++) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';*/
    SegmentTree t;
    t.init(n, a);
    int m;
    std::cin >> m;
    while (m --) {
        int op, l, r, x;
        std::cin >> op >> l >> r;
        if (op == 1) {
            std::cin >> x;
            t.add(l, r, x);
            continue;
        }

        if (l == r) {
            std::cout << 1 << '\n';
            continue;
        }

        if (op == 2) {
            if (t.Max(l + 1, r) == 0 && t.Min(l + 1, r) == 0) {
                std::cout << 1 << '\n';
            } else {
                std::cout << 0 << '\n';
            }
        }

        if (op == 3) {
            if (t.Min(l + 1, r) > 0) {
                std::cout << 1 << '\n';
            } else {
                std::cout << 0 << '\n';
            }
        }

        if (op == 4) {
            if (t.Max(l + 1, r) < 0) {
                std::cout << 1 << '\n';
            } else {
                std::cout << 0 << '\n';
            }
        }

        if (op == 5) {
            int L = l + 1, R = r, ans = -1;
            while (L <= R) {
                int mid = L + R >> 1;
                if (t.Min(L, mid) > 0) {
                    ans = mid;
                    L = mid + 1;
                } else {
                    R = mid - 1;
                }
            }

            /*std::cout << "!!! " << ans << '\n';
            for (int i = 1; i <= n; i ++) {
                std::cout << t.Max(i, i) << ' ';
            }
            std::cout << '\n';*/

            if (ans != -1 && ans + 1 <= r && t.Min(l + 1, ans) > 0 && t.Max(ans + 1, r) < 0) {
                std::cout << 1 << '\n';
            } else {
                std::cout << 0 << '\n';
            }
        }
    }
    return 0;
}
/*
6
1 1 1 1 1 1
7
2 3 5
1 3 5 1
2 2 5
1 4 4 1
5 2 6
5 3 6
5 4 6
*/