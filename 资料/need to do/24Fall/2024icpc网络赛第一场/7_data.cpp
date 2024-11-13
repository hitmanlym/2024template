#include<bits/stdc++.h>
using namespace std;

int main()
{
	srand(time(NULL));
	int n=100;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%10+1);
	return 0;
}