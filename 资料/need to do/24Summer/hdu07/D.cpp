#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
#define MAXN 100010

int n,s,r1,r2;
struct edge{
	int v,nxt;
} e[MAXN*2];
int head[MAXN],cnt=0;
void ad(int u,int v){
	e[++cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

int dis[MAXN];
void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa) continue;
		dis[v]=dis[u]+1;
		dfs(v,u);
	}
}

void solve(){
	scanf("%d%d%d%d",&n,&s,&r1,&r2);
	for(int i=1;i<=n;i++) head[i]=0;
	cnt=0;
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		ad(u,v);
		ad(v,u);
	}
	dis[1]=0;
	dfs(1,0);
	int rt=0;
	for(int i=1;i<=n;i++)
		if(!rt || dis[i]>dis[rt]) rt=i;
	dis[rt]=0;
	dfs(rt,0);
	int d=0;
	for(int i=1;i<=n;i++)
		d=max(d,dis[i]);
	if(2*r1>=d || r2<=2*r1){
		puts("Kangaroo_Splay");
		return;
	}
	puts("General_Kangaroo");
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}