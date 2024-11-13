#include<bits/stdc++.h>
using i64 = long long;
using pii = std::array<int, 2>;
void solve() {
    std::string s;
    int n, a, b;
    std::cin >> n >> a >> b >> s;
    pii cnt = {0, 0};
    cnt[s[0] - '0'] ++;
    std::vector<std::vector<int> > to(20, std::vector<int>(n + 1));
    std::vector<std::vector<pii> > w(20, std::vector<pii>(n + 1));
    for (int i = 0, j = 0; i < n; i ++) {
        while (std::max(cnt[0], cnt[1]) < a) {
            j = (j + 1) % n;
            cnt[s[j] - '0'] ++;
        }
        to[0][i] = (j + 1) % n;
        w[0][i] = (cnt[0] == a ? (pii){0, 1} : (pii){1, 0});

        cnt[s[i] - '0'] --;
    }
    auto get = [&](pii a, pii b) -> pii {
        pii c = {a[0] + b[0], a[1] + b[1]};
        return c;
    };
    for (int j = 1; j < 20; j ++) {
        for (int i = 0; i < n; i ++) {
            to[j][i] = to[j - 1][to[j - 1][i]];
            w[j][i] = get(w[j - 1][i], w[j - 1][to[j - 1][i]]);
        }
    }
    for (int i = 0; i < n; i ++) {
        int pos = i;
        pii cur = {0, 0};
        for (int j = 19; j >= 0; j --) {
            pii it = get(cur, w[j][pos]);
            if (std::max(it[0], it[1]) < b) {
                cur = it;
                pos = to[j][pos];
            }
        }
        cur = get(cur, w[0][pos]);
        if (cur[0] == b) {
            std::cout << 1;
        } else {
            std::cout << 0;
        }
    }
    std::cout << '\n';
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}