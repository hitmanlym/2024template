#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 200010

int pri[MAXN],cnt=0;
bool vis[MAXN];
void getpri(int n){
	vis[1]=true;
	for(int i=2;i<=n;i++){
		if(!vis[i])
			pri[++cnt]=i;
		for(int j=1;j<=cnt && i<=n/pri[j];j++){
			vis[i*pri[j]]=true;
			if(i%pri[j]==0) break;
		}
	}
}

int n;
int a[MAXN];
int f[MAXN][4];
int main()
{
	getpri(MAXN-10);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		f[i][0]=f[i][1]=f[i][2]=f[i][3]=1e9;
	}
	f[1][0]=0;
	f[1][1]=f[1][2]=f[1][3]=1;
	for(int i=2;i<=n;i++){
		if(!vis[a[i]+a[i-1]]) f[i][0]=min(f[i][0],f[i-1][0]);
		if(a[i]&1) f[i][0]=min(f[i][0],f[i-1][2]);
		else f[i][0]=min(f[i][0],f[i-1][3]);
		if(!vis[a[i]+1]) f[i][0]=min(f[i][0],f[i-1][1]);

		if(!vis[a[i-1]+1]) f[i][1]=min(f[i][1],f[i-1][0]+1);
		f[i][1]=min(f[i][1],min(f[i-1][1],f[i-1][2])+1);

		if(a[i-1]&1) f[i][2]=min(f[i][2],f[i-1][0]+1);
		else f[i][3]=min(f[i][3],f[i-1][0]+1);
		f[i][2]=min(f[i][2],min(f[i-1][1],f[i-1][3])+1);
		f[i][3]=min(f[i][3],f[i-1][2]+1);
	}

		// printf("f:\n");
		// for(int i=1;i<=n;i++)
		// 	printf("%d:f[0]=%d f[1]=%d f[2]=%d f[3]=%d\n",i,f[i][0],f[i][1],f[i][2],f[i][3]);
		// printf("\n");

	printf("%d\n",min(min(min(f[n][0],f[n][1]),f[n][2]),f[n][3]));
	return 0;
}