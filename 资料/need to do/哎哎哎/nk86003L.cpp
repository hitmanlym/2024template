#include<bits/stdc++.h>
using i64 = long long;
#define int i64
struct SegmentTree {
    int n;
    struct node {
        int l, r;
        int x, d, sum;
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
        t[u].sum = t[u << 1].sum + t[u << 1 | 1].sum;
    }
    void pushdown(int u) {
        if (t[u].x == 0 && t[u].d == 0) return ;
        int mid = t[u].l + t[u].r >> 1;
        int x1 = t[u].x, x2 = t[u].x + t[u].d * (mid - t[u].l + 1);

        t[u << 1].sum += (x1 + x1 + t[u].d * (mid - t[u].l)) * (mid - t[u].l + 1) / 2;
        t[u << 1 | 1].sum += (x2 + x2 + t[u].d * (t[u].r - mid - 1)) * (t[u].r - mid) / 2; 
        t[u << 1].x += x1;
        t[u << 1 | 1].x += x2;
        t[u << 1].d += t[u].d;
        t[u << 1 | 1].d += t[u].d;

        t[u].x = 0;
        t[u].d = 0;
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0, 0};
        if (l == r) {
            t[u] = {l, r, 0, 0, a[l]};
            return ;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void add(int u, int l, int r, int x, int d) {
    	int xx = x + (t[u].l - l) * d;
        if (t[u].l >= l && t[u].r <= r) {
            t[u].sum += (xx + xx + d * (t[u].r - t[u].l)) * (t[u].r - t[u].l + 1) / 2;
            t[u].x += xx;
            t[u].d += d;
            return ;
        }
        pushdown(u);
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) add(u << 1, l, r, x, d);
        if (mid < r) add(u << 1 | 1, l, r, x, d);
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
    void add(int l, int r, int x, int d) {
        add(1, l, r, x, d);
    }
    int query(int l, int r) {
        return query(1, l, r);
    }
};


void solve() {
	int n;
	std::cin >> n;
	std::vector<std::array<int, 2> > a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i][0];
		a[i][1] = i;
	}
	std::sort(a.begin() + 1, a.end(), [&](auto x, auto y) {
		return x[0] > y[0];
	});
	int m;
	std::cin >> m;
	std::vector<std::array<int, 4> > q(m);
	std::vector<i64> ans(m);
	for (int i = 0; i < m; i ++) {
		std::cin >> q[i][0] >> q[i][1] >> q[i][2];
		q[i][3] = i;
	}
	std::sort(q.begin(), q.end(), [&](auto x, auto y) {
		return x[0] > y[0];
	});
	std::set<std::array<int, 2> > st;
	int l = 1;
	SegmentTree t;
	t.init(n);
	auto insert = [&](int x) -> void { // add or del
		if (! st.size()) {
			st.insert({x, x});
			int len = 1;
			t.add(1, len, len, -1);
			return ;
		}
		auto it = st.lower_bound({x, 0});
		if (it == st.begin()) {
			if (x == (*it)[0] - 1) {
				st.insert({x, (*it)[1]});
				int len = (*it)[1] - x + 1;
				t.add(1, len, len, -1);
				t.add(1, len - 1, -(len - 1), 1);
				st.erase(it);
			} else {
				st.insert({x, x});
				int len = 1;
				t.add(1, len, len, -1);
			}
		} else {
			auto pre = prev(it);
			if (x == (*pre)[1] + 1) {
				st.insert({(*pre)[0], x});
				int len = x - (*pre)[0] + 1;
				t.add(1, len, len, -1);
				t.add(1, len - 1, -(len - 1), 1);
				st.erase(pre);
				pre = prev(it);
			} else {
				st.insert({x, x});
				pre = st.lower_bound({x, x});
				int len = 1;
				t.add(1, len, len, -1);
			}

			if (it != st.end()) {
				if ((*pre)[1] + 1 == (*it)[0]) {
					st.insert({(*pre)[0], (*it)[1]});
					int len = (*it)[1] - (*pre)[0] + 1;
					int x = (*it)[1] - (*it)[0] + 1, y = (*pre)[1] - (*pre)[0] + 1;
					t.add(1, len, len, -1);
					t.add(1, x, -x, 1);
					t.add(1, y, -y, 1);
					st.erase(pre);
					st.erase(it);
				}
			}
		}
	};
	/*
	auto work = [&](int l, int r) -> i64 {
		i64 ans = 0;
		for (auto it : st) {
			//std::cout << "!!! " << l << " " << r << ' ' << it[0] << ' ' << it[1] << '\n';
			int len = it[1] - it[0] + 1;
			if (len < l) continue;
			i64 res = 1ll * len * (len + 1) / 2;
			res -= 1ll * (l - 1) * (len + len - (l - 1) + 1) / 2;
			if (r < len) {
				res -= 1ll * (len - (r + 1) + 1) * (len - (r + 1) + 1 + 1) / 2;
				//std::cout << "?? " << (len - (r + 1) + 1) * (len - (r + 1) + 1 + 1) / 2 << '\n';
			}
			ans += res;
		}
		return ans;
	};*/
	for (int i = 0; i < m; i ++) {
		while (l <= n && a[l][0] >= q[i][0]) {
			insert(a[l][1]);
			l ++;
		}
		//ans[q[i][3]] = work(q[i][1], q[i][2]);
		ans[q[i][3]] = t.query(q[i][1], q[i][2]);
		std::cout << "!!! " << q[i][0] << '\n';
		for (auto it : st) {
			std::cout << it[1] - it[0] + 1 << ' ' << it[0] << ' ' << it[1] << '\n';
		}
		std::cout << '\n';
	}
	for (int i = 0; i < m; i ++) {
		std::cout << ans[i] << '\n';
	}
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