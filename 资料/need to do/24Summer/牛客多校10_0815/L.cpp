#include<cstdio>
#include<queue>
using namespace std;
#define MAXN 100005

int n,m,mp;
struct edge{
	int v,nxt;
} e[MAXN*30];
int head[MAXN],cnt=0;
void ad(int u,int v){
	e[++cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int mi[10],bit[10];
int get(int x,int l,int r,int typ){
	for(int i=1;i<=n;i++)
		bit[i]=x/mi[n-i]%10;
	for(int i=l;i<=r;i++)
		bit[i]=(bit[i]+typ+10)%10;
	int y=0;
	for(int i=1;i<=n;i++)
		y+=bit[i]*mi[n-i];
	// printf("get:%d->%d\n",x,y);
	return y;
}

int mt[MAXN],ok[MAXN],arr[MAXN];
queue <pair<int,int>> q;
void bfs(int x,int t){
	q.push(make_pair(x,0));
	mt[x]=0;
	while(!q.empty()){
		int nx=q.front().first,nt=q.front().second;
		q.pop();
		// if(nt==0 && t!=1) ok[nx]=1;
		// else if(n!=1)
		// 	ok[nx]=1;
		// else if(n==1 && (t-nt)%2==0)
		// 	ok[nx]=1;
		if(n==1){
			if((t-nt)%2==0)
				ok[nx]=1;
		}else {
			if(nt!=0 || t!=1) ok[nx]=1;
		}
		if(nt==t) continue;
		for(int i=head[nx];i;i=e[i].nxt){
			int v=e[i].v,vt=nt+1;
			if(mt[v]==-1){
				mt[v]=vt;
				q.push(make_pair(v,vt));
			}
		}
	}
}

void solve(){
	scanf("%d%d",&n,&m);
	mp=mi[n]-1;
	for(int i=0;i<=mp;i++){
		for(int l=1;l<=n;l++)
			for(int r=l;r<=n;r++){
				ad(i,get(i,l,r,-1));
				ad(i,get(i,l,r,1));
			}
		arr[i]=0;
	}
	for(int i=1;i<=m;i++){
		int x,t;
		scanf("%d%d",&x,&t);
		for(int j=0;j<=mp;j++)
			mt[j]=-1,ok[j]=0;
		bfs(x,t);
		for(int j=0;j<=mp;j++)
			if(ok[j]) arr[j]++;
	}
	int id=-1;
	for(int i=0;i<=mp;i++)
		if(arr[i]==m) {
			if(id!=-1){
				puts("MANY");
				return;
			}else id=i;
		}
	if(id==-1) puts("IMPOSSIBLE");
	else {
		for(int i=1;i<=n;i++)
			printf("%d",id/mi[n-i]%10);
		printf("\n");
	}
}

void clear(){
	cnt=0;
	for(int i=0;i<=mp;i++) head[i]=0;
}


int main()
{
	int t;
	scanf("%d",&t);
	mi[0]=1;
	for(int i=1;i<=5;i++) mi[i]=mi[i-1]*10;
	while(t--){
		solve();
		clear();
	}
	return 0;
}