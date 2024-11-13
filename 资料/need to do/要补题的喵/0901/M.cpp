#include<bits/stdc++.h>
using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::array<int, 2> > a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i][0] >> a[i][1];
    }
    int l = 1, r = 1e9, ans;
    auto check = [&](int x) -> bool {
        std::vector<int> b(n + 1);
        int need = (n + 1) / 2; // 
        for (int i = 1; i <= n; i ++) {
            if (a[i][0] >= x) {
                need --;
            }
            if (a[i][0] < x && a[i][1] >= x) b[i] = 1;
            if (a[i][0] >= x && a[i][1] >= x) b[i] = 0;
            if (a[i][0] >= x && a[i][1] < x) b[i] = -1;
        }
        if (need <= 0) return true;
        int min = 0, sum = 0;
        for (int i = 1; i <= n; i ++) {
            sum += b[i];
            if (sum - min >= need) {
                return true;
            }
            min = std::min(min, sum); 
        }
        return false;
    };
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    std::cout << ans << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}