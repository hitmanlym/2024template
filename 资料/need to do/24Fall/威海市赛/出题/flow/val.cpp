#include <bits/stdc++.h>
#include "testlib.h"
 
using i64 = long long;
 
const int N = 100;
const int S = 1e4, T = 2e5;
void space() {
    inf.readSpace();
}
void eoln() {
    inf.readEoln();
}
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N, "n");
    int lim = n * (n - 1) / 2;
    space();
    int m = inf.readInt(0, lim, "m");
    eoln();
    for (int i = 1; i <= m; i ++) {
        int u = inf.readInt(1, n, "u");
        space();
        int v = inf.readInt(1, n, "v");
        eoln();
    }
    for (int i = 1; i <= n; i ++) {
        int a = inf.readInt(1, S, "a");
        if (i < n) space();
        else eoln();
    }
    for (int i = 1; i <= n; i ++) {
        int b = inf.readInt(1, T, "b");
        if (i < n) space();
        else eoln();
    }
    int X = inf.readInt(1, n, "X");
    eoln();
    inf.readEof();
    return 0;
}
