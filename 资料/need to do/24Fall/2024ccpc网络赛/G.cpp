#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
#define MAXN 1005

int n,m;
int a[MAXN],v[MAXN],w[MAXN],x[MAXN],y[MAXN];
int idn[MAXN],idm[MAXN];
struct graph{
	int S,T,s,t,cntp;
	struct edge{
		int v,f,nxt;
	} e[MAXN*5*3*2];
	int head[MAXN*2],cur[MAXN*2],cnt=0;
	void ad(int u,int v,int f){
		// printf("ad:u=%d v=%d f=%d\n",u,v,f);
		e[++cnt].v=v;
		e[cnt].f=f;
		e[cnt].nxt=head[u];
		head[u]=cnt;
	}
	void add_edge(int u,int v,int a,int b){
		// printf("%d %d %d %d\n",u,v,a,b);
		if(a) ad(S,v,a),ad(v,S,0);
		if(a) ad(u,T,a),ad(T,u,0);
		if(b-a) ad(u,v,b-a),ad(v,u,0);
	}

	queue <int> q;
	int dep[MAXN*2];
	bool bfs(){
		for(int i=0;i<=cntp;i++){
			dep[i]=0;
			cur[i]=head[i];
		}
		while(!q.empty()) q.pop();
		q.push(S);
		dep[S]=1;
		while(!q.empty()){
			int u=q.front();
			// printf("u=%d\n",u);
			q.pop();
			for(int i=head[u];i!=-1;i=e[i].nxt){
				if(!e[i].f) continue;
				int v=e[i].v;
				if(!dep[v]){
					dep[v]=dep[u]+1;
					if(v==T) return true;
					q.push(v);
				}
			}
		}
		return false;
	}
	int dfs(int u,int flow){
		// printf("u=%d\n",u);
		if(u==T) return flow;
		int now=0;
		for(int i=head[u];i!=-1;i=e[i].nxt){
			int v=e[i].v;
			if(!e[i].f) continue;
			if(dep[v]!=dep[u]+1) continue;
			// printf("u=%d v=%d\n",u,v);
			int f=dfs(v,min(flow,e[i].f));
			if(f){
				e[i].f-=f;
				e[i^1].f+=f;
				now+=f;
				flow-=f;
				if(!flow) break;
			}
		}
		if(!now) dep[u]=-1;
		return now;
	}
	int dinic(){
		int ans=0;
		while(bfs()){
			// for(int i=1;i<=cntp;i++)
			// 	printf("%d ",dep[i]);
			// printf("\n");
			ans+=dfs(S,2e9);
			// printf("ans=%d\n",ans);
			// if(ans==22) 
			// 	for(int i=1;i<=1e9;i++);
			// return 0;
		}
		return ans;
	}
	void init(){
		memset(head,-1,sizeof(head));
		cnt=-1;
		cntp=4;
		S=1,T=2,s=3,t=4;
	}
	void clear(){
		memset(head,-1,sizeof(head));
		cnt=-1;
	}
	bool check(){
		for(int i=head[S];i!=-1;i=e[i].nxt)
			if(e[i].f) return false;
		for(int i=head[T];i!=-1;i=e[i].nxt)
			if(e[i^1].f) return false;
		return true;
	}
} G;

bool check(int mid){
	G.clear();
	G.add_edge(G.s,idn[1],mid,a[1]);
	G.add_edge(idn[1],G.t,v[1],2e9);
	for(int i=2;i<=n;i++){
		G.add_edge(G.s,idn[i],0,min(mid-1,a[i]));
		G.add_edge(idn[i],G.t,v[i],2e9);
	}

	for(int i=1;i<=m;i++){
		G.add_edge(idn[x[i]],idm[i],0,2e9);
		if(x[i]!=y[i]) G.add_edge(idn[y[i]],idm[i],0,2e9);
		G.add_edge(idm[i],G.t,w[i],2e9);
	}
	G.add_edge(G.t,G.s,0,2e9);
	int ans=G.dinic();
	return G.check();
}

int main()
{
	scanf("%d%d",&n,&m);
	G.init();
	for(int i=1;i<=n;i++)
		idn[i]=++G.cntp;
	for(int i=1;i<=m;i++)
		idm[i]=++G.cntp;

	// printf("idn=\n");
	// for(int i=1;i<=n;i++)
	// 	printf("%d ",idn[i]);
	// printf("\nidm=\n");
	// for(int i=1;i<=m;i++)
	// 	printf("%d ",idm[i]);
	// printf("\n");

	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i],&v[i]);
	int need = v[1];
	for(int i=1;i<=m;i++) {
		scanf("%d%d%d",&x[i],&y[i],&w[i]);
		if (x[i] == 1 || y[i] == 1) {
			need += w[i];
		}
	}
	need = std::min(need, a[1]);

	if(check(need)){
		printf("YES\n");
	}
	else printf("NO\n");
	return 0;
}