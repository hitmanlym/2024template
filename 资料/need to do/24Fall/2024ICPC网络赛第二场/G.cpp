#include<cstdio>
using namespace std;
#define ll long long

const int mo=998244353;
int x,y,a0,a1,b;

ll qmi(ll x,int y=mo-2){
	ll ans=1;
	while(y){
		if(y&1) ans=1ll*ans*x%mo;
		y>>=1;
		x=1ll*x*x%mo;
	}
	return ans;
}
ll gcd(ll a,ll b){ return b==0?a:gcd(b,a%b); }

void solve(){
	// printf("%lld\n",3*qmi(4)%mo);
	scanf("%d%d",&x,&y);
	scanf("%d%d%d",&a0,&a1,&b);
	ll p=a0*qmi(a0+a1)%mo;
	if(x==y){
		printf("%lld\n",p);
	}else {
		ll ans=0,f=1;
		while(1){
			if(y%x==0){
				ans=(ans+f*qmi(p,y/x)%mo)%mo;
				break;
			}else if(x%y==0){
				ans=(ans+f*(1-qmi(1-p,x/y))%mo+mo)%mo;
				break;
			}
			if(x>y){
				ll t=x/y;
				ans=(ans+f*(1-qmi(1-p,t))%mo+mo)%mo;
				f=(f*qmi(1-p,t)%mo+mo)%mo;
				x%=y;
			}else if(x<y){
				ll t=y/x;
				f=f*qmi(p,t)%mo;
				y%=x;
			}
		}
		printf("%lld\n",ans);
	}
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}