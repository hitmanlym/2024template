#include<bits/stdc++.h>
char m[2][1000005];
int cnt,ans,maxn,b=-1;
using namespace std;
void solve() {
	int n;
	scanf("%d%s%s",&n,m[0],m[1]);
	for(int i=0;i<n;i++){
		if(m[0][i]=='W'&&m[1][i]=='W'){
			ans+=cnt*2;
			maxn=max(ans,maxn);
			ans=0,b=-1,cnt=0;
		}
		if(m[0][i]=='R'&&m[1][i]=='R') cnt++;
		if(m[0][i]!=m[1][i]){
			if(b==-1){
				ans+=cnt*2;
				b=(m[0][i]=='R');
				ans++,cnt=0;
			}
			else if(cnt){
				if(b==(m[0][i]=='R')) ans+=cnt*2-(cnt%2);
				if(b!=(m[0][i]=='R')) ans+=cnt*2-((cnt+1)%2),b=(m[0][i]=='R');
				ans++,cnt=0;
			}
			else if(!cnt){
				if(b==(m[0][i]=='R')) ans++;
				else maxn=max(ans,maxn),ans=1,b=(m[0][i]=='R');
			}
		}
	}
	ans+=cnt*2;
	maxn=max(ans,maxn);
	printf("%d",maxn>0?maxn-1:0);
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}