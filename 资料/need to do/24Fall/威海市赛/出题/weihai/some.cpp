#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int num = 26;
	for (int i = 3500; i <= 5000; i += 50) {
		std::cout << "gen " << i << " > " << num ++ << '\n';
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	while (t --) {
		solve();
	}
	return 0;
}