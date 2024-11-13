#include<bits/stdc++.h>
using i64 = long long;
#define int i64
int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, x, y);
    int z = x;
    x = y;
    y = z - (a / b) * y;
    return d;
}
void solve() { // Why???!!!
	int x1, y1, x2, y2;
	std::cin >> x1 >> y1 >> x2 >> y2;
	if (x1 == x2) {
		std::cout << x1 + 1 << ' ' << y1 << '\n';
		return ;
	} 
	if (y1 == y2) {
		std::cout << x1 << ' ' << y1 + 1 << '\n';
		return ;
	}
	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	int x, y;
	if (y2 > y1) {
		int d = exgcd(y2 - y1, x2 - x1, x, y);
		std::cout << x1 + x << ' ' << y1 - y << '\n';
	} else {
		int d = exgcd(y1 - y2, x2 - x1, x, y);
		std::cout << x1 + x << ' ' << y1 + y << '\n';
	}
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