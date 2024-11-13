#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 2010

int n;
int a[MAXN];
int b[MAXN][MAXN],c[MAXN][MAXN];
struct Tree{
	int ls,rs;
	int sum;
} tre[MAXN*40];
int cnt=0,root=0;
int newnode(){
	++cnt;
	tre[cnt].sum=tre[cnt].ls=tre[cnt].rs=0;
	return cnt;
}
void pushup(int rt){
	int ls=tre[rt].ls,rs=tre[rt].rs;
	tre[rt].sum=tre[ls].sum+tre[rs].sum;
}
void insert(int &rt,int l,int r,int x){
	if(!rt) rt=newnode();
	if(l==r){
		tre[rt].sum++;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) insert(tre[rt].ls,l,mid,x);
	else insert(tre[rt].rs,mid+1,r,x);
	pushup(rt);
}
int query(int rt,int l,int r,int x){
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(!tre[rt].rs || tre[tre[rt].ls].sum>=x)
		return query(tre[rt].ls,l,mid,x);
	else return query(tre[rt].rs,mid+1,r,x); 
}

bool check(int x){
	// printf("mid=%d\n",x);
	for(int i=0;i<=n+1;i++)
		for(int j=0;j<=n+1;j++)
			c[i][j]=0;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			if(b[i][j]>=x) c[i][j]=1;
			else c[i][j]=0;
	// printf("c:\n");
	// for(int i=1;i<=n;i++){
	// 	for(int j=1;j<=n;j++)
	// 		printf("%d ",c[i][j]);
	// 	printf("\n");
	// }
	// printf("\n");
	for(int i=n;i>=1;i--)
		for(int j=i;j<=n;j++)
			c[i][j]+=c[i+1][j]+c[i][j-1]-c[i+1][j-1];
	// printf("c:\n");
	// for(int i=1;i<=n;i++){
	// 	for(int j=1;j<=n;j++)
	// 		printf("%d ",c[i][j]);
	// 	printf("\n");
	// }
	// printf("\n");
	int num=0;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++){
			int len=j-i+1;
			if(c[i][j]>len*(len+1)/2-c[i][j])
				num++;
		}
	return num>n*(n+1)/2-num;
}

int main()
{
	scanf("%d",&n);
	int maxa=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		maxa=max(maxa,a[i]);
	}
	for(int l=1;l<=n;l++){
		cnt=root=0;
		for(int r=l;r<=n;r++){
			insert(root,1,maxa,a[r]);
			b[l][r]=query(root,1,maxa,(r-l+2)/2);
		}
	}
	// printf("b:\n");
	// for(int i=1;i<=n;i++){
	// 	for(int j=1;j<=n;j++)
	// 		printf("%d ",b[i][j]);
	// 	printf("\n");
	// }
	sort(a+1,a+1+n);
	int l=1,r=n,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(a[mid])){
			ans=mid;
			l=mid+1;
		}else r=mid-1;
	}
	printf("%d\n",a[ans]);
	return 0;
}