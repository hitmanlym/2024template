#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
#include<map>
using i64 = long long;

void solve() {
    int n, x, k;
    std::cin >> n >> x >> k;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    i64 sum = 0, heap = 0;
    std::priority_queue<int, std::vector<int>, std::greater<int> > q;
    int ans = k;
    for (int i = 1; i <= k; i ++) {
        sum += a[i];
        q.push(a[i]);
    }
    heap = sum;
    for (int i = k + 1; i <= n; i ++) {
        sum += a[i];
        if (q.size() && a[i] > q.top()) {
            heap -= q.top();
            heap += a[i];
            q.pop();
            q.push(a[i]);
        }
        if (sum - heap < x) {
            ans = i;
        } else {
            break;
        }
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