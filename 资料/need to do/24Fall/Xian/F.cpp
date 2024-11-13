#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;
#define MAXP 5000
#define ll long long
#define int long long

const int mo=998244353;
int logpk=1,p,x;
int C[MAXP][MAXP];

int k[1001],nk[1001];
int stk=1000;
void getlog(){
	while(1){
		bool divided=false;
		int now=0;
		for(int i=stk;i<=1000;i++){
			now=(now<<1)+(now<<3)+k[i];
			if(now>=p){
				int v=now/p;
				int j=i;
				while(v){
					nk[j]+=v%10;
					v/=10;
					j--;
				}
				now%=p;
				divided=true;
			}
		}
		if(!divided) return;
		logpk++;
		for(int i=1;i<=1000;i++) k[i]=nk[i],nk[i]=0;
		stk=1000;
		while(k[stk]){
			k[stk-1]+=k[stk]/10;
			k[stk]%=10;
			stk--;
		}
		stk++;
		// for(int i=stk;i<=1000;i++)
		// 	printf("%d",k[i]);
		// printf("\n\n");
	}
}
ll g[MAXP];
ll f[5010][MAXP];
ll ans[1010];
ll qmi(ll x,int y){
	ll ans=1;
	while(y){
		if(y&1) ans=ans*x%mo;
		y>>=1;
		x=x*x%mo;
	}
	return ans;
}

signed main()
{
	stk=1000;
	char c=getchar();
	while(c>='0' && c<='1'){
		for(int i=1000;i>=stk;i--){
			k[i]<<=1;
			if(i==1000) k[i]+=(c^48);
		}
		stk=1000;
		while(k[stk]){
			k[stk-1]+=k[stk]/10;
			k[stk]%=10;
			stk--;
		}
		stk++;
		for(int i=stk;i<=1000;i++)
			printf("%d",k[i]);
		printf("\n\n");
		c=getchar();
	}
	scanf("%lld%lld",&p,&x);
	getlog();
	// printf("logpk=%d\n",logpk);
	C[0][0]=1;
	g[1]++;
	for(int i=1;i<p;i++){
		C[i][0]=1;
		g[1]++;
		for(int j=1;j<=i;j++){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
			g[C[i][j]]++;
		}
	}
	printf("g[x]=%lld\n",g[x]);
	printf("getg ok\n");
	f[0][1]=1;
	for(int i=1;i<=logpk;i++){
		for(int j=1;j<p;j++){
			for(int u=1;u<p;u++)
				f[i][j*u%p]=(f[i][j*u%p]+f[i-1][j]*g[u]%mo)%mo;
		}
	}
	ll allans=0;
	for(int i=1;i<=logpk;i++){
		allans=(allans+f[i][x]*qmi(p,logpk-i)%mo)%mo;
	}
	printf("%lld\n",allans);
	return 0;
}
