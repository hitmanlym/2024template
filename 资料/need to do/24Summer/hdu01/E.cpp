#include<cstdio>
#define N 10000000
int mod=998244353;
int fac[N+5],inv[N+5];
int t,n,m,h[30],f,mul,p;
char c[2];
int pow(int x,int k){
	int s=1;
	for(;k;x=1ll*x*x%mod,k>>=1) if(k&1) s=1ll*x*s%mod;
	return s;
}
void init(){
	fac[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=pow(fac[N],mod-2);
	for(int i=N;i>0;i--) inv[i-1]=1ll*inv[i]*i%mod;
}
int main(){
	init();
	scanf("%d",&t);
	while(t--){
		scanf("%d",&m),f=n=0,mul=1;
		for(int i=1;i<=m;i++){
			scanf("%s%d",c,&h[i]);
			if(h[i]&1){
				if(f){
					f=-1;
					break;
				}
				f=i;
				h[i]--;
			}
			(n+=h[i])%=mod;
			mul=1ll*mul*fac[h[i]]%mod*inv[h[i]>>1]%mod;
		}
		if(f==-1) printf("%d\n",pow(2,mod-2));
		else if(f){
			p=1ll*(h[f]+1)*pow(n+1,mod-2)%mod*fac[n>>1]%mod*inv[n]%mod*mul%mod;
			printf("%d\n",(p+1ll*(1-p+mod)*pow(2,mod-2)%mod)%mod);
		}
		else{
			p=1ll*fac[n>>1]*inv[n]%mod*mul%mod;
			printf("%d\n",(1ll*(1-p)*pow(2,mod-2)%mod-p+mod)%mod);
		}
	}
	return 0;
}