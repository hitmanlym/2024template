#include<bits/stdc++.h>
#include<queue>
using namespace std;
#define MAXN 200010
#define MAXM 500010
#define mp(x,y) make_pair(x,y)

int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x;
}
int n,m,d;
struct edge{
	int v,nxt;
} e[MAXM*2];
int head[MAXN],cnt=0;
void ad(int u,int v){
	e[++cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

bool vis[MAXN];
int f[MAXN][2],g[MAXN][2];
int pre[MAXN][2];
queue <pair<int,int>> q;
void bfs1(){
	for(int i=1;i<=n;i++){
		f[i][0]=f[i][1]=1e9;
		if(vis[i]) {
			q.push(mp(i,0));
			f[i][0]=0;
		}
	}
	while(!q.empty()){
		int u=q.front().first,step=q.front().second;
		q.pop();
		if(step==d) continue;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].v;
			int c=step&1;
			if(f[v][c^1]>step+1){
				f[v][c^1]=step+1;
				q.push(mp(v,step+1));
			}
		}
	}
}
void bfs2(){
	for(int i=1;i<=n;i++){
		g[i][0]=g[i][1]=1e9;
		pre[i][0]=pre[i][1]=0;
	}
	g[1][0]=0;
	q.push(mp(1,0));
	while(!q.empty()){
		int u=q.front().first,step=q.front().second;
		q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].v;
			int c=step&1;
			if((f[v][c^1]>step+1) && g[v][c^1]>step+1){
			// printf("v=%d\n",v);
				g[v][c^1]=step+1;
				pre[v][c^1]=u;
				q.push(mp(v,step+1));
			}
		}
	}
}

int sta[MAXN*2],top=0;
void solve()
{
	// scanf("%d%d%d",&n,&m,&d);
	n=read(),m=read(),d=read();
	for(int i=1;i<=n;i++)
		head[i]=vis[i]=0;
	cnt=0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		ad(u,v);
		ad(v,u);
	}
	int k=read();
	for(int i=1;i<=k;i++){
		int x=read();
		vis[x]=true;
	}
	bfs1();

	// printf("f:\n");
	// for(int i=1;i<=n;i++){
	// 	printf("i=%d f[0]=%d f[1]=%d\n",i,f[i][0],f[i][1]);
	// }
	// printf("\n");

	bfs2();

	// printf("g:\n");
	// for(int i=1;i<=n;i++){
	// 	printf("i=%d f[0]=%d f[1]=%d\n",i,g[i][0],g[i][1]);
	// }
	// printf("\n");

	if(g[n][0]==1e9 && g[n][1]==1e9)
		printf("-1\n");
	else {
		top=0;
		sta[++top]=n;
		int now=n,step=g[n][0];
		if(g[n][0]>g[n][1])
			step=g[n][1];
		printf("%d\n",step);
		while(step>0){
			now=pre[now][step&1];
			sta[++top]=now;
			step--;
		}
		while(top)
			printf("%d ",sta[top--]);
		printf("\n");
	}
}

int main()
{
	int t;
	// scanf("%d",&t);
	t=read();
	while(t--)
		solve();
	return 0;
}