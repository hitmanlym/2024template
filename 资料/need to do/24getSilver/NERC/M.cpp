#include<cstdio>
#include<unordered_map>
using namespace std;
unordered_map<int,int> s;
int a[2005],n,t,ans;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n),ans=0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=2;i<n;i++){
			s.clear();
			for(int j=1;j<i;j++) s[a[i]-a[j]]++;
			for(int j=i+1;j<=n;j++) ans+=s[a[j]-a[i]];
		}
		printf("%d\n",ans);
	}
	return 0;
}