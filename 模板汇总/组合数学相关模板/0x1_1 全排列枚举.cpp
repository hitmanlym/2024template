#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; i ++) {
		a[i] = i + 1;
	}
	do {
		for (auto it : a) {
			std::cout << it << ' ';
		}
		std::cout << '\n';
	} while (std::next_permutation(a.begin(), a.end()));
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}