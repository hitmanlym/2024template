#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
struct SegmentTree { // 
    int n;
    struct node {
        int l, r;
        int sum, max, tim, maxtim;
    };
    std::vector<node> t;
    std::vector<int> a;
    std::map<pii, pii> mp;
    SegmentTree() {}
    void init(int n) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0});
        a.assign(n + 1, 0);
        build(1, 1, n);
    }
    void init(int n, std::vector<int> v) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0});
        a.assign(v.begin(), v.end());
        build(1, 1, n);
    }
    void pushup(int u) {
        t[u].sum = t[u << 1].sum + t[u << 1 | 1].sum;
        t[u].max = std::max(t[u << 1].max, t[u << 1 | 1].max);
        t[u].maxtim = std::max(t[u << 1].maxtim, t[u << 1 | 1].maxtim);
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0, 0, 0};
        if (l == r) {
            t[u] = {l, r, a[l], a[l], 0, 0};
            return ;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void update(int u, int x, int val, int tim) {
    	//t[u].tim = tim;
        if (t[u].l == t[u].r && t[u].l == x) {
        	t[u].sum = val;
        	t[u].max = val;
        	t[u].maxtim = tim;
            return ;
        }
        int mid = t[u].l + t[u].r >> 1;
        if (x <= mid) update(u << 1, x, val, tim);
        if (mid < x) update(u << 1 | 1, x, val, tim);
        pushup(u);
    }
    int query_max(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            return t[u].max;
        }
        int res = -1e9;
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) res = std::max(res, query_max(u << 1, l, r));
        if (mid < r) res = std::max(res, query_max(u << 1 | 1, l, r));
        return res;
    }
    int Max(int l, int r) {
        return query_max(1, l, r);
    }

    int query_maxtim(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            return t[u].maxtim;
        }
        int res = -1e9;
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) res = std::max(res, query_maxtim(u << 1, l, r));
        if (mid < r) res = std::max(res, query_maxtim(u << 1 | 1, l, r));
        return res;
    }
    int Maxtim(int l, int r) {
        return query_maxtim(1, l, r);
    }

    int query(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            return t[u].sum;
        }
        int res = 0;
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) res += query(u << 1, l, r);
        if (mid < r) res += query(u << 1 | 1, l, r);
        return res;
    }
    int Query(int l, int r) {
    	// 
    	if (r - l + 1 < 3) return -1;
    	int max = Max(l, r), sum = query(l, r), tim = Maxtim(l, r);
    	if (sum > 2 * max) {
    		mp[{l, r}] = {tim, r - l + 1};
    		return r - l + 1;
    	}
    	if (mp.count({l, r}) && mp[{l, r}][0] == tim) {
    		return mp[{l, r}][1];
    	}
    	int L = l, R = r, mid;
    	while (L <= R) {
    		int op = L + R >> 1;
    		if (Max(l, op) == max) {
    			R = op - 1;
    			mid = op;
    		} else {
    			L = op + 1;
    		}
    	}
        int res = -1;

        if (mid - 1 >= l) res = std::max(res, Query(l, mid - 1));
        if (mid < r) res = std::max(res, Query(mid + 1, r));
        mp[{l, r}] = {tim, res};
        return res;
    }
    void update(int x, int val, int tim) {
        update(1, x, val, tim);
    }
    int query(int l, int r) {
        return query(1, l, r);
    }
    
};

void solve() {
	int n, q;
	std::cin >> n >> q;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	SegmentTree t;
	t.init(n, a);
	for (int i = 1; i <= q; i ++) {
		int op, l, r;
		std::cin >> op >> l >> r;
		if (op & 1) {
			std::cout << t.Query(l, r) << '\n';
		} else {
			t.update(l, r, i);
		}
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