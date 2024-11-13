#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int N = 2e5 + 10;
const int mod = 998244353;
const int inf = 0;
struct SegmentTree {
    int n;
    struct node {
        int l, r, x;
        int sum, add, max, min;
    };
    std::vector<node> t;
    std::vector<int> a;
    SegmentTree() {}
    void init(int n) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0, inf});
        a.assign(n + 1, 0);
        build(1, 1, n);
    }
    void init(int n, std::vector<int> v) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0, inf});
        a.assign(v.begin(), v.end());
        build(1, 1, n);
    }
    void pushup(int u) {
        t[u].sum = t[u << 1].sum + t[u << 1 | 1].sum;
        t[u].max = std::max(t[u << 1].max, t[u << 1 | 1].max);
        t[u].min = std::min(t[u << 1].min, t[u << 1 | 1].min);
    }
    void pushdown(int u) {
        if (! t[u].add) return ;
        t[u << 1].sum += (t[u << 1].r - t[u << 1].l + 1) * t[u].add;
        t[u << 1 | 1].sum += (t[u << 1 | 1].r - t[u << 1 | 1].l + 1) * t[u].add;
        t[u << 1].add += t[u].add, t[u << 1 | 1].add += t[u].add;
        t[u << 1].max += t[u].add, t[u << 1 | 1].max += t[u].add;
        t[u << 1].min += t[u].add, t[u << 1 | 1].min += t[u].add;
        t[u].add = 0;
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0, 0, 0, inf};
        if (l == r) {
            t[u] = {l, r, a[l], a[l], 0, a[l], a[l]};
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
    int query_min(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            return t[u].min;
        }
        pushdown(u);
        int res = 1e9;
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) res = std::min(res, query_min(u << 1, l, r));
        if (mid < r) res = std::min(res, query_min(u << 1 | 1, l, r));
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
    int Min(int l, int r) {
        return query_min(1, l, r);
    }
};

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), able(n + 2), lst(n + 2);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}

	SegmentTree t;
    t.init(n);

	for (int i = 1; i <= n; i ++) {
		if (a[i] != 1) {
			able[1] = 1;
		}
		if (a[i] > 1 && t.Min(1, a[i] - 1) > lst[a[i]]) {
			able[a[i]] = 1;
		}
		t.add(a[i], a[i], i - lst[a[i]]);
		lst[a[i]] = i;
	}

	for (int i = 2; i <= n + 1; i ++) {
		if (t.Min(1, i - 1) > lst[i]) {
			able[i] = 1;
		}
	}
	int ans = 1;

	for (; able[ans] && ans <= n + 1; ans ++);
	std::cout << ans << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}