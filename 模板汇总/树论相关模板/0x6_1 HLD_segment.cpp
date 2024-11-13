#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int N = 1e5 + 10, M = 2e5 + 10;

int tot, head[M], nxt[M], to[M];
void addedge(int u, int v) {
	nxt[++ tot] = head[u];
	head[u] = tot;
	to[tot] = v;
}

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
} arr;

struct TreeList {
	int cnt = 0;
	int dep[N], top[N], son[N], siz[N], fa[N], dfn[N];

	void dfs1(int cur) {
		dep[cur] = dep[fa[cur]] + (siz[cur] = 1);
		for (int i = head[cur]; i; i = nxt[i]) {
			if (to[i] == fa[cur]) continue;
			fa[to[i]] = cur;
			dfs1(to[i]);
			siz[cur] += siz[to[i]];
			if (! son[cur] || siz[son[cur]] < siz[to[i]]) {
				son[cur] = to[i];
			}
		}
	}
	void dfs2(int cur, int t) {
		dfn[cur] = ++ cnt;
		top[cur] = t;
		if (son[cur]) {
			dfs2(son[cur], t);
		}
		for (int i = head[cur]; i; i = nxt[i]) {
			if (to[i] != fa[cur] && to[i] != son[cur]) {
				dfs2(to[i], to[i]);
			}
		}
	}

	void update(int x, int y, i64 v) {
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
			arr.add(dfn[top[x]], dfn[x], v);
			x = fa[top[x]];
		}
		if (dfn[x] > dfn[y]) std::swap(x, y);
		arr.add(dfn[x], dfn[y], v);
	}

	i64 query(int x, int y) {
		i64 ans = 0;
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
			ans += arr.query(dfn[top[x]], dfn[x]);
			x = fa[top[x]];
		}
		if (dfn[x] > dfn[y]) std::swap(x, y);
		return ans + arr.query(dfn[x], dfn[y]);
	}
	void update_subtree(int x, i64 v) {
		arr.add(dfn[x], dfn[x] + siz[x] - 1, v);
	}
	i64 query_subtree(int x) {
		return arr.query(dfn[x], dfn[x] + siz[x] - 1);
	}
} tr;

void solve() {
	int n, m, r, p;
	std::cin >> n >> m >> r >> p;
	std::vector<int> a(n + 1);

	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		addedge(u, v);
		addedge(v, u);
	}
	//
	tr.dfs1(r);
	tr.dfs2(r, r);
	arr.init(n);
	for (int i = 1; i <= n; i ++) {
		tr.update(i, i, a[i]);
	}

	while (m --) {
		int s, x, y, v;
		std::cin >> s >> x;
		if (s == 1) {
			std::cin >> y >> v;
			tr.update(x, y, v);
		} else if (s == 2) { 
 			std::cin >> y;
 			std::cout << (tr.query(x, y) % p) << '\n';
		} else if (s == 3) {
			std::cin >> v;
			tr.update_subtree(x, v);
		} else if (s == 4) {
			std::cout << (tr.query_subtree(x) % p) << '\n';
		}
	}
}
signed main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}