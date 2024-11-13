#include <bits/stdc++.h>
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

signed main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    std::vector<int> pos(n + 1), pre(n + 1);
    for (int i = 1; i <= n; i ++) {
        pre[i] = pos[a[i]];
        pos[a[i]] = i;
    }
    Fenwick t(n);

    std::vector<int> ans(q);
    std::vector<std::vector<std::array<int, 2>> > e(n + 1);
    for (int i = 0; i < q; i ++) {
        int u, v;
        std::cin >> u >> v;
        e[v].push_back({u, i});
    }
    for (int i = 1; i <= n; i ++) {
        int u = pre[i];
        if (u) {
            t.add(u, -1);
        }
        t.add(i, 1);
        for (auto it : e[i]) {
            int l = it[0], id = it[1];
            ans[id] = t.rangeSum(l, i);
        }
    }
    for (int i = 0; i < q; i ++) {
        std::cout << ans[i] << '\n';
    }
    return 0;
}