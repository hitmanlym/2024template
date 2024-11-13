#include<bits/stdc++.h>
using i64 = long long;
using pii = std::array<int, 2>;
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n + 1), b(m + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= m; i ++) {
        std::cin >> b[i];
    }
    std::sort(a.begin() + 1, a.end());
    std::sort(b.begin() + 1, b.end());
    std::priority_queue<pii, std::vector<pii>, std::greater<pii> > fuck;
    int need = 0;
    for (int i = n - m + 1; i <= n; i ++) {
        //fuck.push_back()
        if (a[i] > b[i - (n - m)]) {
            //std::cout << "###\n";
            std::cout << -1 << '\n';
            return ;
        } else {
            need += b[i - (n - m)] - a[i];
        }
        fuck.push({a[i], i});
    }
    std::priority_queue<int, std::vector<int>, std::greater<int> > q;
    for (int i = 1; i <= n - m; i ++) {
        q.push(a[i]);
    }
    if (n - m < need) {
        //std::cout << "!!!\n";
        std::cout << -1 << '\n';
        return ;
    }
    std::vector<int> ans;
    int op = 0;
    int l = n - m + 1;
    for (int i = 1; i <= n - m - need; i ++) {
        //std::cout << q.top() << ' ' << "***\n";
        int u = q.top();
        q.pop();
        ans.push_back(u);
        //std::cout << "!!! " << u << '\n';
        if (u == fuck.top()[0]) { // 与极小一致
            need --;
            auto it = fuck.top();
            fuck.pop();
            it[0] ++;
            if (it[0] > b[it[1] - (n - m)]) {
                std::cout << -1 << '\n';
                return ;
            }
            fuck.push(it);
            continue;
        }
        q.push(u + 1);
        q.pop();
    }
    
    int max = 0;
    while (q.size()) {
        max = q.top();
        q.pop();
    }
    if (max > b[1]) {
        //std::cout << "???\n";
        std::cout << -1 << '\n';
        return ;
    }
    while (fuck.size()) {
        auto it = fuck.top();
        a[it[1]] = it[0];
        fuck.pop();
    }
    for (int i = n - m + 1; i <= n; i ++) {
        for (int j = a[i]; j < b[i - (n - m)]; j ++) {
            ans.push_back(j);
        }
    }
    std::cout << ans.size() << '\n';
    if (ans.size()) {
        for (auto it : ans) {
            std::cout << it << ' ';
        }
        std::cout << '\n';
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