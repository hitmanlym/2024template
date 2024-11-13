#include<bits/stdc++.h>
using i64 = long long;
#define MAXN 100010
#define ll long long
using namespace std;
int pri[MAXN],cnt=0;
bool vis[MAXN];
void getpri(int n){
	vis[1]=true;
	for(int i=2;i<=n;i++){
		if(!vis[i]) pri[++cnt]=i;
		for(int j=1;j<=cnt && i<=n/pri[j];j++){
			vis[i*pri[j]]=true;
			if(i%pri[j]==0) break;
		}
	}
}

i64 n;
vector <pair<i64,int> > ve;
ll f[MAXN];
ll qmi(ll x,int y){
	ll ans=1;
	while(y){
		if(y&1) ans=ans*x;
		y>>=1;
		x=x*x;
	}
	return ans;
}
void solve() {
	ve.clear();
	scanf("%lld",&n);
	for(int i=1;i<=cnt && pri[i]<=n/pri[i];i++){
		if(n%pri[i]==0){
			ve.push_back(make_pair(pri[i],0));
			int now=ve.size()-1;
			while(n%pri[i]==0){
				n/=pri[i];
				ve[now].second++;
			}
		}
	}
	if(n!=1)
		ve.push_back(make_pair(n,1));
	if(!ve.size()){
		printf("1\n");
		return;
	}
	// printf("%d\n",ve[0].second);
	f[0]=2*ve[0].second;
	for(int i=1;i<ve.size();i++)
		f[i]=f[i-1]+(f[i-1]+1)*(2*ve[i].second);
	printf("%lld\n",f[(int)ve.size()-1]/2+1);
	return;
}
int main() {	
	getpri(100000);
	int t = 1;
	scanf("%d",&t);
	while (t --) {
		solve();
	}
	return 0;
}