#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define MAXN 100010

int read(){
	int x=0;
	scanf("%d",&x);
	return x;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x;
}
void write(int x)
{
	printf("%d",x);
	return;
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

int n,m;
struct edge{
	int v,nxt;
} e[MAXN*2];
int head[MAXN],cnt=0;
void ad(int u,int v){
	e[++cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

bool vis[MAXN];
int d[MAXN],bel[MAXN],cntd[MAXN];
void dfs(int u){
	vis[u]=true;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(vis[v]) continue;
		bel[v]=bel[u];
		dfs(v);
	}
}

int c[MAXN],dep[MAXN],fa[20][MAXN],lg[MAXN];
void dfs2(int u,int fath){
	vis[u]=true;
	fa[0][u]=fath;
	dep[u]=dep[fath]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(vis[v]) continue;
		dfs2(v,u);
	}
}
void lca_init(){
	lg[1]=0;
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	// printf("lg:\n");
	// for(int i=1;i<=n;i++)
	// 	printf("lg[%d]=%d ",i,lg[i]);
	// printf("\n");
	for(int j=1;j<=lg[n];j++)
		for(int i=1;i<=n;i++)
			fa[j][i]=fa[j-1][fa[j-1][i]];
	// printf("fa[1][26]=%d\n",fa[1][26]);
}
int getlca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int j=lg[dep[x]];j>=0;j--)
		if(dep[fa[j][x]]>=dep[y])
			x=fa[j][x];
	if(x==y) return x;
	for(int j=lg[dep[x]];j>=0;j--)
		if(fa[x][j]!=fa[y][j]){
			x=fa[j][x];
			y=fa[j][y];
		}
	return fa[0][x];
}
bool flag=true;
int cntc=0;
void dfs3(int u){
	vis[u]=true;
	// printf("u=%d head[u]=%d\n",u,head[u]);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		// printf("v=%d fa[0][u]=%d vis[v]=%d\n",v,fa[0][u],vis[v]);
		if(v==fa[0][u]) continue;
		if(vis[v]){
			if(dep[v]>dep[u]) continue;
			cntc++;
			// if(u==9 && v==1)
			// 	printf("xxx\n");
			// if(u==9 && v==1){
			// 	printf("dep[9]=%d lg[dep[9]]=%d\n",dep[u],lg[dep[u]]);
			// 	for(int j=0;j<=lg[dep[9]];j++)
			// 		printf("fa[%d][%d]=%d ",j,u,fa[j][u]);
			// 	printf("\n");
			// }
			int lca=getlca(u,v);
			if(dep[u]+dep[v]-2*dep[lca]+1>4){
				flag=false;
				return;
			}
			c[u]++;
			c[v]++;
			c[lca]--;
			if(fa[0][lca]) c[fa[0][lca]]--;
			// if(u==2 && v==1){
			// 	printf("u=%d v=%d lca=%d fa[0][lca]=%d\n",u,v,lca,fa[0][lca]);
			// 	printf("c[u]=%d c[v]=%d c[lca]=%d\n",c[u],c[v],c[lca]);
			// }
		}else{
			dfs3(v);
			if(!flag) return;
			c[u]+=c[v];
		}
	}
}

vector<int> p;
int cmp(int a,int b){ return d[a]>d[b]; }
void dfs4(int u){
	p.push_back(u);
	vis[u]=true;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(vis[v]) continue;
		dfs4(v);
	}
}

int ans[MAXN],cntans=0;
void init(){
	cnt=cntc=cntans=0;
	flag=true;
	for(int i=1;i<=n;i++) head[i]=bel[i]=vis[i]=d[i]=cntd[i]=c[i]=0;
}
void lca_clear(){
	for(int i=1;i<=n;i++)
		for(int j=0;j<=lg[dep[i]];j++)
			fa[j][i]=0;
}

