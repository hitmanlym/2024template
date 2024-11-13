#include<iostream>
#include<array>
#include<vector>
#include<set>
using i64 = long long;
const int mod1 = 998244353, mod2 = 1e9 + 7;
struct Hasher {
    i64 x, y;
    Hasher(const int& X = 0, const int& Y = 0) {
        x = X, y = Y;
    }
    i64 val(void) {
        return ((1ll * x) << 31ll) |  (1ll * y);
    }
    friend Hasher operator + (const Hasher& A, const Hasher& B) {
        return Hasher((A.x + B.x) % mod1, (A.y + B.y) % mod2);
    }
    friend Hasher operator - (const Hasher& A, const Hasher& B) {
        return Hasher((A.x - B.x + mod1) % mod1, (A.y - B.y + mod2) % mod2);
    }
    friend Hasher operator * (const Hasher& A, const Hasher& B) {
        return Hasher(1ll * A.x * B.x % mod1, 1ll * A.y * B.y % mod2);
    }
};
const Hasher seed = (31, 1331);
const int N = 5e5 + 10;
int s[N][2], t[N][2], f[21][N], n, m, cnt[N];
std::set<std::array<i64, 2> > pick;
Hasher pw[N], ha[N];
void pre(int u, Hasher now, int deep) {
    if (t[u][0] == 1 && t[u][1] == 1) {
        pick.insert({now.val(), deep});
    }
    if (t[u][0] != 1) {
        pre(t[u][0], now * seed + Hasher(0, 0), deep + 1);
    }
    if (t[u][1] != 1) {
        pre(t[u][1], now * seed + Hasher(1, 1), deep + 1);
    }
}
void dfs(int u, Hasher now, int deep) {
    ha[u] = now;
    for (auto it : pick) {
        i64 val = it[0], len = it[1];
        if (deep < len) continue;
        int v = u;
        for (int j = 20; j >= 0; j --) {
            if (len >> j & 1) {
                v = f[j][v];
            }
        }
        i64 get = (ha[u] - ha[v] * pw[len]).val();
        if (get == val) {
            cnt[v] ++;
        }
    }
    if (s[u][0] != 1) {
        dfs(s[u][0], now * seed + Hasher(0, 0), deep + 1);
    }   
    if (s[u][1] != 1) {
        dfs(s[u][1], now * seed + Hasher(1, 1), deep + 1);
    }
}
void solve() {
    pick.clear();
    std::cin >> n;
    for (int i = 1; i <= n; i ++) {
        cnt[i] = 0;
    }
    for (int i = 1; i <= n; i ++) {
        std::cin >> s[i][0] >> s[i][1];
        s[i][0] ++;
        s[i][1] ++;
        if (s[i][0] != 1) {
            f[0][s[i][0]] = i;
        }
        if (s[i][1] != 1) {
            f[0][s[i][1]] = i;
        }
    }
    for (int j = 1; j <= 20; j ++) {
        for (int i = 1; i <= n; i ++) {
            f[j][i] = f[j - 1][f[j - 1][i]];
        }
    }
    std::cin >> m;
    for (int i = 1; i <= m; i ++) {
        std::cin >> t[i][0] >> t[i][1];
        t[i][0] ++;
        t[i][1] ++;
    }
    pre(1, Hasher(0, 0), 0);
    dfs(1, Hasher(0, 0), 0);
    std::vector<int> ans;
    for (int i = 1; i <= n; i ++) {
        if (cnt[i] == pick.size()) {
            ans.push_back(i - 1);
        }
    }
    std::cout << ans.size() << '\n';
    for (auto it : ans) {
        std::cout << it << ' ';
    }
    std::cout << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    freopen("1008.in","r",stdin);
    // freopen("me.out","w",stdout);
    int t = 1;
    std::cin >> t;
    pw[0] = (1, 1);
    for (int i = 1; i < N; i ++) {
        pw[i] = pw[i - 1] * seed;
    }
    while (t --) {
        solve();
    }
    return 0;
}