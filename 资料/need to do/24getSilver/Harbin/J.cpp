#include<cstdio>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define MAXN 100010
#define ll long long

const int inf=2e9;
int n,m;
int a[MAXN],x[MAXN],t[MAXN];
struct node{
	int a,x,id;
	friend bool operator < (node a,node b){
		if(a.x!=b.x) return a.x>b.x;
		return a.a<b.a;
	}
};
priority_queue <node> q;
vector <int> ve[MAXN];
int id[MAXN];

void solve()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		ve[i].clear();
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x[i],&t[i]);
		ve[t[i]].push_back(x[i]);
	}
	for(int i=1;i<=n;i++){
		ve[i].push_back(inf);
		id[i]=0;
		q.push((node){a[i],ve[i][0],i});
	}
	ll ans=0;
	int p=1;
	while(!q.empty()){
		node now=q.top();
		q.pop();
		// printf("%d %d %d %d %lld\n",now.a,now.x,now.id,p,ans);
		if(p>m || ans+now.a<x[p]){
			ans+=now.a;
			continue;
		}else {
			now.a-=x[p]-ans;
			if(t[p]==now.id){
				now.a=a[now.id];
				id[now.id]++;
				now.x=ve[now.id][id[now.id]];
				q.push(now);
			}else {
				q.push(now);
				id[t[p]]++;
				q.push((node){a[t[p]],ve[t[p]][id[t[p]]],t[p]});
			}
			ans=x[p];
			p++;
		}
	}
	printf("%lld\n",ans);
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