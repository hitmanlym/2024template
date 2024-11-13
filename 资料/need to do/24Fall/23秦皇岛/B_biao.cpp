#include<cstdio>
#include<bits/stdc++.h>
using namespace std;

std::string gen_string(int a, int b) {
	std::string res;
	int ia = 0, ib = 0;
	while (ia + ib < a + b) {
		if (ia * b <= ib * a) {
			res += '0';
			ia++;
		} else {
			res += '1';
			ib++;
		}
	}
	return res;
}

int main()
{
	// int n=6;
	// for(int m=7;m<=40;m++){
	// 	printf("%d %d:\n",m,n);
	// 	int y=(m-1)%n;
	// 	// printf("%d %d\n",(n-y)%(y+1),y%(n-y+1));
	// 	std::cout << gen_string(m,n) << '\n';
	// }
	// int n,m;
	// while(scanf("%d%d",&n,&m)!=EOF){
	// 	std::cout << gen_string(n,m) << '\n';
	// }
	printf("%d\n",rand()%2);
}