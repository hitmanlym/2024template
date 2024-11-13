#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;
std::vector<std::string> date;
void pre() {
    for (int i = 1; i <= 12; i ++) {
        int j = 30;
        if (i == 2) j = 29;
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
            j = 31;
        }
        for (int k = 1; k <= j; k ++) {
            std::string s;
            int b = i % 10, a = i / 10;
            int y = k % 10, x = k / 10;
            s += ('0' + a);
            s += ('0' + b);
            s += ('0' + x);
            s += ('0' + y);
            std::reverse(s.begin(), s.end());
            date.push_back(s);
        }
    }
}
inline int get(char c) {
    int id = 0;
    if (c >= '0' && c <= '9') id = 26 + c - '0';
    else id = c - 'a';
    return id;
}
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::string s;
    std::cin >> s;
    //t = s;
    //std::reverse(t.begin(), t.end());
    //s = " " + s;
    //t = " " + t;
    // len = m
    std::vector<int> cnt(m + 1);
    std::vector<std::vector<int> > nxt(m + 1, std::vector<int>(26 + 10, m + 1));
    for (int i = m - 1; i >= 0; i --) {
        for (int j = 0; j < 26 + 10; j ++) {
            nxt[i][j] = nxt[i + 1][j];
        }
        nxt[i][get(s[m - 1 - i])] = i + 1;
    }
    for (auto it : date) {
        int o = 0;
        for (auto c : it) {
            o = nxt[o][get(c)];
            if (o == m + 1) break;
        }
        if (o == m + 1) continue;
        cnt[m - o + 1] ++;
        std::cout << m - o + 1 << ' ';
    }
    std::cout << '\n';
    for (int i = m - 1; i >= 1; i --) {
        cnt[i] += cnt[i + 1];
    }

    for (int i = m - 1; i >= 0; i --) {
        for (int j = 0; j < 26 + 10; j ++) {
            nxt[i][j] = nxt[i + 1][j];
        }
        nxt[i][get(s[i])] = i + 1;
    }
    i64 ans = 0;
    for (int i = 0; i < n; i ++) {
        std::string str;
        std::cin >> str;
        int o = 0;
        for (auto c : str) {
            o = nxt[o][get(c)];
            if (o == m + 1) break;
        }
        if (o == m + 1 || o == m) continue;
        ans += cnt[o + 1];
    }
    std::cout << ans << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    pre();
    int t = 1;/*
    for (auto it : date) {
        std::cout << it << '\n';
    }
    std::cout << date.size() << '\n';*/
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}