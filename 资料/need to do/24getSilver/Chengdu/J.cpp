#include<cstdio>
#include<algorithm>
using namespace std;
#define ll long long
#define MAXN 100010

int read(){
	char c=getchar();
	int ret=0;
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		ret=(ret<<1)+(ret<<3)+(c^48);
		c=getchar();
	}
	return ret;
}
void write(ll x){
	if(!x) return;
	write(x/10);
	putchar(x%10+'0');
}

int n,m,q;
struct node{
	int id;
	ll num;
	friend bool operator < (node a,node b){
		if(a.num!=b.num) return a.num>b.num;
		return a.id<b.id;
	}
} p[MAXN];
int sta[MAXN],top=0;
bool vis[MAXN];

void solve()
{
	// scanf("%d%d%d",&n,&m,&q);
	n=read(),m=read(),q=read();
	for(int i=1;i<=m;i++)
		p[i].id=i,p[i].num=0;
	int now=0,c=m;
	while(q--){
		int op,id,x;
		op=read();
		if(op>1) id=read();
		x=read();
		if(op==1){
			while(top)
				vis[sta[top--]]=false;
			now=x;
			c=m;
		}else {
			if(vis[id] || now!=x) continue;
			vis[id]=true;
			sta[++top]=id;
			if(op==2){
				p[id].num+=c;
				c--;
			}
		}
	}
	sort(p+1,p+1+m);
	for(int i=1;i<=m;i++){
		write(p[i].id);
		putchar(' ');
		if(!p[i].num) putchar('0');
		else write(p[i].num);
		puts("");
	}
}

int main()
{
	int t;
	// scanf("%d",&t);
	t=read();
	while(t--)
		solve();
	return 0;
}