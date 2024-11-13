#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
#define ll long long
#define MAXN 205

const ll mo = 1e9+7;
int n,m;
ll L,R;
ll e[MAXN][MAXN];

struct Matrix{
	ll val[MAXN][MAXN];
	void init(){
		for(int i=1;i<=2*n;i++)
			val[i][i]=1;
	}
	void clear(){
		for(int i=1;i<=2*n;i++)
			for(int j=1;j<=2*n;j++)
				val[i][j]=0;
	}
} F,G,LM[2],RM[2],ansx;

Matrix c;
Matrix mul(Matrix a, Matrix b){
	c.clear();
	
	for(int i=1;i<=2*n;i++)
		for(int j=1;j<=2*n;j++){
			for(int k=1;k<=2*n;k++)
				c.val[i][j] = (c.val[i][j] + a.val[i][k] * b.val[k][j] % mo) % mo;
		}
	return c;
}
Matrix qmi(Matrix x,ll y){
	printf("qmians\n");
	//exit(0);
	ansx.clear();
	ansx.init();
	while(y){
		//if(y&1) ansx = mul(ansx, x);
		x = mul(x, x);
		y >>= 1ll;
	}
	return ansx;
}

ll v[MAXN][MAXN],f[MAXN];
queue <int> q;
int ou[MAXN];
void bfs(int rt){
	for(int i=1;i<=n;i++) ou[i]=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(e[i][j]) ou[i]++;
	for(int i=1;i<=n;i++){
		if(!ou[i]) q.push(i);
		G.val[i][i]=1;
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=1;i<=n;i++){
			if(e[i][u]){
				for(int j=1;j<=n;j++)
					G.val[i][j] = (G.val[i][j] + G.val[u][j] * e[i][u] % mo) % mo;
				ou[i]--;
				if(!ou[i]) q.push(i);
			}
		}
	}
}

void solve(){
	scanf("%d%d%lld%lld",&n,&m,&L,&R);
	F.clear(),G.clear();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=2*n;j++)
			e[i][j]=0;
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[u][v]=w;
	}
	for(int i=1;i<=n;i++)
		bfs(i);
	printf("bfs ok\n");
	for(int i=1;i<=n;i++)
		f[i]=G.val[1][i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			F.val[i][j]=e[i][j+n];
	F=mul(F,G);
	printf("get F ok\n");
	for(int i=1;i<=n;i++)
		F.val[i][i+n]=F.val[i+n][i+n]=1;
	ll l1 = (L-1)/n, r1 = (R-1)/n + 1;
	ll l2 = l1 + 1, r2 = r1 + 1;
	printf("l1=%lld l2=%lld r1=%lld r2=%lld\n",l1,l2,r1,r2);

	LM[0] = qmi(F, l1);/*
	printf("get LM_0 ok\n");
	LM[1] = qmi(F, l2);
	printf("get LM_1 ok\n");
	RM[0] = qmi(F, r1);
	printf("get RM_0 ok\n");
	RM[1] = qmi(F, r2);
	printf("get RM_1 ok\n");
	int lp = (L-1)%n+1, rp = (R-1)%n+1;
	ll ans=0;
	for(int i=1;i<=n;i++){
		int lc = (i > lp), rc = (i > rp);
		ll now=0;
		for(int j=1;j<=n;j++)
			now = (now + f[j] * (RM[rc].val[j][i+n] - LM[rc].val[j][i+n]) % mo) % mo;
		ans = ((ans + now) % mo + mo) % mo;
	}
	printf("%lld\n",ans);*/
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}