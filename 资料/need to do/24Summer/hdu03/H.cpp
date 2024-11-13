#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
struct node{
	int num;
	long long dis;
	friend bool operator < (node x,node y){
		return x.dis>y.dis;
	}
}a[200005],tmp;
struct E{
	int to,nxt;
	long long w;
}e[1000005];
priority_queue<node> q;
int t,n,m,cnt,ncnt,h,now,acnt;
long long dis[100005],k;
int hd[100005];
bool vis[100005];
bool cmp(node x,node y){return x.dis<y.dis;}
void EE(int u,int v,long long w){
	e[++cnt].to=v;
	e[cnt].nxt=hd[u];
	e[cnt].w=w;
	hd[u]=cnt;
	return;
}
void dijkstra(){
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis)),dis[1]=0;
	q.push(node{1,0});
	while(!q.empty()){
		tmp=q.top(),q.pop();
		int u=tmp.num,v;
		long long w;
		if(vis[u]) continue;
		vis[u]=1,a[++ncnt]=node{u,dis[u]};
		for(int i=hd[u];i;i=e[i].nxt){
			v=e[i].to,w=e[i].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push(node{v,dis[v]});
			}
		}
	}
	return;
}
void add_edge(int x,int b){
	if(b==h){
		if(now>n) return;
		if(vis[now]) return;
		vis[now]=1;
		acnt++;
		return EE(x,now,k*(x|now));
	}
	if(acnt>=n/2) return;
	add_edge(x,b+1);
	if(!(x&(1<<b))){
		now^=(1<<b);
		add_edge(x,b+1);
		now^=(1<<b);
	}
	return;
}
int main(){
	scanf("%d",&t);
	while(t--){
		memset(hd,0,sizeof(hd));
		scanf("%d%d%lld",&n,&m,&k),acnt=ncnt=cnt=h=0;
		for(int i=1,u,v,w;i<=m;i++) scanf("%d%d%d",&u,&v,&w),EE(u,v,w),EE(v,u,w);
		dijkstra();
		sort(a+1,a+ncnt+1,cmp);
		int x=n;
		while(x) x>>=1,h++;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=ncnt;i++){
			x=a[i].num;
			if(x&1) continue;
			now=x;
			add_edge(x,1);
			if(acnt>=n/2) break;
		}
		for(int i=2;i<=n;i++) EE(1,i,k*(1|i));
		dijkstra();
		for(int i=2;i<=n;i++) printf("%lld ",dis[i]);
		printf("\n");
	}
	return 0;
}