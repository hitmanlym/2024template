#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pb push_back
using namespace std;
int g[20];
void wrt(ll x)
{
    if(!x){puts("0");return;}
    int t=0;
    while(x)g[++t]=x%10,x/=10;
    for(int i=t;i;i--)putchar(g[i]+'0');puts("");
}
const int N=5005,M=205,bs=10009,M2=N*M*3;
int n,m,D,fa[N][M],siz[N][M],ct[M2];
ll ans; ull bin[M],hs[N];
vector<int> vt[N][M];
namespace H{
  const int md=3e7;
  int hd[md],xnt,nxt[M2]; ull to[M2];
  int get(ull x)
  {
      int h=x%md;
      for(int i=hd[h];i;i=nxt[i])
        if(to[i]==x)return i;
      to[++xnt]=x; nxt[xnt]=hd[h]; hd[h]=xnt;
      return xnt;
  }
  void del(ull x)
  {
      int h=x%md;
      if(to[hd[h]]==x){hd[h]=nxt[hd[h]];return;}
      for(int i=hd[h],lst=0;i;lst=i,i=nxt[i])
        if(to[i]==x){nxt[lst]=nxt[i];break;}
  }
}
int main()
{
  ios::sync_with_stdio(false);
  cin>>D>>n>>m;
  bin[0]=1;for(int i=1;i<=D;i++)bin[i]=bin[i-1]*bs;
  for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=D;j++)
	    {
	        fa[i][j]=i; siz[i][j]=1;
	        vt[i][j].pb(i); hs[i]+=i*bin[j];
	    }
        ct[H::get(hs[i])]++;
    }
  ans=n;
  for(int i=1,u,v,d;i<=m;i++)
    {
	    cin>>u>>v>>d;
	    u=fa[u][d]; v=fa[v][d];
		if(u==v){wrt(ans);continue;}
		if(siz[u][d]<siz[v][d])swap(u,v);
	    int tot=siz[u][d];
	    siz[u][d]+=siz[v][d]; vt[u][d].resize(siz[u][d]);
	    ull tmp=(u-v)*bin[d];
	    for(int j=0,cr;j<siz[v][d];j++)
	    {
		   cr=vt[v][d][j]; fa[cr][d]=u; vt[u][d][tot++]=cr;
		   ull x=hs[cr],y=hs[cr]+tmp; hs[cr]+=tmp;
		   int t0=H::get(x),t1=H::get(y);
		   ct[t0]--; ans-=ct[t0]*2; ans+=ct[t1]*2; ct[t1]++;
	    }
		vector<int> ().swap(vt[v][d]);
	    wrt(ans);
    }
    return 0;
}