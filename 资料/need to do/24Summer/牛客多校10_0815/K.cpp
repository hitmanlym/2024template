#include<cstdio>
#include<algorithm>
using namespace std;
int t,n,a[100005],p,ans,r,l;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n),ans=p=r=l=0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		if(a[1]>=0) p=0;
		else if(a[n]<=0) p=n;
		else for(int i=1;i<=n;i++){
			if(!a[i]) p=i;
			else if(a[i]<0&&a[i+1]>0) p=i;
		}
		r=l=p;
		for(int i=p+1;i<=n;i++) if(a[i]<=n-i) r=i,ans=max(ans,i-p);
		for(int i=p;i>0;i--) if(-a[i]<=i-1) l=i,ans=max(ans,p-i+1);
		for(int i=p+1;i<=n;i++){
			if(a[i]>n-i) break;
			while(a[i]-a[l]>l-1&&l<=p) l++;
			ans=max(ans,i-l+1);
		}
		for(int i=p;i>0;i--){
			if(-a[i]>i-1) break;
			while(a[r]-a[i]>n-r&&r>p) r--;
			ans=max(ans,r-i+1);
		}
		printf("%d\n",ans);
	}
}