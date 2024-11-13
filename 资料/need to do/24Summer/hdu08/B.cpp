#include<bits/stdc++.h>
using i64 = long long;
struct SegmentTree1 {
    int n;
    struct node {
        int l, r, add, max, min, maxid, minid;
    };
    std::vector<node> t;
    std::vector<int> a;
    SegmentTree1() {}
    void init(int n, std::vector<int> v) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0, 0});
        a.assign(v.begin(), v.end());
        build(1, 1, n);
    }
    void pushup(int u) {
        t[u].max = std::max(t[u << 1].max, t[u << 1 | 1].max);
        t[u].min = std::min(t[u << 1].min, t[u << 1 | 1].min);
        if (t[u].max == t[u << 1].max) {
        	t[u].maxid = t[u << 1].maxid;
        } else {
        	t[u].maxid = t[u << 1 | 1].maxid;
        }
        if (t[u].min == t[u << 1].min) {
        	t[u].minid = t[u << 1].minid;
        } else {
        	t[u].minid = t[u << 1 | 1].minid;
        }
    }
    void pushdown(int u) {
        if (! t[u].add) return ;
        t[u << 1].add += t[u].add, t[u << 1 | 1].add += t[u].add;
        t[u << 1].max += t[u].add, t[u << 1 | 1].max += t[u].add;
        t[u << 1].min += t[u].add, t[u << 1 | 1].min += t[u].add;
        t[u].add = 0;
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0, 0, 0, 0};
        if (l == r) {
            t[u] = {l, r, 0, a[l], a[l], l, l};
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
            return t[u].maxid;
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
            return t[u].minid;
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
    int Max(int l, int r) {
        return query_max(1, l, r);
    }
    int Min(int l, int r) {
        return query_min(1, l, r);
    }
};


const int N = 1e3 + 10, M = 2e3 + 10;

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
struct LCA {
    int n, rt = 1, dfn[N], ff[20][N], dn;
    struct {
        int to, nxt;
    } e[N * 2];
    int h[N], num = 0;

    LCA(int n) : n(n + 1) {}
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
        if (u == v) {
            return u;
        } 
        if ((u = dfn[u]) > (v = dfn[v])) std::swap(u, v);
        int d = std::__lg(v - u);
        return get(ff[d][++ u], ff[d][v - (1 << d) + 1]);
    }
};
void solve() {
	int n, m;
	std::cin >> n;
	std::vector<int> a(n + 1), p(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		p[a[i]] = i;
	}
	LCA op(n);
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		addedge(u, v);
		addedge(v, u);
		op.addEdge(u, v);
	}
	op.work();
	SegmentTree1 t;
	std::vector<int> kl(n + 1);
	for (int i = 1; i <= n; i ++) {
		kl[i] = op.dfn[i];
	}
	t.init(n, kl);

	tr.dfs1(1);
	tr.dfs2(1, 1);
	arr.init(n);
	for (int i = 1; i <= n; i ++) {
		tr.update(i, i, a[i]);
	}

	std::cin >> m;
	while (m --) {
		int op, l, r;
		std::cin >> op >> l >> r;
		if (op & 1) {

		} else {
			int max = t.Max(l, r), min = t.Min(l, r);

			
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