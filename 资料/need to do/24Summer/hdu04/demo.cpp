#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
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
            a[x] = std::max(a[x], v);
        }
    }
    int sum(int x) {
        int ans = 0;
        for (; x; x -= x & -x) {
            ans = std::max(ans, a[x]);
        }
        return ans;
    }
};
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::array<int, 2> > a(n + 1), y(m + 1), op(n + 1);
    std::vector<std::vector<int> > st(n + 1), ed(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i][0] >> a[i][1];
    }
    for (int i = 1; i <= m; i ++) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        st[x1].push_back(i);
        ed[x2].push_back(i);
        y[i] = {y1, y2};
    }
    std::vector<int> ans(m + 1);
    std::vector<std::array<int, 4> > mem(m + 1);
    Fenwick t(n);

    t.init(n);
    for (int i = 1; i <= n; i ++) {
        for (auto j : st[i]) {
            mem[j][0] += t.sum(y[j][1]);
        }
        op[i][0] = t.sum(a[i][0]) + a[i][1];
        t.add(a[i][0], op[i][0]);
        for (auto j : ed[i]) {
            mem[j][1] += t.sum(y[j][0] - 1);
        }
    }

    t.init(n);
    for (int i = n; i >= 1; i --) {
        for (auto j : ed[i]) {
            mem[j][1] += t.sum(n - y[j][0] + 1);
        }
        op[i][1] = t.sum(n - a[i][0] + 1) + a[i][1];
        t.add(n - a[i][0] + 1, op[i][1]);
        for (auto j : st[i]) {
            mem[j][0] += t.sum(n - y[j][1] + 1 - 1);
        }
    }
    
    std::vector<int> use(n + 1);
    for (int i = 1; i <= n; i ++) {
        use[i] = op[i][0] + op[i][1] - a[i][1];
    }

    t.init(n);
    for (int i = 1; i <= n; i ++) {
        for (auto j : st[i]) {
            mem[j][2] += t.sum(n - y[j][1] + 1 - 1);
        }
        t.add(n - a[i][0] + 1, use[i]);
    }

    t.init(n);
    for (int i = n; i >= 1; i --) {
        for (auto j : ed[i]) {
            mem[j][3] += t.sum(y[j][0] - 1);
        }
        t.add(a[i][0], use[i]);
    }

    for (int i = 1; i <= m; i ++) {
        for (int j = 0; j < 4; j ++) {
            ans[i] = std::max(ans[i], mem[i][j]);
        }
        std::cout << ans[i] << '\n';
    }
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