#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
#define MAXN 100010
#define ll long long

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

int p[MAXN];
ll s[MAXN],lcm;

ll GCD(int a,int b){ return b==0?a:GCD(b,a%b); }
ll LCM(int a,int b){ return a/GCD(a,b)*b; }

void dfs(int u,int fa){
	s[u]=lcm/p[u];
	ll maxx=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u);
		maxx=max(maxx,s[v]);
	}
	s[u]+=maxx;
}
void clear(){
	for(int i=1;i<=n;i++){
		head[i]=0;
		s[i]=p[i]=0;
	}
	cnt=0;
}

void solve(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		ad(u,v);ad(v,u);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]);
	dfs(1,0);
	ll ans1=s[1],ans2=lcm/15;
	// printf("%lld %lld\n",ans1,ans2);
	ll g=GCD(ans1,ans2);
	printf("%lld/%lld\n",ans1/g,ans2/g);
	clear();
}

int main()
{
	
	lcm=1;
	for(int i=2;i<=15;i++)
		lcm=LCM(lcm,i);
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}