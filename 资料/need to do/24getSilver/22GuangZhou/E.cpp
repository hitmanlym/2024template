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
	std::cin >> n >> m;
	std::vector<std::array<int, 2> > a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i][0];
		a[i][1] = i;
	}
	std::sort(a.begin() + 1, a.end(), [&](auto x, auto y) {
		return x[0] < y[0] || x[0] == y[0] && x[1] < y[1];
	});

	Fenwick t(n);
	std::vector<int> ans(n + 1);
	// for (int i = n; i >= 1; i --) {
	// 	suf[i] = suf[i + 1] + a[i][0];
	// }
	int sum = 0;
	for (int i = 1; i <= n; i ++) {
		sum += a[i][0];
		ans[a[i][1]] = a[i][0] * i - sum + t.rangeSum(1, a[i][1]);
		t.add(a[i][1], 1);
	}
	for (int i = 1; i <= n; i ++) {
		if (ans[i] > m - 2) {
			ans[i] = -1;
		}
		std::cout << ans[i] << '\n';
	}
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