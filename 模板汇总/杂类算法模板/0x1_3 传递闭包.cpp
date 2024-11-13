#include <bits/stdc++.h>
using i64 = long long;
const int N = 2e5 + 10;
std::bitset<110> a[110];
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            int x;
            std::cin >> x;
            a[i][j] = x;
        }
    }
    for (int j = 1; j <= n; j ++ ) { // 枚举中间量, 参考floyed,dp
        for (int i = 1; i <= n; i ++) {
            if (a[i][j]) a[i] |= a[j];
        }
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            std::cout << a[i][j] << ' ';
        }
        std::cout << '\n';
    }
	return 0;
}
