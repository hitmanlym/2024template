#include<bits/stdc++.h>
using i64 = long long;

#define int i64
const int mod = 1e9 + 7;

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
            a[x] = std::max(a[x], v);
        }
    }
    void add(int x, int y, int v) {
        add(x, v), add(y + 1, -v);
    }
    int sum(int x) {
        int ans = 0;
        for (; x; x -= x & -x) {
            ans = std::max(a[x], ans);
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
    std::vector<int> a(n + 1), pos(n + 1);
    for (int i = 1; i <= n; i ++) {
        int x;
        std::cin >> x;
        pos[x] = i;
    } 
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }

    std::vector<int> dp(n + 1);
    Fenwick t(n);
    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        int q = t.sum(pos[a[i]] - 1);
        dp[i] = q + 1;
        t.add(pos[a[i]], dp[i]);
        ans = std::max(ans, dp[i]);
    }
    std::cout << ans << '\n';
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