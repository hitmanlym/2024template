#include<cstdio>
using namespace std;
#define MAXN 200010

int n,q;
int a[MAXN];
int gcd(int a,int b){ return b==0?a:gcd(b,a%b); }

int pri[MAXN],cnt=0;
bool vis[MAXN];
int d[MAXN],num[MAXN];
void getpri(int n){
	vis[1]=true;
	d[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			pri[++cnt]=i;
			d[i]=2;
			num[i]=1;
		}
		for(int j=1;j<=cnt && pri[j]<=n/i;j++){
			vis[i*pri[j]]=true;
			if(i%pri[j]==0){
				num[i*pri[j]]=num[i]+1;
				d[i*pri[j]]=d[i]/num[i*pri[j]]*(num[i*pri[j]]+1);
				break;
			}
			num[i*pri[j]]=1;
			d[i*pri[j]]=d[i]*2;
		}
	}
}

struct node{
	int ls,rs;
	int g,rv,rtag,lv,ltag;
} tre[MAXN*10];
int cntp=0;

void pushup(int rt){
	int ls=tre[rt].ls,rs=tre[rt].rs;
	tre[rt].g=gcd(tre[ls].g,tre[rs].g);
}
void pushdownr(int rt){
	int ls=tre[rt].ls,rs=tre[rt].rs;
	if(tre[rt].rtag){
		tre[ls].rv=tre[rt].rtag;
		tre[ls].rtag=tre[rt].rtag;
		tre[rs].rv=tre[rt].rtag;
		tre[rs].rtag=tre[rt].rtag;
		tre[rt].rtag=0;
	}
}
void pushdownl(int rt){
	int ls=tre[rt].ls,rs=tre[rt].rs;
	if(tre[rt].ltag){
		tre[ls].lv=tre[rt].ltag;
		tre[ls].ltag=tre[rt].ltag;
		tre[rs].lv=tre[rt].ltag;
		tre[rs].ltag=tre[rt].ltag;
		tre[rt].ltag=0;
	}
}
int newnode(){
	int k=++cntp;
	tre[k].ls=tre[k].rs=tre[k].g=tre[k].rv=tre[k].rtag=tre[k].lv=tre[k].ltag=0;
	return k;
}
void build(int &rt,int l,int r){
	if(!rt) rt=newnode();
	if(l==r) return;
	int mid=(l+r)>>1;
	build(tre[rt].ls,l,mid);
	build(tre[rt].rs,mid+1,r);
}
void fix(int rt,int l,int r,int x,int g){
	if(l==r){
		tre[rt].g=g;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) fix(tre[rt].ls,l,mid,x,g);
	else fix(tre[rt].rs,mid+1,r,x,g);
	pushup(rt);
}
void changel(int rt,int l,int r,int L,int R,int v){
	if(L<=l && r<=R){
		tre[rt].lv=tre[rt].ltag=v;
		return;
	}
	pushdownl(rt);
	int mid=(l+r)>>1;
	if(L<=mid) changel(tre[rt].ls,l,mid,L,R,v);
	if(mid<R) changel(tre[rt].rs,mid+1,r,L,R,v);
}
void changer(int rt,int l,int r,int L,int R,int v){
	if(L<=l && r<=R){
		tre[rt].rv=tre[rt].rtag=v;
		return;
	}
	pushdownr(rt);
	int mid=(l+r)>>1;
	if(L<=mid) changer(tre[rt].ls,l,mid,L,R,v);
	if(mid<R) changer(tre[rt].rs,mid+1,r,L,R,v);
}
int query(int rt,int l,int r,int L,int R){
	if(L<=l && r<=R) return tre[rt].g;
	int mid=(l+r)>>1;
	int ans=0;
	if(L<=mid) ans=gcd(ans,query(tre[rt].ls,l,mid,L,R));
	if(mid<R) ans=gcd(ans,query(tre[rt].rs,mid+1,r,L,R));
	return ans;
}
int queryl(int rt,int l,int r,int x){
	if(l==r) return tre[rt].lv;
	pushdownl(rt);
	int mid=(l+r)>>1;
	if(x<=mid) return queryl(tre[rt].ls,l,mid,x);
	else return queryl(tre[rt].rs,mid+1,r,x);
}
int queryr(int rt,int l,int r,int x){
	if(l==r) return tre[rt].rv;
	pushdownr(rt);
	int mid=(l+r)>>1;
	if(x<=mid) return queryr(tre[rt].ls,l,mid,x);
	else return queryr(tre[rt].rs,mid+1,r,x);
}

void solve()
{
	int root=0;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(root,1,n);
	int las=1;
	for(int i=2;i<=n;i++){
		if(a[i-1]>a[i]){
			// printf("%d %d\n",i-1,i-las);
			fix(1,1,n,i-1,i-las);
			changel(1,1,n,las,i-1,las);
			changer(1,1,n,las,i-1,i-1);
			las=i;
		}
	}
	fix(1,1,n,n,n-las+1);
	changel(1,1,n,las,n,las);
	changer(1,1,n,las,n,n);
	// printf("%d %d\n",n,n-las+1);
	printf("%d\n",d[query(1,1,n,1,n-1)]);

	for(int i=1;i<=q;i++){
		int p,v;
		scanf("%d%d",&p,&v);
		int x=a[p];
		a[p]=v;
		int l=p,r=p;
		// if(a[p-1]<=x && a[p-1]<=v && x<=a[p+1] && v<=a[p+1]) continue;
		// if(a[p-1]>x && a[p-1]>v && x>a[p+1] && v>a[p+1]) continue;
		if(((a[p-1]<=x && a[p-1]<=v) || (a[p-1]>x && a[p-1]>v) || p==1) &&
			((x<=a[p+1] && v<=a[p+1]) || (x>a[p+1] && v>a[p+1]) || p==n)){
			printf("%d\n",d[query(1,1,n,1,n-1)]);
			continue;
		}
		if(p>1){
			if(a[p-1]>x && a[p-1]<=v) fix(1,1,n,p-1,0);
			if(a[p-1]<=v) l=queryl(1,1,n,p-1);
			if(a[p-1]<=x && a[p-1]>v){
				l=queryl(1,1,n,p);
				fix(1,1,n,p-1,p-l);
				changel(1,1,n,l,p-1,l);
				changer(1,1,n,l,p-1,p-1);
				l=p;
			}
		}

		if(p<n){
			if(v<=a[p+1]) r=queryr(1,1,n,p+1);
			if(x>a[p+1] && v<=a[p+1]) fix(1,1,n,p,0);
			if(x<=a[p+1] && v>a[p+1]){
				r=queryr(1,1,n,p);
				fix(1,1,n,r,r-p);
				changel(1,1,n,p+1,r,p+1);
				changer(1,1,n,p+1,r,r);
				r=p;
			}
		}
			
		fix(1,1,n,r,r-l+1);
		changel(1,1,n,l,r,l);
		changer(1,1,n,l,r,r);
		printf("%d\n",d[query(1,1,n,1,n-1)]);

	}

	while(cntp){
		int k=cntp;
		tre[k].ls=tre[k].rs=tre[k].g=tre[k].rv=tre[k].rtag=tre[k].lv=tre[k].ltag=0;
		cntp--;
	}
}

int main()
{
	getpri(200000);
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}