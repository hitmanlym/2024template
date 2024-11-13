#include <bits/stdc++.h>
using i64 = long long;
const int N = 1e6;
void solve() {
    int k;
    std::cin >> k;
    std::deque<std::array<int, 2> > d;
    d.push_back({1, 1});
    std::vector<bool> vis(k + 1);
    while (d.size()) {
        auto it = d.back();
        d.pop_back();
        int num = it[0], w = it[1];
        if (vis[num]) continue;
        vis[num] = 1;

        if (num == 0) {
            std::cout << w << '\n';
            return ;
        }
        d.push_back({num * 10 % k, w});
        d.push_front({(num + 1) % k, w + 1});
    }
}
int main() {
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
}