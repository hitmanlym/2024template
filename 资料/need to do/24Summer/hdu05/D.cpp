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
int get(int a, int b) {
    return a % b == 0 ? b : get(b, a % b);
}
const int N = 1e5 + 10;
int lg[N];
struct Fenwick {
    int n;
    std::vector<int> a;

    Fenwick(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        a.resize(n + 1);
        a.assign(n + 1, 0);
    }
    void add(int x, int v) {
        for (; x <= n; x += x & -x) {
            a[x] += v;
        }
    }
    void add(int x, int y, int v) {
        add(x, v), add(y + 1, -v);
    }
    int sum(int x) {
        int ans = 0;
        for (; x; x -= x & -x) {
            ans += a[x];
        }
        return ans;
    }
    int rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
}arr;
int st[N], ed[N];
struct LCA {
    int n, rt = 1, dfn[N], ff[20][N], dn;
    struct {
        int to, nxt;
    } e[N * 2];
    int h[N], num = 0;

    //LCA(int n) : n(n + 1) {}
    void init(int n) {
        num = 0;
        this->n = n;
        for (int i = 0; i <= n; i ++) {
            h[i] = 0;
        }
        dn = 0;
    }
    void addEdge(int a, int b) {
        e[++ num] = {b, h[a]}; h[a] = num;
        e[++ num] = {a, h[b]}; h[b] = num;
    }

    void dfs(int u, int p) {
        ff[0][dfn[u] = ++ dn] = p;
        st[u] = dn;
        for (int  i = h[u]; i; i = e[i].nxt) {
            if (e[i].to == p) continue;
            dfs(e[i].to, u);
        }
        ed[u] = dn;
    }
    int get(int x, int y) {
        if (dfn[x] < dfn[y]) return x;
        else return y;
    }
    void work() {
        dfs(rt, 0);
        for (int i = 1; i <= lg[n]; i ++) { //RMQ deep less
            for (int j = 1; j + (1 << i) - 1 <= n; j ++) {
                ff[i][j] = get(ff[i - 1][j], ff[i - 1][j + (1 << i - 1)]);
            }
        }
    }
    int lca(int u, int v) {
        if (u == v) {
            return u;
        } 
        if ((u = dfn[u]) > (v = dfn[v])) std::swap(u, v);
        int d = lg[v - u];
        return get(ff[d][++ u], ff[d][v - (1 << d) + 1]);
    }
}t;
std::vector<std::pair<int, int>> lcm[N];
std::vector<int> d[N];
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
void write(i64 x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}
const int Q = 1e6 + 10;
struct Query{
    int r,x,idx;
    bool operator <(const Query &rhs)const{
        return x<rhs.x;
    }
}qs[Q];
void solve() {
    int n;
    //std::cin >> n;
    n = read();
    t.init(n);
    for (int i = 1; i < n; i ++) {
        int u, v;
        //std::cin >> u >> v;
        u = read();
        v = read();
        t.addEdge(u, v);
    }
    t.work();
    int q;
    //std::cin >> q;
    q = read();
    std::vector<std::array<int, 3> > a(q);
    std::vector<int> ans(q);
    for (int i = 0; i < q; i ++) {
        qs[i].r = read();
        qs[i].x = read();
        qs[i].idx = i;
    }
    std::sort(qs, qs + q);
    int l = 0;
    for (int i = 0; i < q; i ++) {
        while (l < N && l <= qs[i].x) {
            for (auto it : lcm[l]) {
                int x = it.first, y = it.second;

                if (x <= n) arr.add(t.dfn[t.lca(x, y)], 2 - (x == y));
            }
            l ++;
        }
        //std::cout << "!!! " << st[a[i][1]] << ' ' << ed[a[i][1]] << '\n';
        ans[qs[i].idx] = arr.rangeSum(st[qs[i].r], ed[qs[i].r]);
    }
    for (int i = 0; i < q; i ++) {
        //std::cout << ans[i] << ' ';
        write(ans[i]);
        putchar(' ');
    }
    puts("");
    // std::cout << '\n
    for (int i = 1; i <= n; i ++) {
        arr.a[i] = 0;
    }
}
int main() {
    // freopen("1004.in", "r", stdin);
    // freopen("ans.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    for (int i = 1; i < N; i ++) {
        for (int j = i; j < N; j += i) {
            d[j].push_back(i);
        }
    } 
    // 
    for (int i = 1; i < N; i ++) {
        for (int j = i; j < N; j += i) {
            for (auto k : d[j]) {
                if (k <= i && i / get(k, i) * k == j) {
                    lcm[j].push_back(std::make_pair(i, k));
                }
            }
        }
    }
    arr.init(N);
    for(int i = 2; i < N; i ++)
        lg[i] = lg[i >> 1] + 1;
    int t = 1;
    //std::cin >> t;
    t = read();
    while (t --) {
        solve();
    }
    return 0;
}