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
    int n, m;
    std::cin >> n >> m;
    std::vector<std::array<int, 2> > cla(n + 1), stu(m + 1);
    std::vector<std::array<int, 2> > p;
    for (int i = 1; i <= n; i ++) {
        std::cin >> cla[i][0] >> cla[i][1];
        p.push_back({cla[i][0], 2});
        p.push_back({cla[i][1], 0});
    }
    for (int i = 1; i <= m; i ++) {
        std::cin >> stu[i][0] >> stu[i][1];
        p.push_back({stu[i][0], 3});
        p.push_back({stu[i][1], 1});
    } 
    std::sort(p.begin(), p.end());
    bool f = 1;
    int state_cla = 0, state_stu = 1, last_op = 0, be = 0;
    for (auto it : p) {
        int op = it[1], t = it[0];
        if (op == 0) {
            if (last_op < t) {
                f = 0;
            }
            state_cla = 0;
        } else if (op == 1) {
            state_stu = 1;
            last_op = t + 2 * (t - be);
        } else if (op == 2) {
            state_cla = 1;
        } else if (op == 3) {
            state_stu = 0;
            be = t;
        }
        if (state_cla && ! state_stu) {
            f = 0;
        }
    }
    if (f) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
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