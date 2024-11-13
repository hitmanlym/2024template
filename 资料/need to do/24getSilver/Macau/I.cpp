#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 1000010

int a,b,m;
int f[MAXN];

void solve(){
	scanf("%d%d%d",&a,&b,&m);
	f[0]=2;
	int x=b/a;
	for(int i=1;i<=m;i++){
		f[i]=f[i-1];
		if(i>=a)
			f[i]=max(f[i],f[i-a]+1);
		if(i>=b)
			f[i]=max(f[i],f[i-b]+x+1);
		if(i>=a*(x+1))
			f[i]=max(f[i],f[i-a*(x+1)]+x+2);
	}
	printf("%d\n",f[m]*160);
	return;
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}