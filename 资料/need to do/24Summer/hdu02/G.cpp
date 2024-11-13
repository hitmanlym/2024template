#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
#include<cstring>
using i64 = long long;

char s[210];
void solve() {
	memset(s,0,sizeof(s));
	scanf("%s",s+1);
	int n=strlen(s+1);
	int las=1;
	bool flag=false;
	int t=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='=') flag=true;
		if(s[i]=='/'){
			t++;
			if(s[i-1]==':' && s[i+1]=='/'){
				for(int j=las;j<i-1;j++)
					putchar(s[j]);
				puts("");
				las=i+2;
				i++;
			}else {
				if(t==2 || flag){
					for(int j=las;j<i;j++)
						putchar(s[j]);
					puts("");
				}
				las=i+1;
				flag=false;
			}
		}
	}
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}