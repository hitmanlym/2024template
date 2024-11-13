#include<bits/stdc++.h>
using i64 = long long;

const int mod = 1e6 + 7;

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
            a[x] = std::max(a[x], v); // 改成维护最大值。
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

    int query(int x) {
    	int res = 0;
    	for (; x; x -= x & -x) {
    		res = std::max(res, a[x]);
    	}
    	return res;
    }
};

const int N = 5e4 + 10;
void solve() {
	int n, o;
	std::vector<int> a;
	while (std::cin >> o) {
		a.push_back(o);
	}
	n = a.size();
	a.push_back(0);
	for (int i = n; i >= 1; i --) {
		a[i] = a[i - 1];
	}
	std::vector<int> f(n + 1), g(n + 1);

	Fenwick x(N), y(N);
	for (int i = 1; i <= n; i ++) {
		int q;
		q = x.query(a[n - i + 1]);
		x.add(a[n - i + 1], q + 1);
		f[n - i + 1] = q + 1;

		q = y.query(a[i] - 1); // Dilworth 定理， 偏序中，
			// 最大反链的元素数目 = 最少链划分的数目
			// 序列最长上升子序列的长度 = 最少单调不上升子序列的个数
		y.add(a[i], q + 1);
		g[i] = q + 1;
	}

	int ans1 = 0, ans2 = 0;
	for (int i = 1; i <= n; i ++) {
		ans1 = std::max(ans1, f[i]);
		ans2 = std::max(ans2, g[i]);
	}
	std::cout << ans1 << '\n' << ans2 << '\n';
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