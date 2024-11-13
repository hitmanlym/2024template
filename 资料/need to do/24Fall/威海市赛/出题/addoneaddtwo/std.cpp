#include <bits/stdc++.h>
using i64 = long long;
void solve() {
    int n, x, y;
    std::cin >> n >> x >> y;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    std::sort(a.begin() + 1, a.end());

    auto check = [&](int op) -> bool {
        int Y = y, X = x;
        for (int i = n / 2 + 1; i <= n; i ++) {
            if (a[i] >= op) break;
            // 需要 op - a[i], 优先用 2 去填充
            int y_need = (op - a[i]) / 2;
            if (X && Y) {
                X -= ((op - a[i]) & 1);
                if (Y >= y_need) {
                    Y -= y_need;
                } else {
                    y_need -= Y;
                    Y = 0;
                    if (X >= 2 * y_need) {
                        X -= 2 * y_need;
                    } else {
                        return false;
                    }
                }
            } else if (Y) {
                y_need += ((op - a[i]) & 1);
                if (Y >= y_need) {
                    Y -= y_need;
                } else {
                    return false;
                }
            } else if (X) {
                if (X >= op - a[i]) {
                    X -= op - a[i];
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } 
        return true;
    };

    int l = 0, r = 2e9, ans;
    while (l <= r) {
        int mid = 1ll * l + r >> 1;
        if (check(mid)) {
            l = mid + 1;
            ans = mid;
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
    std::cin >> t;
    while (t --) {
        solve();
    }
}