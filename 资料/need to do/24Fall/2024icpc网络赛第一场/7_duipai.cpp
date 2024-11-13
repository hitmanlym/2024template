#include<bits/stdc++.h>
using namespace std;

int main()
{
	system("g++ 7_data.cpp -o 7_data");
	system("g++ 7.cpp -o 7");
	system("g++ 7_fru.cpp -o 7_fru");
	for(int cas=1;cas<=10000;cas++){
		system("7_data >tt.in");
		system("7 <tt.in >std.out");
		system("7_fru <tt.in >fru.out");
		if(system("fc fru.out std.out >nul")!=0){
			printf("WA\n");
			return 0;
		}
		printf("AC\n");
	}
	return 0;
}