#include<cstdio>
int n,t,cnt,ans[40];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		if((n&1)==0&&(n&2)==0){
			printf("NO\n");
			cnontinue;
		}
		else{
			printf("YES\n"),cnt=1;
			ans[cnt]=1;
			for(int i=31;i>=2;i--){
				if(n&(1<<i)) ans[++cnt]=1;
				else ans[++cnt]=-1;
			}
			if((n&2)==0) ans[++cnt]=-1;
			else ans[++cnt]=n&1;
			for(int i=32;i>=1;i--){
				printf("%d ",ans[i]);
				if(i%8==1) printf("\n");
			}
		}
	}
	return 0;
}