#include<cstdio>
#include<algorithm>
using namespace std;
int a[1100005],p[1100005],n,k,ans[1100005],t[1100005];
void ssort(int l,int r){
	if(l==r) return;
	int mid=l+r>>1,x=1;
	while((1<<(x+1))<=r-l+1) x++;
	ssort(l,mid),ssort(mid+1,r);
	for(int i=l;i<=r;i++) t[i]=p[i];
	int i=l,j=mid+1,now=l;
	while(i<=mid&&j<=r){
		if(t[i]<t[j]) p[now++]=t[i++];
		else p[now++]=t[j++];
	}
	while(i<=mid) p[now++]=t[i++];
	while(j<=r) p[now++]=t[j++];
	for(i=r;i>=max(l,r-k);i--) ans[p[i]]=x;
	return;
}
int main(){
	scanf("%d%d",&n,&k),n=1<<n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),p[i]=a[i];
	ssort(1,n);
	for(int i=1;i<=n;i++){
		int x=0;
		while((1<<(x+1))<=a[i]) x++;
		if(ans[a[i]]<=x) printf("%d ",ans[a[i]]);
		else printf("%d ",x);
	}
	return 0;
}