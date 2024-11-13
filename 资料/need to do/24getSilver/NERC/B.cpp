#include<cstdio>
using namespace std;

int main()
{
	int n;
	scanf("%d",&n);
	int now=710;
	printf("%d\n",0);
	n--;
	for(int i=1;i<=n/2;i++,now+=710)
		printf("%d\n",now);
	now=-710;
	for(int i=1;i<=n-n/2;i++,now-=710)
		printf("%d\n",now);
	return 0;
}
