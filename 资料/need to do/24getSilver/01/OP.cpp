#include<cstdio>
#include<cstring>
#define N 505
#define mod 998244353
#define ll long long
using namespace std;
int n,tot,son[N],siz[N];
ll jc[N],ans[N][N],f[N][N],g[N],t[N];
struct node {int to,next,head;}a[N<<1];
void add(int x,int y)
{
    a[++tot].to=y;a[tot].next=a[x].head;a[x].head=tot;
    a[++tot].to=x;a[tot].next=a[y].head;a[y].head=tot;
}
ll ksm(ll x,ll y)
{
    ll res=1;
    while (y)
    {
        if (y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
void gett(int x,int fa)
{
    ll res=1;
    siz[x]=1;t[x]=1;
    for (int i=a[x].head;i;i=a[i].next)
    {
        int y=a[i].to;
        if (y==fa) continue;
        gett(y,x);
        son[x]++;siz[x]+=siz[y];
        t[x]=t[x]*t[y]%mod;
    }
    t[x]=t[x]*jc[son[x]]%mod;
}
void dfs(int x,int fa)
{
    memset(f,0,sizeof(f));
    f[0][0]=1;
    for (int i=a[x].head;i;i=a[i].next)
    {
        int y=a[i].to;
        if (y==fa) continue;
        for (int j=son[x];j;--j)
            for (int k=siz[y];k<=siz[x];++k)
                f[j][k]=(f[j][k]+f[j-1][k-siz[y]])%mod;
    }
    for (int i=a[x].head;i;i=a[i].next)
    {
        int y=a[i].to;
        ll base=t[x]*ksm(t[y],mod-2)%mod*ksm(jc[son[x]],mod-2)%mod;
        if (y==fa) continue;
        for (int j=1;j<=son[x];++j)
            for (int k=siz[y];k<=siz[x];++k)
                f[j][k]=(f[j][k]-f[j-1][k-siz[y]]+mod)%mod;
        memset(g,0,sizeof(g));
        for (int j=0;j<son[x];++j)
            for (int k=0;k<siz[x];++k)
                g[k+1]=(g[k+1]+f[j][k]*jc[j]%mod*jc[son[x]-1-j]%mod*base%mod)%mod;
        for (int j=1;j<=n;++j)
            for (int k=j+1;k<=n;++k)
                ans[y][k]=(ans[y][k]+ans[x][j]*g[k-j]%mod)%mod;
        for (int j=son[x];j;--j)
            for (int k=siz[y];k<=siz[x];++k)
                f[j][k]=(f[j][k]+f[j-1][k-siz[y]])%mod;
    }
    for (int i=a[x].head;i;i=a[i].next)
    {
        int y=a[i].to;
        if (y==fa) continue;
        dfs(y,x);
    }
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    jc[0]=1;
    for (int i=1;i<=n;++i)
        jc[i]=jc[i-1]*(ll)i%mod;
    gett(1,0);
    ans[1][1]=1;
    dfs(1,0);
    for (int i=1;i<=n;++i)
    {
        for (int j=1;j<=n;++j)
            printf("%lld ",ans[i][j]*t[i]%mod);
        printf("\n");
    }
    return 0;
}