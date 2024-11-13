#include <bits/stdc++.h>
using i64 = long long;
#define int i64
signed main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    int ans = 0;
    std::priority_queue<int, std::vector<int>, std::greater<int> > q;
    for (int i = 1; i <= n; i ++) {
        int x;
        std::cin >> x;
        if (q.size() && q.top() < x) {
            ans += x - q.top();
            q.pop();
            q.push(x);
        }
        q.push(x);
    }
    std::cout << ans << '\n';
    return 0;
}