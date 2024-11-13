#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::vector<std::array<int, 2> > a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i][0] >> a[i][1];
	} 
	// auto work = [&](auto x, auto y) -> int {
	// 	std::vector<int> a(4);
	// 	a[0] = x[0], a[1] = x[1];
	// 	a[2] = y[0], a[3] = y[1];
	// 	int num = 0;
	// 	for (int i = 0; i < 4; i ++) {
	// 		for (int j = i + 1; j < 4; j ++) {
	// 			num += (a[j] < a[i]);
	// 		}
	// 	}
	// 	return num;
	// };
	std::sort(a.begin() + 1, a.end(), [&](auto x, auto y) {
		return x[0] + x[1] < y[0] + y[1];
	});
	for (int i = 1; i <= n; i ++) {
		std::cout << a[i][0] << ' ' << a[i][1] << ' ';
	}
	std::cout << '\n';
} 
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}