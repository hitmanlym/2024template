#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
#include<map>
#include<numeric>
#include<chrono>
#include<random>
using i64 = long long;
using ull = unsigned long long;
std::mt19937_64 rng(std::random_device{}()); // 好像 _64 更快
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
    int n, m, d, k;
    std::cin >> n >> m >> d >> k;
    d ++;
    DSU dsu(n);
    for (int i = 1; i <= m; i ++) {
        int u, v;
        std::cin >> u >> v;
        dsu.merge(u, v);
    }
    std::vector<ull> ha(n + 1); // 
    std::vector<ull> val(d + 1); // every layer
    std::map<ull, i64> cnt;
    i64 ans = 0;
    for (int i = 1; i <= d; i ++) {
        val[i] = rng();
    }
    std::vector<std::vector<std::vector<int> > > 
        r(d + 1, std::vector<std::vector<int> >(n + 1)); // d, rooted_n -> ...
    std::vector<std::vector<int> > rt(d + 1, std::vector<int>(n + 1));
    for (int i = 1; i <= n; i ++) {
        int f = dsu.find(i);
        for (int j = 1; j <= d; j ++) {
            ha[i] ^= 1ull * f * val[j];
        }
    }
    for (int i = 1; i <= d; i ++) {
        for (int j = 1; j <= n; j ++) { // 
            int rf = dsu.find(j);

            rt[i][j] = rf;
            r[i][rf].push_back(j);
        }
    }
    auto add = [&](ull x) {
        ans += cnt[x];
        cnt[x] ++;
    };
    auto del = [&](ull x) {
        cnt[x] --;
        ans -= cnt[x];
    };
    for (int i = 1; i <= n; i ++) {
        add(ha[i]);
    }
    for (int i = 1; i <= k; i ++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u = rt[w][u], v = rt[w][v];
        if (u == v) {
            std::cout << ans << '\n';
            continue;
        }
        if (r[w][u].size() < r[w][v].size()) {
            std::swap(u, v);
        }
        for (auto it : r[w][v]) {
            r[w][u].push_back(it);
            rt[w][it] = u;
            del(ha[it]);
            ha[it] ^= 1ull * v * val[w];
            ha[it] ^= 1ull * u * val[w];
            add(ha[it]);
        }
        std::cout << ans << '\n';
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}