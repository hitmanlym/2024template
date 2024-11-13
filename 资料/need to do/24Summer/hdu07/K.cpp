#include<cstdio>
int t;
long long x,y,ans;
long long gcd(long long a,long long b){
	if(!b) return a;
	return gcd(b,a%b);
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld",&x,&y);
		long long g=gcd(x,y);
		if(((y/g)&1)&&(x%y!=0)) ans=2;
		else ans=1;
		ans*=x/g;
		printf("%lld %lld\n",y,ans);
	}
	return 0;
}