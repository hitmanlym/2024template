#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
struct SegmentTree {
    int n;
    struct node {
        int l, r, x;
        int sum, add, max;
    };
    std::vector<node> t;
    std::vector<int> a;
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
    }
    void pushdown(int u) {
        if (! t[u].add) return ;
        t[u << 1].sum += (t[u << 1].r - t[u << 1].l + 1) * t[u].add;
        t[u << 1 | 1].sum += (t[u << 1 | 1].r - t[u << 1 | 1].l + 1) * t[u].add;
        t[u << 1].add += t[u].add, t[u << 1 | 1].add += t[u].add;
        t[u << 1].max += t[u].add, t[u << 1 | 1].max += t[u].add;
        t[u].add = 0;
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0, 0, 0};
        if (l == r) {
            t[u] = {l, r, a[l], a[l], 0, a[l]};
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
	int n;
	std::cin >> n;
	SegmentTree t;
	t.init(n);
	std::vector<std::vector<int> > e(n + 1);
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	int q;
	std::cin >> q;
	std::vector<int> ans(q + 1);
	std::vector<std::vector<pii> > bg(n + 1);
	for (int i = 1; i <= q; i ++) {
		int x, k;
		std::cin >> x >> k;
		bg[x].push_back({k, i});
	}
	std::vector<std::vector<pii> > max(n + 1, std::vector<pii>(2)); 
	auto add = [&](int u, int v, int val) {
		if (val > max[u][0][0]) {
			max[u][1] = max[u][0];
			max[u][0] = {val, v};
		} else if (val > max[u][1][0]) {
			max[u][1] = {val, v};
		}
	};
	auto dfs = [&](auto self, int u, int p) -> void {
		for (auto v : e[u]) {
			if (v == p) continue;	
			self(self, v, u);
			add(u, v, max[v][0][0] + 1);
		}
	};
	dfs(dfs, 1, 0);
	auto dfs1 = [&](auto self, int u, int p, int dep) -> void {
		// int MAX = op + max[u][0][0];
		for (auto it : bg[u]) {
			int id = it[1], k = it[0];
			ans[id] = max[u][0][0];
			if (dep > 1) {
				int op = t.Max(std::max(1ll, dep - k), dep - 1);
				ans[id] = std::max(ans[id], op + dep);
			}
		}
		for (auto v : e[u]) {
			if (v == p) continue;
			int th;
			if (max[u][0][1] != v) {
				th = max[u][0][0];
			} else {
				th = max[u][1][0];
			}
			t.add(dep, dep, th - dep);
			self(self, v, u, dep + 1);
			t.add(dep, dep, dep - th);
		}
	};
	dfs1(dfs1, 1, 0, 1);
	for (int i = 1; i <= q; i ++) {
		std::cout << ans[i] << ' ';
	}
	std::cout << '\n';
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