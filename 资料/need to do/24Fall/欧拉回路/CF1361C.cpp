#include<bits/stdc++.h>
using i64 = long long;
using pii = std::array<int, 2>;
struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n + 1);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};
void solve() {
    int n;
    std::cin >> n;
    std::vector<pii> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i][0] >> a[i][1];
    }
    auto check = [&](int b) -> bool {
        int lim = (1 << b) - 1;
        std::vector<std::vector<int> > e(lim + 1);
        DSU d(lim);
        int num1 = 0, num2 = 0;
        for (int i = 1; i <= n; i ++) {
            int u = a[i][0] & lim, v = a[i][1] & lim;
            e[u].push_back(v);
            e[v].push_back(u);
            if (d.merge(u, v)) {
                num1 ++;
            }
        }
        for (int i = 0; i <= lim; i ++) {
            if (e[i].size() & 1) {
                return false;
            }
            if (e[i].size()) {
                num2 ++;
            }
        }
        if (num1 + 1 != num2) {
            return false;
        }
        return true;
    };
    int l = 0, r = 20, ans;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    std::cout << ans << '\n';

    std::vector<std::vector<std::array<int, 4> > > E(1 << ans);
    std::vector<int> cur(1 << ans), res;
    std::vector<bool> vis(n + 1);
    ans = (1 << ans) - 1;
    for (int i = 1; i <= n; i ++) {
        int u = a[i][0] & ans, v = a[i][1] & ans;
        E[u].push_back({v, 2 * i - 1, 2 * i, i});
        E[v].push_back({u, 2 * i, 2 * i - 1, i});
    }
    auto dfs = [&](auto self, int u) -> void {
        for (int &i = cur[u]; i < E[u].size(); ) {
            auto it = E[u][i ++];
            int v = it[0], x = it[1], y = it[2], id = it[3];
            if (! vis[id]) {
                vis[id] = 1;
                self(self, v);
                res.push_back(y);
                res.push_back(x);
            }
        }   
    };
    dfs(dfs, (a[1][0] & ans));
    //std::reverse(res.begin(), res.end());
    for (auto it : res) {
        std::cout << it << ' ';
    }
    std::cout << '\n';
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