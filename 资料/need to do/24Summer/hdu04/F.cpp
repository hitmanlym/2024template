#include<cstdio>
using namespace std;
#define ll long long

const ll mo=1e9+7;
int n,m,k,hp;
int f[55][55][55][6],g[55][55][55];
int a[55][55];
char s[55];
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
void solve(){
	scanf("%d%d%d%d",&n,&m,&k.&hp);
	for(int i=0;i<=m-k;i++)
		for(int x=1;x<=n;x++)
			for(int y=1;y<=n;y++)
				for(int t=0;t<=hp;t++)
					f[i][x][y][t]=0;
	for(int i=1;i<=k;i++)
		for(int x=1;x<=n;x++)
			for(int y=1;y<=n;y++)
				g[i][x][y]=0;
	int px=0,py=0,ex=0,ey=0;
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++){
			if(s[j]=='#') a[i][j]=0;
			else a[i][j]=1;
			if(s[j]=='P') 
				px=i,py=j;
			if(s[j]=='E')
				ex=i,ey=j;
		}
	}
	f[0][px][py][0]=1;
	for(int i=0;i<=m-k;i++)
		for(int x=1;x<=n;x++)
			for(int y=1;y<=n;y++){
				for(int t=0;t<=hp;t++){
					if(!f[i][x][y][t]) continue;
					for(int c=0;c<4;c++){
						int ex1=ex+x-px,ey1=ey+y-py;
						int nx=x+dx,ny=n+dy;
						if(nx<1 || nx>n || ny<1 || ny>n || a[nx][ny]==0) continue;

					}
				}
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