#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
#define MAXN 2000010

int n,m=0;
int a[MAXN],b[MAXN];
vector <int> e[MAXN];
int sta[MAXN],top=0,in[MAXN];
priority_queue <int> q;
int tpA[MAXN],tpB[MAXN];
int cmp(int a,int b){ return a>b; }

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;i++){
		while(top && sta[top]<a[i]) top--;
		if(top){
			e[sta[top]].push_back(a[i]);
			in[a[i]]++;
			m++;
		}
		sta[++top]=a[i];
	}
	top=0;
	for(int i=1;i<=n;i++){
		while(top && sta[top]>b[i]) top--;
		if(top){
			e[sta[top]].push_back(b[i]);
			in[b[i]]++;
			m++;
		}
		sta[++top]=b[i];
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
		if(!in[i]) q.push(-i);
	while(!q.empty()){
		int u=-q.top();
		q.pop();
		tpA[++cnt]=u;
		for(int i=0;i<(int)e[u].size();i++){
			int v=e[u][i];
			in[v]--;
			if(!in[v])
				q.push(-v);
		}
	}
	if(cnt<n){
		printf("No\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
		if(tpA[i]!=a[i]){
			printf("No\n");
			return 0;
		}
	for(int i=1;i<=n;i++){
		for(int j=0;j<(int)e[i].size();j++)
			in[e[i][j]]++;
	}
	for(int i=n;i>=1;i--)
		if(!in[i]) q.push(i);
	cnt=0;
	while(!q.empty()){
		int u=q.top();
		q.pop();
		tpB[++cnt]=u;
		for(int i=(int)e[u].size()-1;i>=0;i--){
			int v=e[u][i];
			in[v]--;
			if(!in[v])
				q.push(v);
		}
	}
	// for(int i=1;i<=n;i++)
	// 	printf("%d ",tpB[i]);
	// printf("\n");
	for(int i=1;i<=n;i++){
		if(tpB[i]!=b[i]){
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
	printf("%d\n",m);
	for(int u=1;u<=n;u++){
		for(int i=0;i<(int)e[u].size();i++){
			int v=e[u][i];
			printf("%d %d\n",u,v);
		}
	}
	return 0;
}