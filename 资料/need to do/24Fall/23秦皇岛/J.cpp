#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,s[20],a,ans,cnt,sum;
bool cmp(int x,int y){return x>y;}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a),s[a]++;
	sort(s+1,s+14,cmp);
	while(cnt<13){
		ans++,sum=0;
		for(int i=1;i<=13;i++) if(s[i]!=-1&&sum+s[i]<=m) sum+=s[i],s[i]=-1,cnt++;
	}
	printf("%d\n",ans);
	return 0;
}