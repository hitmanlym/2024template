#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;
/*
bool dfs(int x, int y, int z) {

}*/
void solve() {
    std::vector<int> a(3);

    int x = 0, y = 0;
    for (int i = 0; i < 3; i ++) {
        std::cin >> a[i];
        if (a[i] & 1) x ++;
        else y ++;
    }

    if (x && y) {
        std::cout << "YES\n";
    } else if (x) {
        std::cout << "NO\n";
    } else {
        int cnt = 0;
        while (! x) {
            x = 0, y = 0;
            for (int i = 0; i < 3; i ++) {
                a[i] /= 2;
                if (a[i] & 1) x ++;
                else y ++;
            }
            if (x) {
                if (y) {
                    std::cout << "YES\n";
                } else {
                    std::cout << "NO\n";
                }
            }
        }
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