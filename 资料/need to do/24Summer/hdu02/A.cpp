#include<cstdio>
int t,n,r;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		r=n%3;
		n/=3;
		if(!n) for(int i=2;i<=r+1;i++) printf("1 %d\n",i);
		if(n) for(int i=2;i<=n+3+r;i++) printf("1 %d\n",i);
		if(n>1) for(int i=3;i<=n+2;i++) printf("2 %d\n",i);
		if(n>2) for(int i=4;i<=n+1;i++) printf("3 %d\n",i); 
	}
	return 0;
}