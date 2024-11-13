#include<cstdio>
using namespace std;
#define MAXN 505

int n;
int a[MAXN][MAXN];
int b[MAXN][MAXN];
char s[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++)
			a[i][j]=s[j]-'0';
	}
	for(int i=2;i<=n;i++){
		for(int j=i-1;j>=1;j--){
			b[j][i]=a[j][i];
			for(int k=j+1;k<i;k++)
				if(b[j][k]) b[j][i]=(b[j][i]-a[k][i])%10;
			b[j][i]=(b[j][i]+10)%10;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			printf("%d",b[i][j]);
		printf("\n");
	}
	return 0;
}