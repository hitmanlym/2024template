#include "testlib.h"

#include <vector>
#include <array>

using namespace std;

int main(int argc, char *argv[]) { // 输入 n --> 
    registerGen(argc, argv, 1);
    int n = opt<int>(1);
    int LIM1 = opt<int>(2);
    int LIM2 = opt<int>(3);

    vector<int> perm = rnd.perm(n);
    std::vector<std::array<int, 2> > e;
    std::vector<int> to(n + 1), from(n + 1);

    for (int i = 0, end = perm.size(); i < end; i ++) {
        for (int j = i + 1; j < end; j ++) {
            if (rnd.next() < 0.5) {
                e.push_back({perm[i], perm[j]});
                from[perm[i]] ++;
                to[perm[j]] ++;
            }
        }
    }
    for (int i = 1, end = perm.size(); i < end; i ++) {
        if (to[perm[i]] == 0) {
            int u = perm[rnd.next(0, i - 1)];
            e.push_back({u, perm[i]});
            from[u] ++;
            to[perm[i]] ++;
        }
    }

    int m = e.size();
    printf("%d %d\n", n, m);
    for (int i = 1; i <= m; i ++) {
        printf("%d %d\n", e[i - 1][0] + 1, e[i - 1][1] + 1);
    }
    std::vector<int> it(n + 1);
    for (int i = 1; i <= n; i ++) {
        it[i] = rnd.next(1, LIM1);
        printf("%d", it[i]);
        if (i < n) printf(" ");
        else printf("\n");
    }
    std::vector<int> op(n + 1), mini(n + 1);
    for (int i = 0; i < m; i ++) {
        mini[e[i][1]] = std::max(mini[e[i][1]], it[e[i][0]]);
    }

    int before = 0;
    for (int i = 1; i <= n; i ++) { // 大于 max 前
        if (rnd.next() > 0.2) {
            op[perm[i - 1] + 1] = std::max(before + i * i / rnd.next(1, i), std::min(rnd.next(1, LIM2), i * i * 10));
        } else {
            op[perm[i - 1] + 1] = std::min(rnd.next(1, LIM2), i * i * 10);
        }
        op[perm[i - 1] + 1] = std::max(op[perm[i - 1] + 1], mini[perm[i - 1] + 1] + 1);
        before = std::max(before, op[perm[i - 1] + 1]);
    }
    for (int i = 1; i <= n; i ++) {
        printf("%d", std::max(op[i], it[i] + 1));
        if (i < n) printf(" ");
        else printf("\n");
    }
    int select = 1;
    for (int i = 1; i * i <= n; i ++) {
        int o = rnd.next(1, n);
        if (op[o] > op[select]) {
            select = o;
        }
    }
    printf("%d\n", select);
}