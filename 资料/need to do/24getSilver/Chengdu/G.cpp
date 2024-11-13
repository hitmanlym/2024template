#include<cstdio>
#include<map>
using namespace std;

map <int,bool> mp;
int n;
int a[100010];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		mp[a[i]]=1;
	}
	mp[0]=1;
	for(int i=1;i<n;i++){
		int x=a[i],y=a[i+1];
		// if(x==0 || y==0) continue;
		int z=a[i]^a[i+1];
		mp[z]=1;
		// printf("%d\n"s,z);
		mp[x&z]=1;
		mp[x|z]=1;
		mp[y&z]=1;
		mp[y|z]=1;
		mp[x^(x&z)]=1;
		mp[z^(x&z)]=1;
		mp[y^(y&z)]=1;
		mp[z^(y&z)]=1;
		mp[x&y]=1;
		mp[x|y]=1;
		mp[x^(x&y)]=1;
		mp[y^(x&y)]=1;
		// printf("%d %d %d %d %d %d %d %d\n",x^(x&z),z^(x&z),y^(y&z),z^(y&z),x&y,x|y,x^(x&y),y^(x&y));
	}
	printf("%d\n",(int)mp.size());
	return 0;
}