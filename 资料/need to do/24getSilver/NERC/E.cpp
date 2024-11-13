#include<cstdio>
#define MAXN 200010
using namespace std;

int n,m;
struct edge{
	int v,nxt;
} e[MAXN*2];
int head[MAXN],cnt=0;
void ad(int u,int v){
	e[++cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

int dep[MAXN],maxdis[MAXN];
int c[MAXN];
void dfs(int u,int fa){
	if(c[u]) maxdis[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u);
		maxdis[u]=max(maxdis[u],maxdis[v]+1);
	}
}

int main()
{

}