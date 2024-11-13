#include<cstdio>
#include<iostream>
#include<vector>
#include<array>
using i64 = long long;
const int N = 3e5 + 10;
i64 tr[N];
struct Fenwick {
    int n;
    //std::vector<i64> a;

    Fenwick(int n = 0) {
        init(n);
    }
    void init(int n) {
        this -> n = n;
        /*a.resize(n + 1);
        a.assign(n + 1, 0);*/
        for (int i = 1; i <= n; i ++) {
            tr[i] = 0;
        }
    }
    void add(int x, i64 v) {
        for (; x <= n; x += x & -x) {
            tr[x] = std::max(tr[x], v);
        }
    }
    i64 sum(int x) {
        i64 ans = 0;
        for (; x; x -= x & -x) {
            ans = std::max(ans, tr[x]);
        }
        return ans;
    }
};
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
i64 res[N][4], op[N][2], use[N], ans[N];
int a[N][2], y[N][2];
void solve() {
    int n, m;
    //std::cin >> n >> m;
    n = read();
    m = read();
    for (int i = 1; i <= m; i ++) {
        for (int j = 0; j < 4; j ++) {
            res[i][j] = 0;
        }
    }
    //std::vector<std::array<i64, 4> > res(m + 1); // ans's op
    //std::vector<std::array<int, 2> > a(n + 1);
    for (int i = 1; i <= n; i ++) {
        //std::cin >> a[i][0] >> a[i][1];
        a[i][0] = read();
        a[i][1] = read();
    }
    std::vector<std::vector<int> > st(n + 1), ed(n + 1);
    //std::vector<std::array<int, 2> > y(m + 1);
    for (int i = 1; i <= m; i ++) {
        int x1, y1, x2, y2;
        //std::cin >> x1 >> y1 >> x2 >> y2;
        x1 = read();
        y1 = read();
        x2 = read();
        y2 = read();
        y[i][0] = y1;
        y[i][1] = y2;
        st[x1].push_back(i);
        ed[x2].push_back(i);
    }
    //std::vector<std::array<i64, 2> > op(n + 1);
    Fenwick t;

    t.init(n + 1); //
    for (int i = 1; i <= n; i ++) {
        for (auto j : st[i]) {
            res[j][0] += t.sum(y[j][1]);
        }
        op[i][0] = t.sum(a[i][0]) + a[i][1];
        t.add(a[i][0], op[i][0]);
        for (auto j : ed[i]) {
            res[j][1] += t.sum(y[i][0] - 1);
        }
    }

    t.init(n + 1);
    for (int i = n; i >= 1; i --) {
        for (auto j : ed[i]) {
            res[j][1] += t.sum(n - (y[j][0] - 1) + 1); // here ok for eve
        }
        op[i][1] = t.sum(n - a[i][0] + 1) + a[i][1];
        t.add(n - a[i][0] + 1, op[i][1]);
        for (auto j : st[i]) {
            res[j][0] += t.sum(n - y[j][1]);
        }
    }
    //std::vector<i64> use(n + 1);
    for (int i = 1; i <= n; i ++) {
        use[i] = op[i][0] + op[i][1] - a[i][1];
    }

    t.init(n + 1);
    for (int i = 1; i <= n; i ++) {
        for (auto j : st[i]) {
            res[j][2] += t.sum(n - y[j][1]);
        }
        t.add(n - a[i][0] + 1, use[i]);
    }

    t.init(n + 1);
    for (int i = n; i >= 1; i --) {
        for (auto j : ed[i]) {
            res[j][3] += t.sum(y[j][0] - 1);
        }
        t.add(a[i][0], use[i]);
    }

    for (int i = 1; i <= m; i ++) {
        i64 ans = 0;
        for (int j = 0; j < 4; j ++) {
            ans = std::max(ans, res[i][j]);
        }
        std::cout << ans << '\n';
    }
}   
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    t = read();
    while (t --) {
        solve();
    }
    return 0;
}