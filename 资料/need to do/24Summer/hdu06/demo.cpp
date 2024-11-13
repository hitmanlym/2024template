#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;

void solve() {
	int n,m;
	std::cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		std::cin>>u>>v;
	}
    // if(system("fc me.out 1002.out >nul")!=0)
    //     printf("WA\n");
    return;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    freopen("1002.in","r",stdin);
    freopen("data.out","w",stdout);
    int t = 1;
    std::cin >> t;
    for (int i = 1; i <= t; i ++) {
    	if(i==25006){
    		int n,m;
    		std::cin>>n>>m;
    		std::cout<<n<<' '<<m<<'\n';
    		for(int j=1;j<=m;j++){
    			int u,v;
    			std::cin>>u>>v;
    			std::cout<<u<<' '<<v<<'\n';
    		}return 0;
    	}
    	solve();
    	// else 
    }
    return 0;
}