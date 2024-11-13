#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 2010
#define ll long long

int n;
int a[MAXN],t[MAXN];
ll f[MAXN][MAXN][2],g[MAXN][2],v1[MAXN][MAXN][2],gv1[MAXN][2];
int clf[MAXN],cson[MAXN];

struct edge{
	int v,nxt;
} e[MAXN*2];
int head[MAXN],cnt=0;
void ad(int u,int v){
	e[++cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

void dfs1(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa) continue;
		dfs1(v,u);
		cson[u]++;
	}
}
void dfs2(int u,int fa){
	for(int i=0;i<=n;i++)
		f[u][i][0]=1e18,f[u][i][1]=1e18,v1[u][i][0]=1e18,v1[u][i][1]=1e18;
	// f[u][0][0]=0;
	f[u][0][1]=a[u];
	v1[u][0][1]=0;
	// ll minv=1e18;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa) continue;
		dfs2(v,u);
		// nowson++;
		if(cson[u]>1){
			for(int j=0;j<=clf[u];j++){
				g[j][0]=f[u][j][0],g[j][1]=f[u][j][1];
				gv1[j][0]=v1[u][j][0];
				gv1[j][1]=v1[u][j][1];
				f[u][j][0]=f[u][j][1]=v1[u][j][0]=v1[u][j][1]=1e18;
			}
			for(int j=0;j<=clf[u];j++)
				for(int k=0;k<=clf[v];k++){
					v1[u][j+k][1]=min(v1[u][j+k][1],f[v][k][1]+gv1[j][1]);
					v1[u][j+k][0]=min(v1[u][j+k][0],min(f[v][k][0]+gv1[j][1],min(f[v][k][0],f[v][k][1])+gv1[j][0]));
					// if(j+k+nowson<=clf[u]+clf[v] && k<clf[v]) 
					// 	f[u][j+k+nowson][1]=min(f[u][j+k+nowson][1],min(f[v][k][0],f[v][k][1])+g[j][0]+a[u]);
					if(k<clf[v])
						f[u][j+k+1][1]=min(f[u][j+k+1][1],f[v][k][0]+g[j][1]);
					f[u][j+k][1]=min(f[u][j+k][1],f[v][k][1]+g[j][1]);
				}
		}else {
			for(int j=0;j<=clf[v];j++){
				f[u][j][0]=f[v][j][0];
				f[u][j][1]=f[v][j][1];
				if(j>1) f[u][j][1]=min(f[u][j][1],f[v][j-1][0]+a[u]);
			}
		}
		clf[u]+=clf[v];
		// if(u==2){
		// 	printf("v=%d\n",v);
		// 	for(int j=0;j<=clf[u];j++)
		// 		printf("%lld ",v1[u][j][0]);
		// 	printf("\n\n");
		// }
	}
	if(cson[u]==0){
		f[u][0][0]=0;
		f[u][0][1]=1e18;
		f[u][1][1]=a[u];
		clf[u]=1;
	}else if(cson[u]>1){
		for(int i=0;i<=clf[u];i++){
			f[u][i][0]=min(f[u][i][0],v1[u][i][0]);
			f[u][i][1]=min(f[u][i][1],v1[u][i][1]);
		}
	}
}

void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&t[i]);
	for(int i=1;i<=n;i++)
		head[i]=cson[i]=clf[i]=0;
	cnt=0;
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		ad(u,v);
		ad(v,u);
	}
	dfs1(1,0);
	// for(int i=1;i<=n;i++)
	// 	printf("%d ",cson[i]);
	// printf("\n");
	dfs2(1,0);

	// printf("f:\n");
	// for(int i=1;i<=n;i++){
	// 	printf("i:%d\n",i);
	// 	for(int j=0;j<=clf[i];j++)
	// 		printf("%d:{%lld,%lld}\n",j,f[i][j][0],f[i][j][1]);
	// 	printf("\n");
	// }
	// printf("\n");

	// printf("v1:\n");
	// for(int i=1;i<=n;i++){
	// 	printf("i:%d\n",i);
	// 	for(int j=0;j<=clf[i];j++)
	// 		printf("%d:{%lld,%lld}\n",j,v1[i][j][0],v1[i][j][1]);
	// 	printf("\n");
	// }
	// printf("\n");

	ll ans=min(f[1][clf[1]][0],f[1][clf[1]][1]);
	for(int i=0;i<clf[1];i++)
		ans=min(ans,t[clf[1]-1-i]+min(f[1][i][0],f[1][i][1]));
	printf("%lld\n",ans);
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}

/*
1
5 
1 5 2 1 6
1 4 5 6 7
1 2
2 3
2 4
2 5

*/