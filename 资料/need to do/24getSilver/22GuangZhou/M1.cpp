#include<cstdio>
using namespace std;

int n,m,k,ans;
int a[20];
int t[20];
void dfs(int id,int sum){
	// printf("!! %d\n",id);
	if(sum>n) return;
	if(id>k){
		if(sum==n){
			ans++;
			for(int i=1;i<=k;i++)
				printf("%d ",a[i]);
			printf("\n");
			int now=0;
			for(int i=1;i<=k;i++)
				if(a[i]==m) now++;
			t[now]++;
		}
			return;
	}
	for(int i=0;i<=m;i++){
		a[id]=i;
		int ns=0;
		for(int j=1;j<id;j++)
			ns+=a[id]^a[j];
		dfs(id+1,sum+ns);
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	// printf("!\n");
	dfs(1,0);
	printf("%d\n",ans);
	for(int i=0;i<=k;i++)
		printf("%d ",t[i]);
	printf("\n");
	return 0;
}