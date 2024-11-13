#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

int id[1000];
void solve(){
	memset(id,0,sizeof(id));
	int n,m,hp,dmg,k;
	scanf("%d%d%d%d",&n,&m,&hp,&dmg);
	k=hp/m;
	// printf("k=%d\n",k);
	for(int i=1;i<=m;i++){
		if(k) id[i]=(k-1)%5+1;
		else id[i]=-1;
	}
	// for(int j=1;j<=m;j++){
	// 	if(id[j]==0) putchar('.');
	// 	else if(id[j]>0) putchar('A'+id[j]-1);
	// 	else putchar(' ');
	// }
	// puts("");

	hp%=m;
	// printf("%d\n",hp);
	for(int i=1;i<=hp;i++) id[i]=k%5+1;
	for(int i=1,now=hp;i<=min(dmg,m);i++){
		if(now==0) now=m;
		id[now]=0;
		now--;
	}

	putchar('+');
	for(int i=1;i<=m;i++) putchar('-');
	putchar('+');
	puts("");
	for(int i=1;i<=n;i++){
		putchar('|');
		for(int j=1;j<=m;j++){
			if(id[j]==0) putchar('.');
			else if(id[j]>0) putchar('A'+id[j]-1);
			else putchar(' ');
		}
		putchar('|');
		puts("");
	}
	putchar('+');
	for(int i=1;i<=m;i++) putchar('-');
	putchar('+');
	puts("");
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}