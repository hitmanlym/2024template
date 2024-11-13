#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	i64 a, b;
	std::cin >> a >> b;
	auto get = [&](i64 x) -> i64 {
		i64 res = 0;
		while (x) {
			res = res * 10 + x % 10;
			x /= 10;
		}
		res *= -1;
		return res;
	};
	if (a < 0) {
		a = get(-a);
	}
	if (b < 0) {
		b = get(-b);
	}
	std::cout << a + b << '\n';
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