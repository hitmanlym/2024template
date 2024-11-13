#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
int t,n,m,a[500005],tree[500005],ans;
map<int,int> pos;
int lowbit(int x){return x&-x;}
void add(int x,int v){
	while(x<=n) tree[x]+=v,x+=lowbit(x);
	return;
}
int sum(int x){
	int s=0;
	while(x) s+=tree[x],x^=lowbit(x);
	return s;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m),ans=-1;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),tree[i]=0;
		pos.clear();
		for(int i=1;i<=n;i++){
			ans=max(ans,sum(i-1)-sum(pos[a[i]])-a[i]);
			if(pos[a[i]]) add(pos[a[i]],-1);
			add(i,1),pos[a[i]]=i;
		}
		// map<int,int>::iterator i;
		// for(int *i=pos) ans=max(ans,sum(n)-sum(pos[i])-i);
		for(map<int,int>::iterator i=pos.begin();i!=pos.end();i++)
			ans=max(ans,sum(n)-sum(i->second)-i->first);
		sort(a+1,a+1+n);
		int x=0;
		for(int i=1;i<=n;i++){
			if(a[i]==x) continue;
			if(a[i]==x+1) x++;
			else break;
		}
		x++;
		ans=max(ans,sum(n)-x);
		printf("%d\n",ans);
	}
	return 0;
}