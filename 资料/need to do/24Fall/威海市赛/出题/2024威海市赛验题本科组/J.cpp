#include<bits/stdc++.h>
using i64 = long long;
const int inf = 1e9;
struct SegmentTree {
    int n;
    struct node {
        int l, r, iui;
        int sum, add, max, x, y;
    };
    std::vector<node> t;
    std::vector<int> a;
    SegmentTree() {}
    void init(int n) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0, 0, 0, 0});
        a.assign(n + 1, 0);
        build(1, 1, n);
    }
    void pushup(int u) {
        t[u].max = std::max(t[u << 1].max, t[u << 1 | 1].max);
        if (t[u].max == t[u << 1].max) {
        	t[u].x = t[u << 1].x;
        	t[u].y = t[u << 1].y;
        } else {
        	t[u].x = t[u << 1 | 1].x;
        	t[u].y = t[u << 1 | 1].y;
        }
    }
    void pushdown(int u) {
        if (! t[u].add) return ;
        t[u << 1].add += t[u].add, t[u << 1 | 1].add += t[u].add;
        t[u << 1].max += t[u].add, t[u << 1 | 1].max += t[u].add;
        t[u].add = 0;
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0, 0, 0, 0, 0};
        if (l == r) {
            t[u] = {l, r, a[l], a[l], 0, a[l], 0, 0};
            return ;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void add(int u, int l, int r, std::array<int, 3> val) {
        if (t[u].l >= l && t[u].r <= r) {
            t[u].max = val[0];
            t[u].x = val[1];
            t[u].y = val[2];
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
    std::array<int, 3> fix(auto xx, auto xy) {
    	if (xx[0] > xy[0]) {
    		return xx;
    	} else {
    		return xy;
    	}
    }
    std::array<int, 3> query_max(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) {
            return {t[u].max, t[u].x, t[u].y};
        }
        pushdown(u);
        std::array<int, 3> res = {-inf, 0, 0};
        int mid = t[u].l + t[u].r >> 1;
        if (l <= mid) res = fix(res, query_max(u << 1, l, r));
        if (mid < r) res = fix(res, query_max(u << 1 | 1, l, r));
        return res;
    }
    void add(int l, int r, std::array<int, 3> val) {
        add(1, l, r, val);
    }
    int query(int l, int r) {
        return query(1, l, r);
    }
    std::array<int, 3> Max(int l, int r) {
        return query_max(1, l, r);
    }
};
void solve() {
	int h, w, n;
	std::cin >> h >> w >> n;
	std::vector<std::vector<int> > have(h + 1);
	std::map<std::array<int, 2>, std::array<int, 2> > nxt;
	for (int i = 1; i <= n; i ++) {
		int x, y;
		std::cin >> x >> y;
		have[x].push_back(y);
	}
	have[1].push_back(1);
	for (int i = 1; i <= h; i ++) {
		std::sort(have[i].begin(), have[i].end());
	}
	std::set<std::array<int, 3> > dp;
	SegmentTree t;
	t.init(w);
	for (int i = h; i >= 1; i --) {
		std::vector<int> fuck(have[i].size(), 1); // 直接进入下一层的max
		if (i + 1 <= h) {
			for (int j = 0; j < have[i].size(); j ++) {
				auto it = t.Max(have[i][j], w);
				if (fuck[j] < it[0] + 1) {
					fuck[j] = it[0] + 1;
					nxt[{i, have[i][j]}] = {it[1], it[2]};
				}
			}
		}
		std::vector<std::array<int, 3> > now;
		int y = w, num = 0;
		for (int j = have[i].size() - 1; j >= 0; j --) {
			if (fuck[j] < num + 1) {
				now.push_back({num + 1, i, have[i][j]});
				nxt[{i, have[i][j]}] = {i, y};
				y = have[i][j];
				num ++;
			} else {
				now.push_back({fuck[j], i, have[i][j]});
				y = have[i][j];
				num = fuck[j];
			}
		}
		for (auto it : now) {
			t.add(it[2], it[2], {it[0], it[1], it[2]});
		}
	}
	std::cout << t.Max(1, 1)[0] - 1 << '\n';
	int x = 1, y = 1;
	while (nxt.count({x, y})) {
		auto it = nxt[{x, y}];
		while (x < it[0]) {
			std::cout << "D";
			x ++;
		}
		while (y < it[1]) {
			std::cout << "R";
			y ++;
		}
	}
	while (x < h) {
		std::cout << "D";
		x ++;
	}
	while (y < w) {
		std::cout << "R";
		y ++;
	}
	std::cout << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}