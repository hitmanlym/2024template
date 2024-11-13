#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,anc[20100][16],dep[20100];
ll val[20100];
struct lb{//linear basis?
	ll d[64];
	void print(){
		for(int i=0;i<=62;i++)if(d[i])printf("%d:%lld\n",i,d[i]);
	}
	lb(){memset(d,0,sizeof(d));}
	void operator +=(ll x){
		for(int i=62;i>=0;i--){
			if(!(x&(1ll<<i)))continue;
			if(d[i])x^=d[i];
			else{d[i]=x;break;}
		}
	}
	ll& operator [](int x){
		return d[x];
	}
	void operator +=(lb &x){
		for(int i=62;i>=0;i--)if(x[i])*this+=x[i];
	}
	friend lb operator +(lb &x,lb &y){
		lb z=x;
		for(int i=62;i>=0;i--)if(y[i])z+=y[i];
		return z;
	}
	ll calc(){
//		print();
		ll res=0;
		for(int i=62;i>=0;i--)if((res^d[i])>res)res^=d[i];
		return res;
	}
}LB[20100][16];
vector<int>v[20100];
void dfs(int x){
	LB[x][0]+=val[x];
	for(int y:v[x])if(y!=anc[x][0])dep[y]=dep[x]+1,anc[y][0]=x,dfs(y);
} 
ll query(int x,int y){
	lb z;
	if(dep[x]<dep[y])swap(x,y);
	for(int i=15;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])z+=LB[x][i],x=anc[x][i];
	if(x==y){z+=val[x];return z.calc();}
	for(int i=15;i>=0;i--)if(anc[x][i]!=anc[y][i])z+=LB[x][i],z+=LB[y][i],x=anc[x][i],y=anc[y][i];
	z+=LB[x][0];
	z+=LB[y][0];
	z+=val[anc[x][0]];
	return z.calc();
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&val[i]);
	for(int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),v[x].push_back(y),v[y].push_back(x);
	dfs(1);
	for(int j=1;j<=15;j++)for(int i=1;i<=n;i++)anc[i][j]=anc[anc[i][j-1]][j-1],LB[i][j]=LB[i][j-1]+LB[anc[i][j-1]][j-1]; 
	for(int x,y;m--;)scanf("%d%d",&x,&y),printf("%lld\n",query(x,y));
	return 0;
}