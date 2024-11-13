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
	int n;
	std::cin >> n;
	//std::vector<int> a(n + 1);
	std::vector<std::vector<int> > d(n + 1);
	for (int i = 1; i <= n; i ++) {
		int x;
		std::cin >> x;
		for (int j = 1; j * j <= x; j ++) {
			if (x % j == 0) {
				d[j].push_back(x);
				if (x / j != j) {
					d[x / j].push_back(x);
				}
			}
		}
	}
	Fenwick t(n);
	std::vector<int> dp(n + 1);
	for (int i = n; i >= 1; i --) {
		for (int j = 0; j < d[i].size(); j ++) {
			//std::cout << d[i][j] << ' ';
			dp[i] += t.rangeSum(d[i][j] + 1, n);
			t.add(d[i][j], 1);
		}
		//std::cout << '\n';
		for (int j = i + i; j <= n; j += i) {
			dp[i] -= dp[j];
		}
		for (int j = 0; j < d[i].size(); j ++) {
			t.add(d[i][j], -1);
		}
		//std::cout << dp[i] << '\n';
	}
	std::cout << dp[1] << '\n';
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