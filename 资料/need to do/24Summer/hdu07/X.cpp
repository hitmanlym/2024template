#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define ll long long
#define MAXN 205
#define re register
#define il inline 
using i64 = long long;
const int mo = 1e9+7;
const ll lim = 4e18;
int n,m;
ll L,R;
int e[MAXN][MAXN];

struct Matrix {
	int n;
	std::vector<std::vector<i64> > val;
	Matrix() {}
	void init(int n) {
		this -> n = n;
		val.assign(n + 1, std::vector<i64>(n + 1, 0));
	}
	void norm() {
		for (int i = 1; i <= n; i ++) {
			val[i][i] = 1;
		}
	}
	il Matrix friend operator * (const Matrix &a, const Matrix &b) {
		Matrix ans;
		re short n = a.n;
		ans.init(n);
		for (re short i = 1; i <= n; i ++) {
			for (re short j = 1; j <= n; j ++) {
				re long long now = 0;
				for (re short k = 1; k <= n; k ++) {
					now = (now + a.val[i][k] * b.val[k][j]);
					if(now > lim) now %= mo;
				}
				ans.val[i][j] = now % mo;
			}
		}
		return ans;
	}
} F,G,LM[2],RM[2];
Matrix qmi(Matrix a, long long b) {
	//std::cout << "FUCK " << b << '\n';
	Matrix ans;
	int n = a.n;
	ans.init(n);
	ans.norm();
	while (b) {
		if (b & 1ll) ans = ans * a;
		a = a * a;
		b >>= 1ll;
	}
	return ans;
}

ll v[MAXN][MAXN],f[MAXN];
queue <int> q;
int ou[MAXN];
void bfs(){
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
		for(int i=1;i<=u-1;i++){
			if(e[i][u]){
				for(int j=u;j<=n;j++) {
					G.val[i][j] = (G.val[i][j] + G.val[u][j] * e[i][u]);
					if (G.val[i][j] > lim) G.val[i][j] %= mo;
				}
				ou[i]--;
				if(!ou[i]) q.push(i);
			}
		}
		for(int i=1;i<=u-1;i++){
			if(e[i][u]){
				for(int j=u;j<=n;j++) {
					G.val[i][j] %= mo;
				}
			}
		}
	}
}

void solve(){
	scanf("%d%d%lld%lld",&n,&m,&L,&R);
	//std::cout << n << ' ' << m << ' ' << L << ' ' << R << '\n';
	F.init(n * 2);
	G.init(n * 2);
	//F.clear(),G.clear();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=2*n;j++)
			e[i][j]=0;
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		//std::cout << u << ' ' << v << ' ' << w << '\n';
		e[u][v]=w;
	}
	bfs();
	// printf("bfs ok\n");
	for(int i=1;i<=n;i++)
		f[i]=G.val[1][i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			F.val[i][j]=e[i][j+n];


	// printf("F:\n");
	// for(int i=1;i<=n;i++){
	// 	for(int j=1;j<=n;j++)
	// 		printf("%d ",F.val[i][j]);
	// 	printf("\n");
	// }
	// printf("\n");
	// printf("G:\n");
	// for(int i=1;i<=n;i++){
	// 	for(int j=1;j<=n;j++)
	// 		printf("%d ",G.val[i][j]);
	// 	printf("\n");
	// }
	// printf("\n");


	F = F * G;
	//printf("get F ok\n");
	for(int i=1;i<=n;i++)
		F.val[i][i+n]=F.val[i+n][i+n]=1;
	ll l1 = (L-1)/n, r1 = (R-1)/n;
	// printf("l1=%lld l2=%lld r1=%lld r2=%lld\n",l1,l2,r1,r2);

	LM[0] = qmi(F, l1);
	// printf("get LM_0 ok\n");
	LM[1] = LM[0] * F;
	// printf("get LM_1 ok\n");
	RM[0] = LM[0] * qmi(F, r1 - l1);
	// printf("get RM_0 ok\n");
	RM[1] = RM[0] * F;
	// printf("get RM_1 ok\n");
	int lp = (L-1)%n+1, rp = (R-1)%n+1;
	//printf("lp=%d rp=%d\n",lp,rp);
	
	ll ans=0;
	for(int i=1;i<=n;i++){
		int lc = (i < lp), rc = (i <= rp);
		ll now=0;
		for(int j=1;j<=n;j++)
			now = (now + f[j] * (RM[rc].val[j][i+n] - LM[lc].val[j][i+n]) % mo) % mo;
		ans = ((ans + now) % mo + mo) % mo;
		// printf("i=%d:lc=%d rc=%d now=%lld\n",i,lc,rc,now);
	}
	printf("%lld\n",ans);
}

int main()
{

	//freopen("1008.out","r",stdin);
    // freopen("data.out","w",stdout);
	int t = 1;
	//scanf("%d",&t);
	// while(t--)
	char s[]="data0.out";
	while(t--){
		///freopen(s,"w",stdout);
		solve();
		//i64 x;
		//std::cin >> x;
		//std::cout << x;
		s[4]++;
	}
	return 0;
}