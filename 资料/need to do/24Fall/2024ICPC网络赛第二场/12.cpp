#include<cstdio>
#include<cmath>
using namespace std;
#define ll long long

int n;
ll T;
ll gcd(ll a,ll b){ return b==0?a:gcd(b,a%b); }
double f(ll x) { return 1.0*x/2+1.0*T/x-0.5; }

int main()
{
	scanf("%d",&n);
	while(n--){
		scanf("%lld",&T);
		double x = (sqrt(8*T+1)-1)/2;
		// printf("%lf\n",x);
		if(x>=T){
			ll x1=T*(T+1),y1=2;
			if(x1%2==0) x1/=2,y1/=2;
			printf("%lld %lld\n",x1,y1);
		}else {
			ll a=ceil(x),b=floor(x);
			// printf("%lld %lld\n",a,b);
			if(f(a)<f(b)){
				x=a;
			}else x=b;
			// printf("%lf\n",x);
			ll x1=x*x-x+2*T;
			ll y1=2*x;
			ll g=gcd(x1,y1);
			printf("%lld %lld\n",x1/g,y1/g);
		}
	}
}