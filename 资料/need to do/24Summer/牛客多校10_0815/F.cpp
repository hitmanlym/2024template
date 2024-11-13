#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
#define MAXN 1005

int read(){
	char c;
	int ret=0;
	c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		ret=(ret<<1)+(ret<<3)+(c^48);
		c=getchar();
	}
	return ret;
} 

int n;
bool vis[MAXN][MAXN];
int g[MAXN][MAXN];
char s[MAXN*MAXN];
int x[MAXN*MAXN],y[MAXN*MAXN],pn[MAXN*MAXN];
int cnt=0;

int gcd(int a,int b){ return b==0?a:gcd(b,a%b); }

void del(int i,int j){
//	printf("del:\n");
	int x1=x[i],x2=x[j],y1=y[i],y2=y[j];
	int dx=abs(x1-x2),dy=abs(y1-y2);
	int dg=g[dx][dy];
	
//	printf("%d %d %d\n",dx,dy,dg);
	
	if(!dx) {
		for(int i=1;i<=n;i++)
			vis[x1][i]=true;
		return;
	}
	if(!dy) {
		for(int i=1;i<=n;i++)
			vis[i][y1]=true;
		return;
	}
	dx/=dg,dy/=dg;
	if(x1>x2){
		swap(x1,x2);
		swap(y1,y2);
	}
	int nx=x1%dx;
	if(!nx) nx=dx;
	int ny;
	if(y1<y2) ny=y1-(x1-nx)/dx*dy;
	else ny=y1+(x1-nx)/dx*dy;
	while(ny<1 || ny>n){
		nx+=dx;
		if(y1<y2) ny+=dy;
		else ny-=dy;
	}
	while(nx<=n && ny<=n && ny>=1 && nx>=1){
		vis[nx][ny]=true;
		nx+=dx;
		if(y1<y2) ny+=dy;
		else ny-=dy;
	}
}

void solve() {
	n=read();
//	scanf("%d",&n);
	cnt=0;
	for(int i=1;i<=n*n;i++){
		x[i]=read(),y[i]=read();
//		scanf("%d%d",&x[i],&y[i]);
		vis[x[i]][y[i]]=false;
	}
	for(int i=1;i<=n*n;i++){
		if(vis[x[i]][y[i]]){
			s[i]='0';
			continue;
		}
		s[i]='1';
		vis[x[i]][y[i]]=true;
		for(int j=1;j<=cnt;j++)
			del(i,pn[j]);
		pn[++cnt]=i;
	}
	printf("%s\n",s+1);
	return;
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
//	std::cin >> t;
	for(int i=0;i<=1000;i++)
		for(int j=0;j<=1000;j++)
			g[i][j]=gcd(i,j);
	while (t --) {
		solve();
	}
	return 0;
}
/*
4
1 1
2 4
2 3
3 2
2 2
2 1
3 1
1 4
1 3
4 4
3 4
4 2
1 2
4 1
3 3
4 3
*/
