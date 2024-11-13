#include<cstdio>
using namespace std;
#define ll long long
const ll mo = 998244353;
#define MAXN 1000010

ll qmi(ll x, ll y = mo - 2){
	ll ans = 1;
	while(y){
		if(y & 1) ans = ans * x % mo;
		x = x * x % mo;
		y >>= 1;
	}
	return ans;
}

int n,m;
ll f[MAXN],p;
void solve(){
	scanf("%d%d",&n,&m);
	ll ansmax = 1, mi26 = 1;
	for(int i = 1; i <= m; i ++){
		mi26 *= 26;
		if(mi26 >= n) mi26 = n;
		ansmax += mi26;
	}
	printf("%lld ",ansmax%mo);
	for(int i = 1; i <= m; i ++)
		f[i] =(1 - qmi((1 - qmi(qmi(26), i) + mo) % mo, n) + mo)% mo;
	ll ans = 1;
	for(int i = 1; i <= m; i ++)
		ans = (ans + f[i] * qmi(26, i) % mo) % mo;
	printf("%lld\n", ans);
}

int main()
{
	solve();
	return 0;
}