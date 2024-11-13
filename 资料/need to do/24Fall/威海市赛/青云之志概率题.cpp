// 先自己藏着吧
// 雀魂青云之志，换牌操作，达成国士无双十三面听牌，期望换牌次数
// 细节，有36张牌可以替换，手牌13张
#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	// 1 9 1 9 1 9 0 0 0 0 0 0 0 
	std::vector<int> a(14); // 共36张 // 13 为非幺九牌
	std::string s;
	std::cin >> s; // 手牌
	const int N = 1 << 13;
	std::vector<std::vector<int> > dp(N, std::vector<int>(N));
	for (int i = N - 1; i >= 0; i --) {
		// 0 位置 ? 1 << x, 算这些概率，
	}
	std::cout << dp[have] << '\n';
}
int main() {
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}