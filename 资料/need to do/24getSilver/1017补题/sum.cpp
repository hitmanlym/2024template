#include<bits/stdc++.h>
using i64 = long long;
using db = double;
const int inf = 2e9;
// #define int i64
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::set<std::array<int, 2> > a, b;
    db total = 0.0;
    i64 lena = 0, lenb = 0;
    std::set<int> p;
    for (int i = 1; i <= n; i ++) {
        int u, v;
        std::cin >> u >> v;
        p.insert(u);
        p.insert(v);
        a.insert({u, v});
        lena += (v - u);
    }
    for (int i = 1; i <= m; i ++) {
        int u, v;
        std::cin >> u >> v;
        p.insert(u);
        p.insert(v);
        b.insert({u, v});
        lenb += (v - u);
    }
    if (lena == 0 && lenb == 0) {
        int k = b.size(), oo = a.size();
        std::vector<db> suf(k + 2), pre(k + 1), PRE(k + 1), SUF(k + 2);
        std::vector<int> B(k + 1);
        int cnt = 0;
        std::map<int, int> min, max;
        for (auto it : b) {
            B[++ cnt] = it[0];
            max[it[0]] = cnt;
            if (! min.count(it[0])) {
                min[it[0]] = cnt;
            }
        }
        for (int i = 1; i <= k; i ++) {
            pre[i] = pre[i - 1] + B[i];
            PRE[i] = PRE[i - 1] + 1;
        }
        for (int i = k; i >= 1; i --) {
            SUF[i] = SUF[i + 1] + 1;
            suf[i] = suf[i + 1] + B[i];
        }
        b.insert({inf, inf});
        for (auto it : a) {
            int v = it[0];
            auto o = b.lower_bound({v, 0});
            auto po = o;
            int idl = 0, idr = k + 1;
            if (o != b.begin()) {
                o = prev(o);
                idl = max[(*o)[0]];
            }
            if (po != b.end()) {
                idr = min[(*po)[0]];
            }
            total += ((db)(PRE[idl] * v - pre[idl]) + (db)(suf[idr] - SUF[idr] * v)) / (db)k;
        }
        printf("%.15lf", total / (db)oo);
        return ;
    } else {
        bool f = 0;
        if (lena != 0) {
            std::swap(a, b);
            std::swap(lena, lenb);
        } 
        std::vector<std::array<int, 2> > dela, delb;
        for (auto it : b) {
            if (it[0] == it[1]) delb.push_back({it[0], it[1]}); // 段
        }
        for (auto it : delb) {
            b.erase(it);
        }
        if (lena == 0) {
            lena = a.size(); // 与点一样的.
            f = 1;
        } else {
            for (auto it : a) {
                if (it[0] == it[1]) dela.push_back({it[0], it[1]});
            }
            for (auto it : dela) {
                a.erase(it);
            }
        }
        for (auto v : p) { // 断点
            auto it = a.lower_bound({v, 0});
            if (! f && it != a.begin()) {
                it = prev(it);
                if ((*it)[1] > v) {
                    auto op = *it;
                    a.erase(it);
                    if (op[0] != v) a.insert({op[0], v});
                    if (op[1] != v)a.insert({v, op[1]});
                }
            }
            it = b.lower_bound({v, 0});
            if (it == b.begin()) continue;
            it = prev(it);
            if ((*it)[1] > v) {
                auto op = *it;
                b.erase(it);
                if (op[0] != v) b.insert({op[0], v});
                if (v != op[1]) b.insert({v, op[1]});
            }
        }
        int k = b.size();
        std::vector<db> pre(k + 1), suf(k + 2);
        std::vector<db> PRE(k + 1), SUF(k + 2);
        std::vector<std::array<int, 2> > B(k + 1);
        std::map<int, int> rev;
        int cnt = 0;
        for (auto it : b) { // * 长度贡献
            B[++ cnt] = it;
            rev[it[0]] = cnt;
        }
        for (int i = 1; i <= k; i ++) {
            pre[i] = pre[i - 1] + (db)(B[i][1] + B[i][0]) * (B[i][1] - B[i][0]) / 2.0;
            PRE[i] = PRE[i - 1] + (db)(B[i][1] - B[i][0]);
        }
        for (int i = k; i >= 1; i --) {
            suf[i] = suf[i + 1] + (db)(B[i][1] + B[i][0]) * (B[i][1] - B[i][0]) / 2.0;
            SUF[i] = SUF[i + 1] + (db)(B[i][1] - B[i][0]);
        }
        b.insert({inf, inf});
        for (auto it : a) {
            int l = it[0], r = it[1];
            auto L = b.lower_bound({l, -inf}), R = b.lower_bound({r, -inf});
            auto com = *L;
            int idl = 0, idr = k + 1;
            if (L != b.begin()) {
                L = prev(L);
                if (rev.count((*L)[0]))
                idl = rev[(*L)[0]];
            }
            if (R != a.end() && rev.count((*R)[0])) {
                idr = rev[(*R)[0]];
            }
            db x = (db)(l + r) / 2.0;
            // std::cout << l << ' ' <<  r << ' ' << idl << ' ' << idr << '\n';
            if (f) { // 点
                total += ((db)(PRE[idl] * x - pre[idl]) + (db)(suf[idr] - SUF[idr] * x)) / (db)lenb;
            } else { // NO 
                total += (db)(r - l) / (db)(lenb) * ((PRE[idl] * x - pre[idl]) + (suf[idr] - SUF[idr] * x) 
                    + ((com[0] == l && com[1] == r) ? (db)(r - l) * (r - l) / 3.0 : 0.0));
            }
        }
        printf("%.15lf", total / (db)(lena));
        return ;
    }
}
signed main() {
    solve();
    return 0;
}
/*
8 9
-2175 -2174
-1068 -1065
-1721 -1718
777 834
1162 1169
-3529 -3524
3966 3993
1934 1952
-234 -223
-4967 -4947
8500 8510
5272 5276
-6048 -6033
-34 -22
700 705
-7890 -7886
5538 5543
*/