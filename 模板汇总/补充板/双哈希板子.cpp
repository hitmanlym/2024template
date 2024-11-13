#include<bits/stdc++.h>
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
const Hasher seed = (31, 131);
void solve() {
    std::string s, t;
    std::cin >> s >> t;
    int n = s.size(), m = t.size();
    s = "#" + s + s, t = "#" + t;
    std::vector<Hasher> pw(2 * n + 1), h(std::max(2 * n + 1, m + 1));
    pw[0] = Hasher(1, 1);
    for (int i = 1; i <= 2 * n; i ++) {
        pw[i] = pw[i - 1] * seed;
    }
    for (int i = 1; i <= 2 * n; i ++) {
        h[i] = h[i - 1] * seed + Hasher(s[i] - 'A', s[i] - 'A');
    }
    std::set<i64> exist;
    auto getHash = [&](int l, int r) -> Hasher {
        return h[r] - h[l - 1] * pw[r - l + 1];
    };
    for (int i = 1; i <= n; i ++) {
        exist.insert(getHash(i, i + n - 1).val());
    }
    for (int i = 1; i <= m; i ++) {
        h[i] = h[i - 1] * seed + Hasher(t[i] - 'A', t[i] - 'A');
    }
    i64 ans = 0;
    for (int i = 1; i <= m - n + 1; i ++) {
        ans += exist.count(getHash(i, i + n - 1).val());
    }
    std::cout << ans << '\n';
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