#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define MAXN 3010
#define ll long long

ll v[20];
int n,m;
int a[MAXN],b[MAXN];
ll f[MAXN],g[MAXN];
void solve(){
	for(int i=1;i<=10;i++)
		scanf("%lld",&v[i]);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=m;i++)
		f[i]=-1e9;
	f[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=a[i];j<=m;j++)
			f[j]=max(f[j],f[j-a[i]]+b[i]);
	}
	for(int i=1;i<=m;i++) f[i]=max(f[i],0ll);
	// printf("\n");
	// for(int i=1;i<=m;i++)
	// 	printf("%lld ",f[i]);
	// printf("\n");
	for(int i=1;i<=m;i++)
		g[i]=0;
	g[0]=0;
	for(int i=1;i<=m;i++){
		for(int j=i;j<=m;j++){
			ll vi=ceil(10.0*f[i]/i);
			g[j]=max(g[j],g[j-i]+v[vi]*i);
		}
	}
	// printf("\n");
	// for(int i=1;i<=m;i++)
	// 	printf("%lld ",g[i]);
	// printf("\n");
	ll ans=0;
	for(int i=1;i<=m;i++)
		ans=max(ans,g[i]);
	printf("%lld\n",ans);
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