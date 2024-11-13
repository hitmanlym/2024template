#include<bits/stdc++.h>
using i64 = long long;
#define int i64

struct SegmentTree {
    int n;
    struct node {
        int l, r, x;
        int sum, add, max, min, num;
    };
    std::vector<node> t;
    std::vector<int> a;
    SegmentTree() {}
    void init(int n) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0, 0, 1});
        a.assign(n + 1, 0);
        build(1, 1, n);
    }
    void init(int n, std::vector<int> v) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0, 0, 1});
        a.assign(v.begin(), v.end());
        build(1, 1, n);
    }
    void pushup(int u) {
        t[u].sum = t[u << 1].sum + t[u << 1 | 1].sum;
        t[u].max = std::max(t[u << 1].max, t[u << 1 | 1].max);
        t[u].min = std::min(t[u << 1].min, t[u << 1 | 1].min);
        t[u].num = 0; // bug!
        if (t[u << 1].min == t[u].min) {
        	t[u].num += t[u << 1].num;
        }
        if (t[u << 1 | 1].min == t[u].min) {
        	t[u].num += t[u << 1 | 1].num;
        }
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
        t[u] = {l, r, 0, 0, 0, 0, 0, 0};
        if (l == r) {
            t[u] = {l, r, a[l], a[l], 0, a[l], a[l], 1};
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
    int query(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            if (t[u].min == 0) {
            	return t[u].num;
            } else {
            	return 0ll;
            }
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

void solve() {
	int n, m, k;
	std::cin >> n >> m >> k;
	std::vector<int> a(n + 1), pos(n + 1);
	std::set<int> need;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		pos[a[i]] = i;
		need.insert(a[i]);
	}
	SegmentTree t;
	t.init(n, a);
	std::vector<int> b(m + 1);
	for (int i = 1; i <= m; i ++) {
		std::cin >> b[i];
		need.erase(b[i]);
	}
	std::set<int> c;
	for (int i = 1; i <= k; i ++) {
		int x;
		std::cin >> x;
		c.insert(x);
	}
	// if (n - m > k) {
	// 	std::cout << "NO\n";
	// 	return ;
	// }

	std::vector<int> p;
	for (auto it : need) {
		p.push_back(it);
		// std::cout << "??? " << it << '\n';
	}
	while (p.size()) {
		int u = p.back();
		p.pop_back();
		int i = pos[u];
		int L = 1, R = i, l, r;
		while (L <= R) {
			int mid = L + R >> 1;
			if (t.Max(mid, i) == u) {
				l = mid;
				R = mid - 1;
			} else {
				L = mid + 1;
			}
		}
		L = i, R = n;
		while (L <= R) {
			int mid = L + R >> 1;
			if (t.Max(i, mid) == u) {
				r = mid;
				L = mid + 1;
			} else {
				R = mid - 1;
			}
		}

		int len = r - l + 1 - t.query(l, r);
		// for (int j = 1; j <= n; j ++) {
		// 	std::cout << t.Max(j, j) << ' ';
		// }
		// std::cout << '\n';
		// std::cout << "!!! " << u << ' ' << len << ' ' << t.query(l, r) << ' ' << l << ' ' << r << '\n';
		t.add(i, i, -u);
		auto fk = c.upper_bound(len);
		if (fk == c.begin()) {
			std::cout << "NO\n";
			return ;
		}
		fk --;
		c.erase(fk);
	}
	std::cout << "YES\n";
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
/*
1
5 1 4
1 2 3 4 5
1
4 3 2 1
*/