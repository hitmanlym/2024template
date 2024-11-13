#include<cstdio>
int t,n,m,k,x,y,nw;
char tp,ans[805][805];
bool f;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&m,&k);
		scanf("%d%d",&x,&y),tp=getchar();
		while(tp!='A'&&tp!='B') tp=getchar();
		k-=n+m;
		nw=(n-1)*(m-1)/2;
		if(n%2==0&&m%2==0&&(tp=='A'&&(x+y)%2==0||tp=='B'&&(x+y)%2!=0)) nw++;
		if(nw<k||k<0){
			printf("No\n");
			continue;
		}
		f=(x+y)%2;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if((i+j)%2==f) ans[i][j]=tp;
				else ans[i][j]=(tp=='A'?'B':'A');
			}
		for(int i=n-1;i>0;i--){
			for(int j=m-1;j>0;j--){
				if(nw==k) break;
				if(ans[i][j]=='A'){
					if(x==i+1&&y==j) ans[i+1][j+1]='B';
					else ans[i+1][j]='A';
					nw--;
				}
			}
		}
		printf("Yes\n");
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++) printf("%c",ans[i][j]);
			if(i<n) printf("\n");
		}
	}
	return 0;
}