#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<array>
#define re register
using i64 = long long;
// #define int i64
const long long inf = 1e18 + 7;
int read(){
	char c=getchar();
	int a=0;
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9') {
		a=(a<<1)+(a<<3)+(c^48);
		c=getchar();
	}
	return a;
}
void solve() {
	int n, k;
	// std::cin >> n >> k;
	n=read(),k=read();
	std::vector<int > a(5);
	std::vector<long long> dp(k + 1, inf);
	dp[0] = 0;
	for (re int i = 1; i <= n; i ++) {
		for(re int op = 1; op < 5; op ++)
			a[op] = read();
		for (re int j = std::min(4*i, k); j >= 0; j --) {
			for (re int op = 1; op < 5; op ++) {
				if (j - op >= 0) {
					dp[j] = std::min(dp[j], dp[j - op] + a[op]);
				}
			}
		}
	}
	std::cout << dp[k] << '\n';
}
signed main() { 
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}