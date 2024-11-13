#include <bits/stdc++.h>
#include "testlib.h"
 
using i64 = long long;
 
const int N = 2e5;
 
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N, "n");
    inf.readSpace();
    int q = inf.readInt(1, N, "q");
    inf.readEoln();
    for (int i = 1; i < n; i ++) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();
    }
    int cnt = 0;
    for (int i = 1; i <= q; i ++) {
        int op = inf.readInt(1, 2, "o");
        inf.readSpace();
        if (op & 1) {
            int num = inf.readInt(1, n, "m");
            inf.readSpace();
            for (int i = 1; i <= num; i ++) {
                int it = inf.readInt(1, n, "i");
                if (i < num) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
            ++ cnt;
        } else {
            int l = inf.readInt(1, cnt, "l");
            inf.readSpace();
            int r = inf.readInt(l, cnt, "r");
            inf.readEoln();
        }
    }
    inf.readEof();
    return 0;
}
