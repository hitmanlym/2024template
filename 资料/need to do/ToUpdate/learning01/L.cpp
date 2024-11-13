#include<bits/stdc++.h>
using i64 = long long;
const int inf = 1e9 + 7;
struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n + 1);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};

const int N = 5e5 + 10, M = 1e6 + 10;

int tot, head[M], nxt[M], to[M];
void addedge(int u, int v) {
	nxt[++ tot] = head[u];
	head[u] = tot;
	to[tot] = v;
}

int val[N];
struct SegmentTree {
    int n;
    struct node {
        int l, r, x;
    };
    std::vector<node> t;
    std::vector<int> a;
    SegmentTree() {}
    void init(int n) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, inf});
        a.assign(n + 1, 0);
        build(1, 1, n);
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, inf};
        if (l == r) {
            return ;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }
    void add(int u, int l, int r, int val) {
        if (t[u].l >= l && t[u].r <= r) {
            t[u].x = std::min(t[u].x, val);
            return ;
        }
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) add(u << 1, l, r, val);
        if (mid < r) add(u << 1 | 1, l, r, val);
    }
    void add(int l, int r, int val) {
    	add(1, l, r, val);
    }
    void down(int u) {
    	if (t[u].l == t[u].r) {
    		val[t[u].l] = t[u].x;
    		return ;
    	}
    	t[u << 1].x = std::min(t[u << 1].x, t[u].x);
    	t[u << 1 | 1].x = std::min(t[u << 1 | 1].x, t[u].x);
    	down(u << 1);
    	down(u << 1 | 1);
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
		if (x != y)
		arr.add(dfn[son[x]], dfn[y], v);
	}
} tr;


void solve() {
	int n, k, m;
	std::cin >> n >> k >> m;
	DSU d(n);
	std::vector<std::array<int, 2> > e(k + 1);
	for (int i = 1; i <= k; i ++) {
		std::cin >> e[i][0] >> e[i][1];
		if (! d.same(e[i][0], e[i][1])) {
			d.merge(e[i][0], e[i][1]);
		}
		addedge(e[i][0], e[i][1]);
		addedge(e[i][1], e[i][0]);
	}
	std::vector<std::array<int, 3> > o(m);
	for (int i = 0; i < m; i ++) {
		std::cin >> o[i][0] >> o[i][1] >> o[i][2];
	}
	std::sort(o.begin(), o.end(), [&](auto x, auto y) {
		return x[2] < y[2];
	});
	int minus = 0;
	for (int i = 0; i < m; i ++) {
		int u = o[i][0], v = o[i][1], w = o[i][2];
		if (! d.same(u, v)) {
			minus += w;
			d.merge(u, v);
			addedge(u, v);
			addedge(v, u);
		}
	}
	tr.dfs1(1);
	tr.dfs2(1, 1);
	arr.init(n);

	for (int i = 0; i < m; i ++) {
		int u = o[i][0], v = o[i][1], w = o[i][2];
		tr.update(u, v, w);
	}
	arr.down(1);

	i64 ans = 0;
	for (int i = 1; i <= k; i ++) {
		int u = tr.dfn[e[i][0]], v = tr.dfn[e[i][1]];
		int it = std::max(u, v);
		if (val[it] == inf) {
			std::cout << -1 << '\n';
			return ;
		}
		ans += val[it];
	}
	std::cout << ans << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}