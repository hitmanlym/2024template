#include<bits/stdc++.h>
using i64 = long long;

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
            a[x] ^= v;
        }
    }
    int sum(int x) {
        int ans = 0;
        for (; x; x -= x & -x) {
            ans ^= a[x];
        }
        return ans;
    }
};

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), sum(n + 1), pos(n + 1);
	//std::map<int, int> mp;
	std::vector<int> v;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		v.push_back(a[i]);
		sum[i] = (sum[i - 1] ^ a[i]);
	}

	// 离散化
	std::sort(v.begin(), v.end());
	v.erase(std::unique(v.begin(), v.end()), v.end());
	int siz = v.size();
	std::vector<int> pre(siz + 1);
	for (int i = 1; i <= n; i ++) {
		int p = std::lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
		pos[i] = pre[p];
		pre[p] = i;
	}

	int m;
	std::cin >> m;
	std::vector<std::array<int, 3> > e(m);
	std::vector<int> ans(m + 1);
	for (int i = 0; i < m; i ++) {
		std::cin >> e[i][0] >> e[i][1];
		e[i][2] = i + 1;
	}
	std::sort(e.begin(), e.end(), [&](auto x, auto y) {
		return x[1] < y[1] || x[1] == y[1] && x[0] < y[0];
	});
	Fenwick t(n);

	int it = 0;
	for (int i = 0; i < m; i ++) {
		int l = e[i][0], r = e[i][1], id = e[i][2];
		while (it < r) {
			it ++;
			if (pos[it]) {
				t.add(pos[it], a[it]);
			}
			t.add(it, a[it]);
		}
		ans[id] = (t.sum(r) ^ t.sum(l - 1)) ^ (sum[r] ^ sum[l - 1]);
	}
	for (int i = 1; i <= m; i ++) {
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