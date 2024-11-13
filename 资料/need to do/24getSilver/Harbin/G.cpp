#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
#define MAXN 200010
#define MAXM 500010


int read(){
	char c=getchar();
	int ret=0;
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		ret=(ret<<1)+(ret<<3)+(c^48);
		c=getchar();
	}
	return ret;
}
int n,m,k;
bool vis[MAXN],out[MAXN];
int f[MAXN];
int find(int x){ return f[x]==x?x:f[x]=find(f[x]); }
struct node{
	int u,v;
} ed[MAXM];
vector <int> e[MAXN];
vector <int> ans[MAXN];
queue <int> q;

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++){
		int x=read();
		vis[x]=true;
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		if(vis[u] && vis[v]){
			i--;
			m--;
			continue;
		}
		ed[i].u=u,ed[i].v=v;
	}

	for(int i=1;i<=n;i++)
		f[i]=i;
	for(int i=1;i<=m;i++){
		int u=ed[i].u,v=ed[i].v;
		if(find(u)!=find(v))
			f[find(u)]=find(v);
	}
	for(int i=2;i<=n;i++)
		if(find(i)!=find(1)){
			printf("No\n");
			return 0;
		}

	for(int i=1;i<=n;i++)
		f[i]=i;
	for(int i=1;i<=m;i++){
		int u=ed[i].u,v=ed[i].v;
		if(vis[u] || vis[v]) continue;
		if(find(u)!=find(v)){
			f[find(u)]=find(v);
		}
	}
	int id=0;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			id=i;
			break;
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i] && find(i)!=find(id)){
			printf("No\n");
			return 0;
		}
	}
	for(int i=1;i<=m;i++){
		int u=ed[i].u,v=ed[i].v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	printf("Yes\n");
	q.push(id);
	out[id]=true;
	int cnt=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		if(vis[u]) continue;
		++cnt;
		ans[cnt].clear();
		ans[cnt].push_back(u);
		for(int i=0;i<(int)e[u].size();i++){
			int v=e[u][i];
			if(out[v]) continue;
			ans[cnt].push_back(v);
			q.push(v);
			out[v]=true;
		}
		if(ans[cnt].size()==1) cnt--;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++){
		printf("%d %d ",ans[i][0],ans[i].size()-1);
		for(int j=1;j<(int)ans[i].size();j++)
			printf("%d ",ans[i][j]);
		printf("\n");
	}
	return 0;
}