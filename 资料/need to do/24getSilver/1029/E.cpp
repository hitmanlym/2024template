#include<bits/stdc++.h>
using i64 = long long;
#define int i64
struct SegmentTree {
    int n;
    struct node { // min & num
        int l, r;
        int min, num, add;
    };
    std::vector<node> t;
    SegmentTree() {}
    void init(int n) {
        this -> n = n;
        t.assign(4 * n + 1, (node){0, 0, 0, 0, 0});
        build(1, 1, n);
    }
    void pushup(int u) {
        t[u].min = std::min(t[u << 1].min, t[u << 1 | 1].min);
        t[u].num = 0;
        if (t[u << 1].min == t[u].min) {
        	t[u].num += t[u << 1].num;
        }
        if (t[u << 1 | 1].min == t[u].min) {
        	t[u].num += t[u << 1 | 1].num;
        }
    }
    void pushdown(int u) { // +1 ; -1
        if (! t[u].add) return ;
        t[u << 1].add += t[u].add, t[u << 1 | 1].add += t[u].add;
        t[u << 1].min += t[u].add, t[u << 1 | 1].min += t[u].add;
        t[u].add = 0;
    }
    void build(int u, int l, int r) {
        t[u] = {l, r, 0, 0, 0};
        if (l == r) {
        	t[u].num = 1;
            return ;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void add(int u, int l, int r, int val) {
        if (t[u].l >= l && t[u].r <= r) {
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
    void add(int l, int r, int val) {
        add(1, l, r, val);
    }
    int query(int l, int r) {
        return query(1, l, r);
    }
};
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n + 1);
	std::map<int, std::vector<int> > v;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		// v[a[i]].push_back(i);
	}
	SegmentTree t;
	t.init(n);
	int ans = 0;
	// for (int i = 1; i <= n; i ++) {
	// 	std::cout << t.query(1, i) << ' ';
	// }
	// std::cout << '\n';
	for (int i = 1; i <= n; i ++) {
		int u = a[i], o = v[u].size();
		if (o >= k) {
			int l = 1;
			if (o > k) {
				l = v[u][o - k - 1] + 1;
			}
			int r = v[u][o - k];
			t.add(l, r, -1);
		}
		v[u].push_back(i);
		o ++;
		if (o >= k) {
			int l = 1;
			if (o > k) {
				l = v[u][o - k - 1] + 1;
			} 
			int r = v[u][o - k];
			t.add(l, r, 1);
		}
		// std::cout << t.query(1, i) << ' ';
		ans += t.query(1, i);
	}
	// std::cout << '\n';
	std::cout << ans << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}