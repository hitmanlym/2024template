#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
#define MAXN 2000010

int n,m=0;
int a[MAXN],b[MAXN];
vector <int> e[MAXN];
int sta[MAXN],top=0,in[MAXN];
queue <int> q;
map <pair<int,int>,bool> mp;

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
			if(!mp[make_pair(sta[top],a[i])]){
				mp[make_pair(sta[top],a[i])]=1;
				e[sta[top]].push_back(a[i]);
				in[a[i]]++;
				m++;
			}
		}
		sta[++top]=a[i];
	}
	top=0;
	for(int i=n;i>=1;i--){
		while(top && sta[top]>a[i]) top--;
		if(top){
			if(!mp[make_pair(a[i],sta[top])]){
				mp[make_pair(a[i],sta[top])]=1;
				e[a[i]].push_back(sta[top]);
				in[sta[top]]++;
				m++;
			}
		}
		sta[++top]=a[i];
	}
	top=0;
	for(int i=1;i<=n;i++){
		while(top && sta[top]>b[i]) top--;
		if(top){
			if(!mp[make_pair(sta[top],b[i])]){
				mp[make_pair(sta[top],b[i])]=1;
				e[sta[top]].push_back(b[i]);
				in[b[i]]++;
				m++;
			}
		}
		sta[++top]=b[i];
	}
	top=0;
	for(int i=n;i>=1;i--){
		while(top && sta[top]<b[i]) top--;
		if(top){
			if(!mp[make_pair(b[i],sta[top])]){
				mp[make_pair(b[i],sta[top])]=1;
				e[b[i]].push_back(sta[top]);
				in[sta[top]]++;
				m++;
			}
		}
		sta[++top]=b[i];
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(!in[i]) q.push(i);
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		cnt++;
		for(int i=0;i<(int)e[u].size();i++){
			int v=e[u][i];
			in[v]--;
			if(!in[v])
				q.push(v);
		}
	}
	if(cnt<n){
		printf("No\n");
	}else {
		printf("Yes\n");
		printf("%d\n",m);
		for(int u=1;u<=n;u++){
			for(int i=0;i<(int)e[u].size();i++){
				int v=e[u][i];
				printf("%d %d\n",u,v);
			}
		}
	}
	return 0;
}