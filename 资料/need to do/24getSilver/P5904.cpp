#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define ll long long
#define MAXN 100010

int n;
struct edge{
	int v,nxt;
} e[MAXN*2];
int head[MAXN],cnt=0;
void ad(int u,int v){
	e[++cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

ll ans=0;
int son[MAXN],maxdep[MAXN];
void dfs1(int u,int fa){
	maxdep[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa) continue;
		dfs1(v,u);
		if(!son[u] || maxdep[v]>maxdep[son[u]])
			son[u]=v;
	}
	maxdep[u]=maxdep[son[u]]+1;
}
//void dfs2(int u,int fa){
//	f[u][0]=1;
//	for(int i=head[u];i;i=e[i].nxt){
//		int v=e[i].v;
//		if(v==fa) continue;
//		dfs(v,u);
//		for(int j=1;j<=n;j++){
//			ans+=f[u][j-1]*g[v][j]+g[u][j]*f[v][j-1];
//			g[u][j]+=1ll*f[u][j]*f[v][j-1];
//		}
//		for(int j=0;j<n;j++)
//			g[u][j]+=g[v][j+1];
//		for(int j=1;j<=n;j++)
//			f[u][j]+=f[v][j-1];
//	}
////	ans+=g[u][0];
//}
ll *f[MAXN],*g[MAXN],tmp[MAXN*4],*id=tmp;
void dfs2(int u,int fa){
	if(son[u]){
		f[son[u]]=f[u]+1,g[son[u]]=g[u]-1;
		dfs2(son[u],u);
	}
	f[u][0]=1;ans+=g[u][0];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa || v==son[u]) continue;
		f[v]=id;id+=maxdep[v]*2;
		g[v]=id;id+=maxdep[v]*2;
		dfs2(v,u);
		for(int j=1;j<=maxdep[v];j++)
			ans+=f[u][j-1]*g[v][j]+g[u][j]*f[v][j-1];
		for(int j=0;j<=maxdep[v];j++)
			g[u][j+1]+=f[u][j+1]*f[v][j];
		for(int j=0;j<maxdep[v];j++)
			g[u][j]+=g[v][j+1];
		for(int j=0;j<=maxdep[v];j++)
			f[u][j+1]+=f[v][j];
	}
}

int main()
{
//	freopen("three.in","r",stdin);
//	freopen("three.out","w",stdout);
//	while(scanf("%d",&n)!=EOF){
//		if(n==0) break;
		scanf("%d",&n);
		cnt=ans=0;
		for(int i=1;i<n;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			ad(u,v);ad(v,u);
		}
		dfs1(1,0);
		f[1]=id;id+=maxdep[1]*2;
		g[1]=id;id+=maxdep[1]*2;
		dfs2(1,0);
		printf("%lld\n",ans);
		for(int i=1;i<=n;i++)
			head[i]=maxdep[i]=son[i]=0;
		for(int i=1;i<=n*4;i++)
			tmp[i]=0;
		id=tmp;
//	}
	return 0;
}
