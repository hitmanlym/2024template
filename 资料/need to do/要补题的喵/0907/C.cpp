#include<bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
struct Fenwick {
    int n;
    std::vector<u64> a;

    Fenwick(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        a.resize(n + 1);
        a.assign(n + 1, 0);
    }
    void add(int x, u64 v) {
        /*std::cout << "ADD : " << x << '\n';
        return ;*/
        for (; x <= n; x += x & -x) {
            a[x] += v;
        }
    }
    u64 sum(int x) {
        /*std::cout << "SUM : 1-x : " << x << '\n';
        return 0;*/
        assert(x >= 1 && x <= n);
        u64 ans = 0;
        for (; x; x -= x & -x) {
            ans += a[x];
        }
        return ans;
    }
    u64 rangeSum(int l, int r) {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
};
const int LIM = 1e6 + 10;
void solve() {
    int n;
    std::cin >> n;
    std::vector<Fenwick> bit(3);
    for (int i = 0; i < 3; i ++) {
        bit[i].init(LIM);
    }    std::vector<std::vector<int> > e(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    std::vector<int> siz(n + 1), son(n + 1), st(n + 1), ed(n + 1), node(n + 1); 
    std::vector<u64> ans(n + 1);
    int dfn = 0;
    u64 now_ans = 0;
    auto dfs1 = [&](auto self, int u, int p) -> void {
        st[u] = ++dfn;
        node[dfn] = u;
        siz[u] = 1;
        for (auto v : e[u]) {
            if (v == p) continue;
            self(self, v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) {
                son[u] = v;
            }
        }
        ed[u] = dfn;
    };  
    dfs1(dfs1, 1, 0);
    auto add = [&](int u) {
        //std::cout << "???? " << u << ' ' << a[u] << '\n';
        u64 val = a[u];
        now_ans += val * (bit[0].sum(val - 1) * val - bit[1].sum(val - 1));
        now_ans += bit[2].rangeSum(val + 1, LIM) - val * bit[1].rangeSum(val + 1, LIM);

        bit[0].add(val, 1);
        bit[1].add(val, val);
        bit[2].add(val, val * val);
    };
    auto del = [&](int u) {
        u64 val = a[u];
        now_ans -= val * (bit[0].sum(val - 1) * val - bit[1].sum(val - 1));
        now_ans -= bit[2].rangeSum(val + 1, LIM) - val * bit[1].rangeSum(val + 1, LIM);

        bit[0].add(val, -1);
        bit[1].add(val, -val);
        bit[2].add(val, -val * val);
    };
    auto dfs2 = [&](auto self, int u, int p, bool f) -> void {
        for (auto v : e[u]) {
            if (v == p || v == son[u]) continue;
            self(self, v, u, 0);
        }
        if (son[u]) {
            self(self, son[u], u, 1);
        }
        for (auto v : e[u]) {
            if (v == p || v == son[u]) continue;
            for (int j = st[v]; j <= ed[v]; j ++) {
                add(node[j]);
            }
        }
        add(u);
        ans[u] = now_ans;
        if (! f) {
            for (int i = st[u]; i <= ed[u]; i ++) {
                del(node[i]);
            }
        }
    };
    dfs2(dfs2, 1, 0, 0);

    u64 res = 0;
    for (int i = 1; i <= n; i ++) {
        res ^= 2ull * ans[i];
    }
    std::cout << res << '\n';
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