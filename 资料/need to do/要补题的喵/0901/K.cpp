#include<cstdio>
#include<bitset>
#include<unordered_map>
using namespace std;
#define ull unsigned long long

int n,m;
int a[200][200];

bool use[10];
int sit[362900],cnt=0;
unordered_map <int,int> mp;
bitset <362881> vis[2];
void dfs(int id,int now){
	if(id==n+1){
		sit[++cnt]=now;
		mp[now]=cnt;
		return;
	}
	for(int i=1;i<=n;i++){
		if(use[i]) continue;
		use[i]=true;
		dfs(id+1,(now<<1)+(now<<3)+i);
		use[i]=false;
	}
}
int change(int id,int now){
	int A[10],B[10];
	for(int i=1;i<=n;i++)
		A[i]=a[id][i];
	for(int i=n;i>=1;i--){
		B[i]=now%10;
		now/=10;
	}
	now=0;
	for(int i=1;i<=n;i++){
		int x=A[B[i]];
		now=(now<<1)+(now<<3)+x;
	}
	return now;
}

void solve1(){
	dfs(1,0);
	int cur=0;
	for(int i=m;i>=1;i--){
		for(int j=1;j<=cnt;j++){
			if(vis[cur][j]==1)
				vis[cur^1][mp[change(i,sit[j])]]=1;
		}
		int now=0;
		for(int j=1;j<=n;j++)
			now=(now<<1)+(now<<3)+a[i][j];
		// printf("now=%d\n",now);
		vis[cur^1][mp[now]]=1;
		vis[cur^1]|=vis[cur];
		cur^=1;
	}
	int ans=0;
	for(int i=1;i<=cnt;i++)
		if(vis[cur][i]) ans++;
	printf("%d\n",ans);
}


const ull bas=13131;
unordered_map <ull,bool> mp1;
int A[2][200];

void solve2(){
	bool flag=false;
	for(int s=1;s<(1<<m);s++){
		flag=false;
		int cur=0;
		for(int i=m;i>=1;i--){
			if(s>>(i-1)&1){
				if(!flag){
					for(int j=1;j<=n;j++)
						A[cur][j]=a[i][j];
					flag=true;
				}else {
					for(int j=1;j<=n;j++)
						A[cur^1][j]=a[i][A[cur][j]];
					cur^=1;
				}
			}
		}
		ull now=0;
		for(int i=1;i<=n;i++)
			now=now*bas+A[cur][i];
		mp1[now]=1;
	}
	printf("%d\n",(int)mp1.size());
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	if(n<=9)
		solve1();
	else
		solve2();
	return 0;
}