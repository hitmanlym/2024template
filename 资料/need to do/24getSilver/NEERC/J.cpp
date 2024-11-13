#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

int n,m,k;
char s[200010];
int cnt[30];
bool f[30][30010];
int pre[30][30010];

void solve(){
	scanf("%d%d%d",&n,&m,&k);
	scanf("%s",s+1);
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=k;i++)
		cnt[s[i]-'A'+1]++;
	int del=k-(n+m);
	int ans=1e9;
	for(int i=1;i<=26;i++){
		if(!cnt[i]) continue;
		for(int c=1;c<=26;c++)
			for(int i=0;i<=n;i++)
				f[c][i]=pre[c][i]=0;
		f[0][0]=1;
		for(int j=1;j<=26;j++){
			for(int v=0;v<=n;v++){
				if(f[j-1][v]){
					f[j][v]=true;
					pre[j][v]=v;
				}
			}
			if(i==j) continue;
			for(int v=cnt[j];v<=n;v++){
				if(f[j-1][v-cnt[j]]){
					f[j][v]=true;
					pre[j][v]=v-cnt[j];
				}
			}
		}
		// printf("%d\n",(int)f[26][0]);
		for(int v=n;v>=max(n-cnt[i],0);v--){
			if(f[26][v]){
				int sum=k-cnt[i],now=v,j=26;
				while(j){
					sum-=now-pre[j][now];
					now=pre[j][now];
					j--;
				}
				if(sum>=m){
					printf("0\n");
					return;
				}
				ans=min(ans,(n-v)*(m-sum));
			}
		}
	}
	printf("%d\n",ans);
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