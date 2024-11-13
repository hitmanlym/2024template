#include<bits/stdc++.h>
using i64 = long long;
const int N = 1e5 + 10, M = 2e5 + 10;

int a[N];
int tot, head[M], nxt[M], to[M];
void addedge(int u, int v) {
	nxt[++ tot] = head[u];
	head[u] = tot;
	to[tot] = v;
}

int lowbit(int x) {return x & (- x);}
struct Fenwick {
	int n;
	i64 t1[N], t2[N];
	void add(int x, i64 val) {
		for (int i = x; i <= n; i += lowbit(i)) {
			t1[i] = t1[i] + val, t2[i] =  t2[i] + val * x;
		}
	}
	i64 sum(int x) {
		i64 ans = 0;
		for (int i = x; i; i -= lowbit(i)) {
			ans = ans + (x + 1) * t1[i] - t2[i];
		}
		return ans;
	}
	void update(int l, int r, i64 val) {
		add(l, val), add(r + 1, -val);
	}
	i64 query(int l, int r) {
		return sum(r) - sum(l - 1);
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
			arr.update(dfn[top[x]], dfn[x], v);
			x = fa[top[x]];
		}
		if (dfn[x] > dfn[y]) std::swap(x, y);
		arr.update(dfn[x], dfn[y], v);
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
		arr.update(dfn[x], dfn[x] + siz[x] - 1, v);
	}
	i64 query_subtree(int x) {
		return arr.query(dfn[x], dfn[x] + siz[x] - 1);
	}
} tr;

void solve() {
	int n, m, r, p;
	std::cin >> n >> m >> r >> p;
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
	arr.n = n;
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
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}