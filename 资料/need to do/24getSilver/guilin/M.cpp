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
	std::vector<int> a(n + 1); // permutation
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	std::deque<int> q;
	Fenwick t(n);
	int ans = 0, total = n * (n - 1) / 2;
	for (int i = 1; i <= n; i ++) {
		q.push_back(a[i]);
		ans += t.rangeSum(a[i], n);
		t.add(a[i], 1);
	}
	int f = 0;
	std::cout << ans << '\n';
	for (int i = 1; i <= m; i ++) {
		char c;
		std::cin >> c;
		if (c == 'S') {
			if (f == 0) {
				int u = q.front();
				q.pop_front();
				q.push_back(u);
				ans -= u - 1;
				ans += n - u;
			} else {
				int u = q.back();
				q.pop_back();
				q.push_front(u);
				ans -= u - 1;
				ans += n - u;
			}
		} else {
			f ^= 1;
			ans = total - ans;
		}std::cout << ans % 10;
	}
	std::cout << '\n';
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