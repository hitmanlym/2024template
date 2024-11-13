#include<cstdio>
#include<algorithm>
using namespace std;
#define ll long long

int read(){
	int x=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x;
}

const int MAXN = 1e5 + 10;
const int mo = 998244353;
int n;
int a[MAXN],id[MAXN];
int cmp(int x,int y){ return a[x]<a[y]; }
struct edge{
	int v,nxt;
} e[MAXN*2];
int head[MAXN],cnt=0;
void ad(int u,int v){
	e[++cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

int fa[MAXN],f[MAXN],g[MAXN],mex=0;
ll sum=0,ans=0;
bool vis[MAXN];
void dfs(int u){
	f[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa[u]) continue;
		fa[v]=u;
		dfs(v);
		f[u]=1ll*f[u]*(f[v]+1)%mo;
	}
}
void getmex(){
	while(mex<n && vis[id[mex]]) mex++;
}
ll inv(ll x,int y){
	ll ans = 1;
	while(y){
		if(y&1) ans = ans * x % mo;
		x = x * x % mo;
		y >>= 1;
	}
	return ans;
}

int sta[MAXN],top=0;
void solve(){
	int rt=0;
	n=read();
	for(int i=1;i<=n;i++) head[i]=vis[i]=f[i]=g[i]=fa[i]=0;
	ans = sum = mex = 0;
	cnt=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(!a[i]) rt=i;
		id[a[i]]=i;
	}
	for(int i=1;i<n;i++){
		int u=read(), v=read();
		ad(u,v);
		ad(v,u);
	}
	dfs(rt);
	// printf("dfs ok\n");
	sum=f[rt];
	vis[rt]=true;
	getmex();
	sort(id,id+n,cmp);
	// printf("sort ok\n");
	// for(int i=1;i<=n;i++) printf("f[%d]=%d ",i,f[i]);
	// printf("\n");
	// for(int i=0;i<n;i++) printf("id[%d]=%d ",i,id[i]);
	// printf("\n");
	for(int i=1;i<n;i++){
		int x=id[i];
		if(vis[x]) continue;
		while(!vis[x]){
			vis[x]=true;
			if(x==id[i]) g[x]=0;
			else 
				g[x] = 1ll * f[x] * inv(f[sta[top]] + 1, mo - 2) % mo * (g[sta[top]] + 1) % mo;
			// printf("x=%d g[x]=%d\n",x,g[x]);
			sta[++top]=x;
			x = fa[x];
		}
		// printf("jump ok\n");
		sum = sum * inv(f[sta[top]] + 1, mo - 2) % mo;
		// printf("getmex ok\n");
		ans = (ans + sum * (g[sta[top]] + 1) % mo * mex % mo) % mo;
		// printf("mex=%d sum=%lld ans=%lld\n",mex,sum,ans);
		while(top){
			int u = sta[top];
			for(int i = head[u]; i; i = e[i].nxt){
				int v=e[i].v;
				if(vis[v]) continue;
				sum = sum * (f[v] + 1) % mo;
			}
			top --;
		}
		// printf("update sum ok\n");
		getmex();
	}
	ans = (ans + n) % mo;
	printf("%lld\n", ans);
	return;
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}