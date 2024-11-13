#include<cstdio>
#include<algorithm>
using namespace std;
bool f;
int t,l,d,n,a[100005],maxn,minn,cnt;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d",&n,&l,&d,&a[1]);
		maxn=minn=a[1],cnt=f=0;
		if (a[1] < l) cnt ++;
		else f=1;
		for(int i=2;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i]<l) cnt++;
			if(!f||a[i]<l) minn=min(minn, a[i]);
			if(!f||a[i]<l) maxn = std::max(maxn, a[i]);
		}
		if(cnt > 2 && maxn - minn > d) printf("Yes\n");
		else printf("No\n");
	}
}