#include<cstdio>
#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
#define int long long
#define RI register int
#define CI const int&
using namespace std;
namespace Pollard_Rho
{
	mt19937_64 rnd(20030909);
	inline int quick_mul(CI x,CI y,CI mod)
	{
		return (__int128)(x)*y%mod;
	}
	inline int sum(CI x,CI y,CI mod)
	{
		return x+y>=mod?x+y-mod:x+y;
	}
	inline int sub(CI x,CI y,CI mod)
	{
		return x-y<0?x-y+mod:x-y;
	}
	inline int quick_pow(int x,int p,int mod,int mul=1)
	{
		for (;p;p>>=1,x=quick_mul(x,x,mod)) if (p&1) mul=quick_mul(mul,x,mod); return mul;
	}
	inline bool Miller_Rabin(CI n)
	{
		if (n<=1) return 0;
        vector <int> base={2,3,5,7,11,13,17,19,23};
		for (int x:base)
		{
			if (n==x) return 1;
			if (n%x==0) return 0;
		}
		int m=(n-1)>>__builtin_ctzll(n-1);
		for (int x:base)
		{
			int t=m,a=quick_pow(x,m,n);
			while (t!=n-1&&a!=1&&a!=n-1) a=quick_mul(a,a,n),t*=2;
			if (a!=n-1&&t%2==0) return 0;
		}
		return 1;
	}
	inline int get_fact(CI n)
	{
		if (n%2==0) return 2;
		auto f=[&](CI x)
		{
			return sum(quick_mul(x,x,n),1,n);
		};
		int x=0,y=0,tot=0,p=1,q,g;
		for (int i=0;(i&0xff)||(g=__gcd(p,n))==1;++i,x=f(x),y=f(f(y)))
		{
			if (x==y) x=tot++,y=f(x);
			q=quick_mul(p,sub(x,y,n),n); if (q) p=q;
		}
		return g;
	}
	inline vector <int> solve(CI n)
	{
		if (n==1) return {};
		if (Miller_Rabin(n)) return {n};
		int d=get_fact(n); auto v1=solve(d),v2=solve(n/d);
		auto i1=v1.begin(),i2=v2.begin(); vector <int> ans;
		while (i1!=v1.end()||i2!=v2.end())
		{
			if (i1==v1.end()) ans.push_back(*i2++);
			else if (i2==v2.end()) ans.push_back(*i1++);
			else ans.push_back(*i1<*i2?*i1++:*i2++);
		}
		return ans;
	}
};
using namespace Pollard_Rho;
int t,n,r,ans; vector <int> p,c;
inline int S(int x)
{
    int ret=0; while (x) ret+=x%10,x/=10; return ret;
}
inline void DFS(CI now=0,CI m=1)
{
    if (now>=(int)p.size())
    {
        int tmp=S(m);
        if (tmp==r&&n%m==tmp) ++ans;
        return;
    }
    int cur=1; for (RI i=0;i<=c[now];++i) DFS(now+1,m*cur),cur*=p[now];
}
signed main()
{
    for (scanf("%lld",&t);t;--t)
    {
        scanf("%lld",&n); ans=0;
        for (r=1;r<=min(108LL,n-1);++r)
        {
            auto fact=solve(n-r);
            p.clear(); c.clear();
            for (auto x:fact)
            if (p.empty()||x!=p.back()) p.push_back(x),c.push_back(1); else ++c.back();
            DFS();
        }
        printf("%lld\n",ans);
    }
    return 0;
}