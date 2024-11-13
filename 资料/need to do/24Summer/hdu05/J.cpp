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
const int N = 2e5 + 10;
int a[N], c[N], f[19][N], ok[N], dep[N];
int lg[N];
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
void solve() {
    // memset(f[0],0,sizeof(f[0]));
    // for(int i = 0; i <= lg[200000]; i ++)
    //     f[i][0] = 0;
    int q;
    q = read();
    c[0] = read();
    a[0] = read();
    ok[0] = 1; 
    dep[0] = 0;
    for (int i = 1; i <= q; i ++) {
        int op;
        op = read();
        if (op == 1) {
            int u, v, p, w;
            v = read();
            u = read();
            p = read();
            w = read();
            f[0][v] = u;
            c[v] = p;
            a[v] = w;
            ok[v] = 1;
            dep[v] = dep[u] + 1;
            for (int j = 1; j <= lg[dep[v]]; j ++) {
                f[j][v] = f[j - 1][f[j - 1][v]];
            }
        } else if (op == 2) {
            int k, s, x;
            k = read();
            s = read();
            int cnt = 0;
            i64 sum = 0;
            while (s) {
                x = k;
                for (int j = lg[dep[x]]; j >= 0; j = std::min(j - 1, lg[dep[x]])) {
                    if (ok[f[j][x]]) {
                        x = f[j][x];
                    }
                }
                i64 it = std::min(s, a[x]);
                if (it == 0 && (! ok[x])) break;
                a[x] -= it;
                s -= it;
                cnt += it;
                sum += 1ll * c[x] * it;
                if (a[x] == 0) {
                    ok[x] = 0;
                } 
            }
            //std::cout << cnt << ' ' << sum << '\n';
            write(cnt);
            putchar(' ');
            write(sum);
            puts("");
        } else {
            int l;
            l = read();
            //std::cin >> l;
            a[l] = 0;
        }
    }
}
int main() {
    // freopen("1010.in", "r", stdin);
    // freopen("ans.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    for(int i = 2; i <= 200000; i ++)
        lg[i] = lg[i >> 1] + 1;
    // printf("%d\n",lg[63]);
    int t = 1;
    t = read();
    while (t --) {
        solve();
    }
    return 0;
}