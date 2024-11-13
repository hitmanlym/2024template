#include<cstdio>
int a,r,n,k;
long long ans;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		if(r){
			if(a+r<=k) ans++,r=0;
			else ans+=(a+r)/k,r=(a+r)%k;
		}
		else ans+=a/k,r=a%k;
	}
	if(r) ans++;
	printf("%lld\n",ans);
	return 0;
}