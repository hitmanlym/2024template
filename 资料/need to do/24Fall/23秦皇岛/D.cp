#include<bits/stdc++.h>
using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<i64> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    std::vector<std::array<int, 2> > b(m);
    for (int i = 0; i < m; i ++) {
        std::cin >> b[i][0] >> b[i][1];
    }
    std::sort(b.begin(), b.end());
    int l = 1, now = 1;
    for (int i = 0; i < m; i ++) {
        int r = b[i][0], w = b[i][1];
        while (l <= r) {
            if (a[l] < a[now]) {
                now = l;
            }
            l ++;
        }
        a[now] -= w;
    }
    std::priority_queue<i64, std::vector<i64>, std::greater<i64> > q;
    for (int i = 1; i <= n; i ++) {
        q.push(a[i]);
    }
    i64 ans = 0;
    for (int i = 1; i <= n; i ++) {
        ans += q.top();
        q.pop();
        std::cout << ans << ' ';
    }
    std::cout << '\n';
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