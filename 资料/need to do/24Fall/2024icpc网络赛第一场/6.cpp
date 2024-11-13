#include<cstdio>
#include<queue>
using namespace std;
#define MAXN 200010
int n;
int a[MAXN];

struct node{
	int id,x,w;
	int l,r;
	friend bool operator < (node a,node b){
		return a.x>b.x;
	}
} p[MAXN];
int cnt=0;
priority_queue <node> q;

void solve(){
	cnt=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		if(cnt && x==p[cnt].x){
			p[cnt].w++;
		}else{
			p[++cnt].x=x;
			p[cnt].w=1;
		}
	}
	for(int i=1;i<=cnt;i++){
		p[i].id=i;
		p[i].l=i-1;
		p[i].r=i+1;
		q.push(p[i]);
	}
	long long ans=0;
	while(!q.empty()){
		node now=q.top();
		q.pop();
		int l=p[now.id].l,r=p[now.id].r,w=p[now.id].w,x=p[now.id].x;
		if(!l && r==cnt+1) break;
		// printf("%d %d %d %d\n",x,w,l,r);
		if(l && p[l].x==x)
			p[l].w+=w;
		else if(r<=cnt && p[r].x==x)
			p[r].w+=w;
		else{
			ans+=w;
			if(!l) p[r].w+=w;
			else if(r==cnt+1) p[l].w+=w;
			else if(p[l].x<=p[r].x)
				p[l].w+=w;
			else
				p[r].w+=w;
		}
		p[r].l=l;
		p[l].r=r;
	}
	printf("%lld\n",ans);
	for(int i=1;i<cnt;i++)
		p[i]=(node){0,0,0,0,0};
	while(!q.empty()) q.pop();
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

/*

4
2
1 2
2
2 2
7
1 1 1 2 2 2 2
3
1 2 3
*/