
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vint;

const int N = 10005;

int nxt[N];
int n, m, d[N];
vint e[N];
int qr[105], as[105], val[N];

set<int> b[N];
/*
void dfs(int u, int pa) {
    d[u] += val[u];
    b[u].insert(d[u]);
    for (int v : e[u]) {
        d[v] = d[u];
        dfs(v, u);
        if (b[u].size() < b[v].size()) b[v].swap(b[u]);
        for (int i : b[v]) {
            for (int j = 1; j <= m; ++j)
                if (!as[j] && b[u].find(qr[j] + d[u] + d[pa] - i) != b[u].end()) as[j] = 1;
        }
        b[u].merge(b[v]);
    }
   // for (int i : b[u]) cout << i << ' '; cout << ": " << u << '\n';
}*/

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    string s; cin >> s; s = '#' + s;
    for (int i = 2,p = 0; i <= n; ++i) {
        while(p && s[i] != s[p + 1]) p = nxt[p];
        if(s[i] == s[p + 1]) p ++;
        nxt[i] = p;
    }
    for (int i = 1; i <= n; ++i) e[nxt[i]].push_back(i), val[i] = i ^ nxt[i];
    for (int i = 1; i <= m; ++i) cin >> qr[i];
    for (int i = 1; i <= n; i ++) {
        std::cout << nxt[i] << ' ' << i << '\n';
    }
    for (int i = 0; i <= n; i ++) {
        std::cout << val[i] << ' ';
    }
    std::cout << '\n';
    /*dfs(0, 0);
    for (int i = 1; i <= m; ++i) cout << (as[i] ? "Yes" : "No") << '\n';*/
    return 0;
}