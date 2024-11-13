#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int inf = 1e18;
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
	std::vector<std::vector<pii> > e(3, std::vector<pii>(n + 1));
	for (int j = 0; j < 3; j ++) {
		for (int i = 1; i <= n; i ++) {
			std::cin >> e[j][i][0];
			e[j][i][1] = i;
		}
	}
	std::vector<std::vector<int> > E(n * 3 + 1);
	for (int i = 0; i < 3; i ++) {
		std::sort(e[i].begin() + 1, e[i].end(), [&](auto x, auto y) {
			return x[0] > y[0];
		});
		std::vector<int> O(n + 1);
		for (int j = 1; j <= n; j ++) {
			O[j] = e[i][j][1];
		}
		SegmentTree t;
		t.init(n, O);
		for (int j = 1; j <= n; j ++) { // 后面的第一个比他小的
			int L = j + 1, R = n, x = -1;
			while (L <= R) {
				int mid = L + R >> 1;
				if (t.Max(j + 1, mid) > e[i][j][1]) {
					x = mid;
					R = mid - 1;
				} else {
					L = mid + 1;
				}
			}
			if (x != -1) {
				int u = i * n + e[i][j][1], v = i * n + e[i][x][1];
				E[u].push_back(v);
			}
		}
	}
	for (int i = 1; i <= n; i ++) {
		int a = i, b = i + n, c = i + 2 * n;
		E[a].push_back(b);
		E[a].push_back(c);
		E[b].push_back(a);
		E[b].push_back(c);
		E[c].push_back(a);
		E[c].push_back(b);
	}
	std::vector<int> d(n * 3 + 1, inf), vis(n * 3 + 1);
	std::vector<int> pre(n * 3 + 1, -1);
	std::queue<int> q;
	q.push(1);
	d[1] = 0;
	while (! q.empty()) {
		int u = q.front();
		// std::cout << "!! " << u << '\n';
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto v : E[u]) {
			if (! vis[v]) {
				d[v] = d[u];
				pre[v] = u;
				q.push(v);
			}
		}
	}
	for (int i = 0; i < 3; i ++) {
		if (d[i * n + n] != inf) {
			std::cout << "YES\n";
			std::vector<pii> ans;
			int now = i * n + n;
			while (pre[now] != -1) {
				int A = now % n, B = pre[now] % n;
				if (A != B) {
					ans.push_back({(now - 1) / n, (now - 1) % n + 1});
				}
				now = pre[now];
			}
			std::cout << ans.size() << '\n';
			std::reverse(ans.begin(), ans.end());
			for (auto it : ans) {
				char c;
				if (it[0] == 0) {
					c = 'q';
				}
				if (it[0] == 1) {
					c = 'k';
				}
				if (it[0] == 2) {
					c = 'j';
				}
				std::cout << c << " " << it[1] << '\n';
			}
			return ;
		}
	}
	std::cout << "NO\n";
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