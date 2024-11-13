#include <bits/stdc++.h>
using i64 = long long;
const int inf = 1e9 + 7;
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n + 2, inf);
    std::vector<std::vector<int> > f(17, std::vector<int>(n + 1));
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
        f[0][i] = i;
    }
    auto cmp = [&](int x, int y) -> int {
        return a[x] > a[y] ? y : x;
    };
    for (int j = 1; j <= std::__lg(n); j ++) {
        for (int i = 1; i <= n; i ++) {
            if (i + (1 << j) - 1 > n) break;
            f[j][i] = cmp(f[j - 1][i], f[j - 1][i + (1 << j - 1)]);
        }
    }
    auto rmq = [&](int l, int r) -> int {
        int x = std::__lg(r - l + 1);
        return cmp(f[x][l], f[x][r - (1 << x) + 1]);
    };

    std::vector<int> st, pre(n + 2), suf(n + 2);
    st.push_back(0);
    for (int i = 1; i <= n; i ++) {
        while (st.size() > 1 && a[st.back()] > a[i]) {
            suf[st.back()] = i;
            st.pop_back();
        }
        pre[i] = st.back();
        st.push_back(i);
    }
    while (st.size() > 1) {
        int u = st.back();
        st.pop_back();
        pre[u] = st.back();
        if (st.size() > 1) suf[st.back()] = n + 1;
    }
    std::vector<i64> fr(n + 2), fl(n + 2), gr(n + 2), gl(n + 2);
    for (int i = 1; i <= n; i ++) {
        fr[i] = fr[pre[i]] + 1ll * a[i] * (i - pre[i]);
        gr[i] = gr[i - 1] + fr[i];
    }
    for (int i = n; i >= 1; i --) {
        fl[i] = fl[suf[i]] + 1ll * a[i] * (suf[i] - i);
        gl[i] = gl[i + 1] + fl[i];
    }
    for (int i = 1; i <= m; i ++) {
        int l, r;
        std::cin >> l >> r;
        int p = rmq(l, r);
        i64 ans = 1ll * a[p] * (p - l + 1) * (r - p + 1) + 
                  gr[r] - gr[p] - fr[p] * (r - p) + 
                  gl[l] - gl[p] - fl[p] * (p - l);
        std::cout << ans << '\n';
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t--) {
        solve();
    }
}