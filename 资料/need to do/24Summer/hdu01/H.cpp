#include<cstdio>
long long ans;
int t,n,k;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k),ans=1;
		while(k--){
			if(n&1) ans*=12;
			else ans*=4;
			n>>=1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}