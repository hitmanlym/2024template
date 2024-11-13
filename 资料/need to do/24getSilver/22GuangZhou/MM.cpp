#include<bits/stdc++.h>
#include<bits/stdc++.h>
using namespace std;
 
#define db(args...) { \
    string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
    stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); cout << '\n';}
void err(istream_iterator<string> it){}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << ' ';
    err(++it, args...);
}
#define ll long long
const ll mod=1e9+7;
ll qm(ll x){
    if(x>=mod) x-=mod;
    return x;
}
ll fpow(ll a,ll b){
    ll r=1;
    while(b){
        if(b&1) r=r*a%mod;
        a=a*a%mod;b>>=1;
    }return r;
}
ll fac[30],ivf[30];
ll C(ll n,ll m){
    if(n<m||n<0||m<0) return 0;
    return fac[n]*ivf[m]%mod*ivf[n-m]%mod;
}
ll n,m,k;
int a[60],aa;
ll f[60][200][20];
ll dfs(int o,ll p,int lim_num){
    if(p>180) return 0;
    if(o==-1) return (p==0);
    if(f[o][p][lim_num]!=-1) return f[o][p][lim_num]; 
    int nd=p+((n>>o)&1);
    ll rt=0;
    for(int i=0;i<=k;i++){ //0's num
        int res=nd-i*(k-i);
        if(res<0) continue;
        if(!a[o]){
            if(i>=lim_num){
                ll kinds=C(k-lim_num,i-lim_num);
                if(!kinds) continue;
                rt=qm(rt+kinds*dfs(o-1,res*2,lim_num)%mod);
                // cout<<"now"<<o<<" "<<p<<" "<<lim_num<<"\n";
                // cout<<"next"<<o-1<<" "<<res*2<<" "<<lim_num<<" "<<dfs(o-1,res*2,lim_num)<<"\n";
                // cout<<"kinds="<<kinds<<"\n";
                // cout<<"~~~~~~\n";
            }
        }else{
            for(int j=0;j<=min(i,lim_num);j++){ //how many lim use 1
                ll kinds=C(lim_num,j)*C(k-lim_num,i-j)%mod;
                if(!kinds) continue;
                rt=qm(rt+kinds*dfs(o-1,res*2,j)%mod);
                //if(o==0&&p==4&&)
                // cout<<"now"<<o<<" "<<p<<" "<<lim_num<<"\n";
                // cout<<"next"<<o-1<<" "<<res*2<<" "<<j<<" "<<dfs(o-1,res*2,j)<<"\n";
                // cout<<"kinds="<<kinds<<"\n";
                // cout<<"~~~\n";
            }
        }
    }
    f[o][p][lim_num]=rt;
    //cout<<o<<" "<<p<<" "<<lim_num<<" //"<<rt<<"\n";
    return rt;
}
void solve(){
    cin>>n>>m>>k;
    // if(m==0){
    //     if(n==0) cout<<1;
    //     else cout<<0;
    //     return;
    // }
    memset(f,-1,sizeof(f));
    ll M=m;
    while(M){
        a[aa++]=M&1;
        M>>=1;
    }
    //cout<<aa-1<<" "<<((n>>aa)<<1)<<" "<<k<<"\n";
    ll ans=dfs(aa-1,(n>>aa)<<1,k);
    cout<<ans;
}
signed main() {
    //ios::sync_with_stdio(0); cin.tie(0);
    fac[0]=1;
    for(int i=1;i<=20;i++) fac[i]=fac[i-1]*i%mod;
    ivf[20]=fpow(fac[20],mod-2);
    for(int i=19;i>=0;i--) ivf[i]=ivf[i+1]*(i+1)%mod;
    int t = 1;
    while (t--) solve();
    return 0;
}
/*
g++ m.cpp -std=c++20 -o m && ./m < in.txt > out.txt
*/
