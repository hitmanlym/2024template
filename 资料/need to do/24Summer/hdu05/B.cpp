#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<numeric>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;
int get(int a, int b) {
    return a % b == 0 ? b : get(b, a % b);
}
void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    std::sort(a.begin() + 1, a.end());
    int ans = n + 1;
    //if (a[1] == 1) ans = std::min(ans, n - 1); 
    
    for (int i = 1; i <= n; i ++) {
        for (int j = i + 1; j <= n; j ++) {
            if (a[j] % a[i] == 1) ans = std::min(ans, n);
        }
    }
    int num = 0, gcd = 0;
    for (int i = 2; i <= n; i ++) {
        if (a[i] % a[1] == 0) num ++;
        else gcd = get(gcd, a[i]);
    }
    if (num == n - 1) ans = std::min(ans, n - 1);
    //if (num == n - 2) ans = std::min(ans, n);
    if (gcd >= a[1]) {
        ans = std::min(ans, n);
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = i + 1; j <= n; j ++) {
            int m = a[j] % a[i];
            if (m == 0) continue;
            int num = 0;
            for (int k = 1; k <= n; k ++) {
                if (k == j || a[k] < m) continue;
                if (a[k] % m == 0) num ++;
            }
            if (num == n - 1) ans = std::min(ans, n);
        }
    }

    std::cout << ans << '\n';
    // 模出的数 
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