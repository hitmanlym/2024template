#include<cstdio>
#include<iostream>
#include<vector>
#include<array>
using i64 = long long;
using pii = std::array<int, 2>;
void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<pii> > e(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back({v, i});
        e[v].push_back({u, i});
    } 
    std::vector<int> fa(n + 1), dep(n + 1), ed(n + 1); 
    auto dfs = [&](auto self, int u, int p) -> void {
        dep[u] = dep[p] + 1;
        for (auto it : e[u]) {
            int v = it[0], id = it[1];
            if (v == p) continue;
            fa[v] = u;
            ed[v] = id;
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);
    std::vector<int> f(n + 1);
    for (int i = 1; i <= n; i ++) {
        f[i] = i;
    }
    auto get = [&](auto self, int x) -> int {
        if (f[x] == x) return x;
        return f[x] = self(self, f[x]);
    };
    std::vector<int> ans(n);
    auto check = [&](int x, int y, int g) -> void {
        //std::cout << x << ' ' << y << ' ' << g << '\n';
        for (x = get(get, x), y = get(get, y); x != y;) {
            //std::cout << "!!! " << x << ' ' << y << ' ' << dep[x] << ' ' << dep[y] << '\n';
            if (dep[x] < dep[y]) {
                std::swap(x, y);
            }
            ans[ed[x]] = g;
            f[x] = get(get, fa[x]);
            x = f[x];
            //std::cout << ">>> " << x << ' ' << y << '\n';
            return ;
        }
    };
    for (int i = n / 2; i >= 1; i --) {
        for (int j = i * 2; j <= n; j += i) {
            check(i, j, i);
        }
    }
    for (int i = 1; i < n; i ++) {
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    //int size(256<<20); //256M
    //__asm__ ( "movq %0, %%rsp\n"::"r"((char*)malloc(size)+size));
    int t = 1;
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}