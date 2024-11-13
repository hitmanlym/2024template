#include<cstdio>
int n,k,x,y;
int main(){
	scanf("%d%d",&n,&k),x=y=1;
	for(int i=1;i<n;i++) printf("%d %d\n%d %d\n",i,i,i,i+1);
	printf("%d %d\n%d %d\n",n,n,n,1);
	for(int i=n*2+1;i<=k;i++){
		while(true){
			if(y>n) x++,y=1;
			if(x==y||(y==x+1&&x!=n)||(x==n&&y==1)) y++;
			else break;
		}
		printf("%d %d\n",x,y);
		y++;
	} 
	return 0;
}