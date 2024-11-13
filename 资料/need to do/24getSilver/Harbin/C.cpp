#include<cstdio>
int n,t,now,s,nxt;
char c[2],v[4]={'N','E','S','W'};
int get(char a){for(int i=0;i<4;i++) if(a==v[i]) return i;}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%s%d",&n,&c,&s),
		now=get(c[0]);
		printf("%d %c\n",n*2-1,c[0]);
		printf("Z %d\n",s);
		for(int i=2;i<=n;i++){
			scanf("%s%d",&c,&s);
			nxt=get(c[0]);
			if((nxt-now+4)%4==1) printf("R\n");
			else printf("L\n");
			printf("Z %d\n",s);
			now=nxt;
		} 
	}
	return 0;
}