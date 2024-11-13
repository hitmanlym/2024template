#include <bits/stdc++.h>
using i64 = long long;

const int N = 2e3 + 10; // 换根
const int inf = 1e9 + 7;
struct Gravity {
    struct {
        int to, nxt;
    } e[N];
    int h[N], num;
    void addEdge(int a, int b) {
        e[++ num] = {b, h[a]}; h[a] = num;
        e[++ num] = {a, h[b]}; h[b] = num;
    }
    int n, siz[N], f[N];
    Gravity(int n) : n(n) {}
    int dfs1(int u, int p, int dp) {
        siz[u] = 1;
        int res = dp;
        for (int i = h[u]; i; i = e[i].nxt) {
            if (e[i].to == p) continue;
            res += dfs1(e[i].to, u, dp + 1);
            siz[u] += siz[e[i].to];
        }
        return res;
    }
    void dfs2(int u, int p) {
        for (int i = h[u]; i; i = e[i].nxt) {
            if (e[i].to == p) continue;
            f[e[i].to] = f[u] + (n - siz[e[i].to]) - siz[e[i].to]; 
            dfs2(e[i].to, u);
        }
    }
    std::array<int, 2> work() {
        f[1] = dfs1(1, 0, 0); //use the deep
        dfs2(1, 0);
        int ans = inf, ansid = inf;
        for (int i = 1; i <= n; i ++) {
            if (f[i] < ans) {
                ans = f[i], ansid = i;
            }
        }
        return {ansid, ans}; // ans 是各点到重心的距离之和， i64 安排
        // 注意 inf 变大， 否则 RE -> ansid 
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    Gravity g(n);
    for (int i = 1; i < n; i ++) {
        int x, y;
        std::cin >> x >> y;
        g.addEdge(x, y);
    }
    auto it = g.work();
    std::cout << it[0] << ' ' << it[1] << '\n';
	return 0;
}
