#include<bits/stdc++.h>
using i64 = long long;
#define int i64

struct Fenwick {
    int n;
    std::vector<int> a;

    Fenwick(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        a.resize(n + 1);
        a.assign(n + 1, 0);
    }
    void add(int x, int v) {
        for (; x <= n; x += x & -x) {
            a[x] += v;
        }
    }
    void add(int x, int y, int v) {
        add(x, v), add(y + 1, -v);
    }
    int sum(int x) {
        int ans = 0;
        for (; x; x -= x & -x) {
            ans += a[x];
        }
        return ans;
    }
    int rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    int kth(int k) {   // kth value
        int ans = 0;
        for (int i = std::__lg(n); i >= 0; i--) {
            int val = ans + (1 << i);
            if (val < n && a[val] < k) {
                k -= a[val];
                ans = val;
            }
        }
        return ans + 1;
    }
};

void solve() {
	int n, m;
	std::cin >> n;
	std::vector<std::vector<int> > e(n + 1);
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	Fenwick t(n + 1);
	for (int i = 1; i < n; i ++) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	std::vector<bool> vis(n + 1);
	std::vector<int> maxp(n + 1), siz(n + 1);
	int rt, Sum = n, ans = 0;
	maxp[rt = 0] = n;

	auto getRoot = [&](auto self, int u, int p) -> void {
		siz[u] = 1;
		maxp[u] = 0;
		for (auto v : e[u]) {
			if (v == p || vis[v]) continue;
			self(self, v, u);
			siz[u] += siz[v];
			maxp[u] = std::max(maxp[u], siz[v]);
		}
		maxp[u] = std::max(maxp[u], Sum - siz[u]);
		if (maxp[u] < maxp[rt]) rt = u;
	};
	std::vector<int> sum(n + 1), max(n + 1);
	std::vector<std::array<int, 2> > q(n + 1), all(n + 1); // max, sum.
	auto getSum = [&](auto self, int u, int p) -> void {
		for (auto v : e[u]) {
			if (v == p || vis[v]) continue;
			sum[v] = sum[u] + a[v];
			q[++ q[0][0]][1] = sum[v];
			q[q[0][0]][0] = std::max(max[u], a[v]);
			max[v] = q[q[0][0]][0];
			self(self, v, u);
		}
	};
	auto calc = [&](int u) -> void {
		int p = 1;
		all[1] = {a[u], a[u]};
		for (auto v : e[u]) {
			if (vis[v]) continue;
			sum[v] = a[u] + a[v];
			max[v] = std::max(a[u], a[v]);
			q[0][0] = 1;
			//q[1][0] = q[1][1] = a[u];
			q[1][0] = max[v], q[1][1] = sum[v];
			getSum(getSum, v, u);

			// son minus
			std::sort(q.begin() + 1, q.begin() + q[0][0] + 1, [&](auto x, auto y) {
				return x[0] > y[0];
			});
			std::vector<int> vv;
			for (int i = 1; i <= q[0][0]; i ++) {
				vv.push_back(a[u] + 2 * q[i][0] - q[i][1]);
			}
			std::sort(vv.begin(), vv.end());
			vv.erase(std::unique(vv.begin(), vv.end()), vv.end());
			for (int i = 1; i <= q[0][0]; i ++) {
				int val = a[u] + 2 * q[i][0] - q[i][1];
				int idx = std::lower_bound(vv.begin(), vv.end(), q[i][1]) - vv.begin() + 1;
				int add = 0;
				if (idx > 1) {
					add = t.rangeSum(1, idx - 1);
				}
				ans -= add;

				idx = std::lower_bound(vv.begin(), vv.end(), val) - vv.begin() + 1;
				t.add(idx, 1);
			}
			for (int i = 1; i <= q[0][0]; i ++) {
				//if (q[0][1] != a[u]) {
					all[++ p] = q[i];
				//}
				int val = a[u] + 2 * q[i][0] - q[i][1];
				int idx = std::lower_bound(vv.begin(), vv.end(), val) - vv.begin() + 1;
				t.add(idx, -1);
			}
		} 
		// all add
		std::sort(all.begin() + 1, all.begin() + p + 1, [&](auto x, auto y) {
			return x[0] > y[0];
		});

		std::vector<int> vv;
		for (int i = 1; i <= p; i ++) {
			vv.push_back(a[u] + 2 * all[i][0] - all[i][1]);
		}
		std::sort(vv.begin(), vv.end());
		vv.erase(std::unique(vv.begin(), vv.end()), vv.end());
		for (int i = 1; i <= p; i ++) {
			int val = a[u] + 2 * all[i][0] - all[i][1];
			int idx = std::lower_bound(vv.begin(), vv.end(), all[i][1]) - vv.begin() + 1;
			//std::cout << "! " << idx << ' ' << all[i][0] << ' ' << all[i][1] << '\n'; 
			int add = 0;
			if (idx > 1) {
				add = t.rangeSum(1, idx - 1);
			}
			ans += add;

			idx = std::lower_bound(vv.begin(), vv.end(), val) - vv.begin() + 1;
			t.add(idx, 1);
		}
		for (int i = 1; i <= p; i ++) {
			int val = a[u] + 2 * all[i][0] - all[i][1];
			int idx = std::lower_bound(vv.begin(), vv.end(), val) - vv.begin() + 1;
			t.add(idx, -1);
		}
	};
 	auto dfz = [&](auto self, int u) -> void {
		vis[u] = 1;
		calc(u);
		for (auto v : e[u]) {
			if (vis[v]) continue;
			Sum = siz[v];
			maxp[rt = 0] = Sum;
			getRoot(getRoot, v, 0);
			self(self, rt);
		}
	};
	getRoot(getRoot, 1, 0);
	dfz(dfz, rt);

	std::cout << ans << '\n';
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