void solve(){
	n=read(),m=read();
	init();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		ad(u,v);
		ad(v,u);
		d[u]++,d[v]++;
	}
	int k=0;
	for(int i=1;i<=n;i++){
		if(!bel[i]) {
			bel[i]=++k;
			dfs(i);
		}
		if(d[i]>1){
			if(cntd[bel[i]]==0) 
				cntd[bel[i]]=1;
			else cntd[bel[i]]=-1;
		}
	}
	int sumk=0;
	for(int i=1;i<=k;i++)
		if(cntd[i]>=0) sumk++;
	if(sumk==k){
		for(int i=1;i<=n;i++){
			write(i);
			putchar(' ');
		}
		puts("");
		return;
	}
	// printf("sumk=%d\n",sumk);
	if(sumk<k-1){
		write(-1);
		puts("");
		return;
	}
	int id=0;
	for(int i=1;i<=k;i++)
		if(cntd[i]==-1) id=i;
	for(int i=1;i<=n;i++) vis[i]=0;
	int rt=0,siz=0;
	for(int i=1;i<=n;i++) if(bel[i]==id) siz++;
	for(int i=1;i<=n;i++)
		if(bel[i]==id){
			rt=i;
			break;
		}
	// printf("bel:\n");
	// for(int i=1;i<=n;i++)
	// 	printf("bel[%d]=%d ",i,bel[i]);
	// printf("\n");
	// printf("id=%d rt=%d siz=%d\n",id,rt,siz);
	dfs2(rt,0);
	// printf("dfs2 ok\n");
	lca_init();
	// printf("lca ok\n");
	for(int i=1;i<=n;i++) vis[i]=0;
	// for(int i=1;i<=n;i++)
	// 	printf("c[%d]=%d ",i,c[i]);
	dfs3(rt);
	// printf("dfs3 ok\n");
	if(!flag){
		lca_clear();
		write(-1);
		puts("");
		return;
	}
	if(cntc){
		// printf("cntc=%d\n",cntc);
		// for(int i=1;i<=n;i++)
		// 	if(bel[i]==id) printf("c[%d]=%d ",i,c[i]);
		// printf("\n");
		for(int u=1;u<=n;u++){
			if(bel[u]==id && c[u]==cntc){
				for(int i=head[u];i;i=e[i].nxt){
					int v=e[i].v;
					d[v]--;
					vis[i]=false;
				}
				for(int i=1;i<=n;i++) vis[i]=false;
				// for(int i=1;i<=n;i++)
				// 	printf("d[%d]=%d ",i,d[i]);
				// printf("\n");
				bool flag1=true;
				vis[u]=true;
				for(int i=head[u];i;i=e[i].nxt){
					int v=e[i].v;
					if(!vis[v]){
						p.clear();
						dfs4(v);
						sort(p.begin(),p.end(),cmp);
						// printf("u=%d p.size=%d\n",u,p.size());
						if(p.size()>2 && d[p[1]]>1){
							flag1=false;
							break;
						}
					}
				}
				if(flag1)
					// ans.push_back(u);
					ans[++cntans]=u;
				for(int i=head[u];i;i=e[i].nxt){
					int v=e[i].v;
					d[v]++;
				}
			}
		}
		if(cntans==0){
			write(-1);
			puts("");
		}
		else {
			// sort(ans.begin(),ans.end());
			sort(ans+1,ans+1+cntans);
			for(int i=1;i<=cntans;i++){
				write(ans[i]);
				putchar(' ');
			}
			puts("");
		}
		lca_clear();
	}else{
		// printf("-1\n");
		// lca_clear();
		// return;
		int cnt1=0;
		for(int i=1;i<=n;i++)
			if(bel[i]==id && d[i]==1) cnt1++;
		for(int u=1;u<=n;u++){
			if(bel[u]==id){
				int cnt2=cnt1;
				if(d[u]==1) cnt2--;
				int nk=0;
				for(int i=head[u];i;i=e[i].nxt){
					nk++;
					int v=e[i].v;
					if(d[v]==1) cnt2--;
					d[v]--;
					if(d[v]==1){
						cnt2++;
						for(int j=head[v];j;j=e[j].nxt)
							if(e[j].v!=u && d[e[j].v]==1) cnt2--;
					}
				}
				// for(int i=1;i<=n;i++)
				// 	printf("d[%d]=%d ",i,d[i]);
				// printf("nk=%d cnt1=%d\n",nk,cnt2);
				for(int i=head[u];i;i=e[i].nxt)
					d[e[i].v]++;
				if(cnt2==siz-nk-1){
					// printf("siz-nk-1=%d\n",siz-nk-1);
					// ans.push_back(u);
					ans[++cntans]=u;
				}
			}
		}
		if(cntans==0){
			write(-1);
			puts("");
		}
		else {
			// sort(ans.begin(),ans.end());
			sort(ans+1,ans+1+cntans);
			for(int i=1;i<=cntans;i++){
				write(ans[i]);
				// printf("%d",ans[i]);
				putchar(' ');
			}
			puts("");
		}
		lca_clear();
	}
	return;
}

int main()
{
	// lg[1]=0;
	// for(int i=2;i<=10000;i++) lg[i]=lg[i>>1]+1;
	// printf("%d\n",lg[10000]);
	// freopen("1002.in","r",stdin);
	// freopen("me.out","w",stdout);
	int t;
	t=read();
	while(t--)
		solve();
	return 0;
}

/*
1
3 3
1 2
2 3
1 3
*/
/*
1
4 6
1 2
1 3
1 4
2 3
2 4
3 4
*/
/*
1
5 4
1 2
2 3
3 4
4 5
*/
/*
1
6 6
1 2
2 3
3 4
4 1
4 2
5 6
*/
/*
1
9 7
4 7
6 5
8 5
5 7
7 9
1 2
2 3
*/
