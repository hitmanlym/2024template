#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int n = opt<int>(1);
    int t = opt<int>(2);
    int q = opt<int>(3);
    int sum = opt<int>(4);
    std::vector<int> is(q + 1);

    int ti = 1;
    is[1] = 1;
    for (int i = 2; i <= q; i ++) {
        is[i] = rnd.next(n) % 2;
        if (is[i]) ti ++;
    }

    std::vector<int> n_list = rnd.partition(ti, sum, 2);

    vector<int> p(n);
    for (int i = 1; i < n; i++)
        p[i] = rnd.wnext(i, t);

    vector<int> perm = rnd.perm(n);

    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++)
        if (rnd.next(2))
            edges.push_back(make_pair(perm[i], perm[p[i]]));
        else
            edges.push_back(make_pair(perm[p[i]], perm[i]));

    shuffle(edges.begin(), edges.end());

    printf("%d %d\n", n, q);
    for (auto edge: edges) {
        printf("%d %d\n", edge.first + 1, edge.second + 1);
    }
    int cnt = 0;
    for (int i = 1; i <= q; i ++) {
        int op = is[i];
        if (op == 1) {
            printf("1 ");
        } else {
            printf("2 ");
        }
        if (op == 1) {
            int num = n_list[cnt ++];
            printf("%d ", num);
            int st = rnd.next(1, n - num + 1);
            for (int j = 0; j < num; j ++) {
                int it = perm[st + j - 1];
                if (it == 0) it = n;
                printf("%d", it);
                if (j < num - 1) {
                    printf(" ");
                } else {
                    printf("\n");
                }
            }
        } else {
            int l = rnd.next(1, cnt);
            int r = rnd.next(l, cnt);
            printf("%d %d\n", l, r);
        }
    }
}