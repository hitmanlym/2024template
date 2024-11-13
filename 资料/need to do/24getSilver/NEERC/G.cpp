#include<cstdio>
using namespace std;

int n,m;
int s[110],h[110],ls[110],rs[110];
int a[110],id[110];
bool vis[110];
int sta[110],top=0;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&s[i],&h[i]);
		id[s[i]]=i;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++){
		int now=h[i];
		ls[i]=rs[i]=s[i];
		for(ls[i]=s[i]-1;ls[i]>=1;ls[i]--){
			now+=a[ls[i]];
			if(now<0){
				ls[i]++;
				break;
			}
		}
		now=h[i];
		for(rs[i]=s[i]+1;rs[i]<=n;rs[i]++){
			now+=a[rs[i]];
			if(now<0){
				rs[i]--;
				break;
			}
		}
	}

	// printf("ls,rs:\n");
	// for(int i=1;i<=m;i++)
	// 	printf("%d %d\n",ls[i],rs[i]);
	// printf("\n");

	for(int i=1;i<=n;i++){
		int l=i,r=i;
		top=0;
		for(int j=1;j<=m;j++) vis[j]=false;
		for(int j=i-1;j>=1;j--){
			if(a[j]==0 && id[j] && rs[id[j]]>=l){
				l=j;
				sta[++top]=id[j];
			}
		}
		if(l<i) r=i+1;
		for(int j=i+1;j<=n;j++)
			if(a[j]==0 && id[j] && ls[id[j]]<=r){
				r=j;
				sta[++top]=id[j];
			}
		bool flag=true;
		for(int j=1;j<=m;j++)
			if(s[j]<l || s[j]>r){
				flag=false;
				break;
			}
		if(flag){
			printf("%d\n",i);
			for(int j=1;j<=top;j++){
				printf("%d ",sta[j]);
				vis[sta[j]]=true;
			}
			for(int j=1;j<=m;j++){
				if(!vis[j])
					printf("%d ",j);
			}
			return 0;
		}
		l=i,r=i;
		top=0;
		for(int j=1;j<=m;j++) vis[j]=false;
		for(int j=i+1;j<=n;j++)
			if(a[j]==0 && id[j] && ls[id[j]]<=r){
				r=j;
				sta[++top]=id[j];
			}
		if(r>i) l=i-1;
		for(int j=i-1;j>=1;j--){
			if(a[j]==0 && id[j] && rs[id[j]]>=l){
				l=j;
				sta[++top]=id[j];
			}
		}
		flag=true;
		for(int j=1;j<=m;j++)
			if(s[j]<l || s[j]>r){
				flag=false;
				break;
			}
		if(flag){
			printf("%d\n",i);
			for(int j=1;j<=top;j++){
				printf("%d ",sta[j]);
				vis[sta[j]]=true;
			}
			for(int j=1;j<=m;j++){
				if(!vis[j])
					printf("%d ",j);
			}
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}