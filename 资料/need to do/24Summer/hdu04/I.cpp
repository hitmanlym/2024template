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
int cnt = 0;
std::vector<std::vector<int> > date(366, std::vector<int>(4));
void pre() {
    for (int i = 1; i <= 12; i ++) {
        int j = 30;
        if (i == 2) j = 29;
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
            j = 31;
        }
        for (int k = 1; k <= j; k ++) {
            std::string s = "";
            int b = i % 10, a = i / 10;
            int y = k % 10, x = k / 10;
            date[cnt ++] = {('0' + y), ('0' + x), ('0' + b), ('0' + a)};
        }
    }
}
inline int get(char c) {
    int id = 0;
    if (c >= '0' && c <= '9') id = c - '0';
    else id = c - 'a';
    return id;
}
const int N = 7e6 + 10;
char s[N], str[N];
void solve() {
    int n, m;
    //std::cin >> n >> m;
    scanf("%d%d", &n, &m);
    //std::cin >> s;
    scanf("%s", s);
    std::vector<std::array<int, 2> > number, alpha;
    for (int i = 0; i < m; i ++) {
        if (s[i] >= '0' && s[i] <= '9') {
            number.push_back({s[i], i});
        } else {
            alpha.push_back({s[i], i});
        }
    }
    int cnt_number = number.size(), cnt_alpha = alpha.size();
    std::vector<std::vector<int> > nxt1(cnt_alpha + 1, std::vector<int>(26, cnt_alpha + 1));
    std::vector<std::vector<int> > nxt2(cnt_number + 1, std::vector<int>(10, cnt_number + 1));
    for (int i = cnt_alpha - 1; i >= 0; i --) {
        for (int j = 0; j < 26; j ++) {
            nxt1[i][j] = nxt1[i + 1][j];
        }
        nxt1[i][get(alpha[i][0])] = i + 1;
    }
    for (int i = cnt_number - 1; i >= 0; i --) {
        for (int j = 0; j < 10; j ++) {
            nxt2[i][j] = nxt2[i + 1][j];
        }
        nxt2[i][get(number[cnt_number - 1 - i][0])] = i + 1;
        //std::cout << "!!! " << get(number[cnt_number - 1 - i][0]) << ' ';
    }
    //std::cout << '\n';
    std::vector<int> cnt(m + 1);
    for (auto it : date) {
        int o = 0;
        for (auto c : it) {
            o = nxt2[o][get(c)];
            if (o == cnt_number + 1) break;
        }
        if (o == cnt_number + 1) continue;
        cnt[number[cnt_number - 1 - o + 1][1] + 1] ++;
        //std::cout << o << ' ' << m - number[cnt_number - 1 - o + 1][1] + 1 << '\n';
        //std::cout << number[cnt_number - 1 - o + 1][1] + 1  << ' ';
    }
    //std::cout << '\n';
    for (int i = m - 1; i >= 1; i --) {
        cnt[i] += cnt[i + 1];
    }
    i64 ans = 0;
    for (int i = 0; i < n; i ++) {
        //std::string str;
        //std::cin >> str;
        scanf("%s", str);
        int len = strlen(str);
        int o = 0;
        for (int i = 0; i < len; i ++) {
            o = nxt1[o][get(str[i])];
            if (o == cnt_alpha + 1) break;
        }
        //std::cout << "??? " << str << ' ' << o << '\n';
        if (o == cnt_alpha + 1) continue;
        //std::cout << str << ' ' << alpha[o - 1][1] << '\n';
        if (alpha[o - 1][1] + 1 <= m)
        ans += cnt[alpha[o - 1][1] + 1];
    }
    //std::cout << ans << '\n';
    printf("%lld\n", ans);
}
int main() {
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    pre();
    int t = 1;/*
    for (auto it : date) {
        std::cout << it << '\n';
    }
    std::cout << date.size() << '\n';*/
    //std::cin >> t;
    scanf("%d", &t);
    while (t --) {
        solve();
    }
    return 0;
}