#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; i ++) {
		std::cin >> b[i];
	}
	std::sort(a.begin() + 1, a.end(), [&](auto x, auto y) {
		return x > y;
	});
	std::sort(b.begin() + 1, b.end(), [&](auto x, auto y) {
		return x > y;
	});
	int max = 0, min = 0;

	int l = 1, r = n, x = 1, y = n;
	while (l <= r) {
		if (a[l] > b[x]) {
			max ++;
			l ++;
			x ++;
			continue;
		}
		if (a[l] < b[x]) {
			max --;
			x ++;
			r --;
			continue;
		}
		if (a[l] == b[x]) {
			if (a[r] > b[y]) {
				max ++;
				r --;
				y --;
			} else {
				if (a[r] < b[x]) max --;
				r --;
				x ++;
			}
			continue;
		}
	}

	l = 1, r = n, x = 1, y = n;
	while (l <= r) {
		if (b[l] > a[x]) {
			min ++;
			l ++;
			x ++;
			continue;
		}
		if (b[l] < a[x]) {
			min --;
			x ++;
			r --;
			continue;
		}
		if (b[l] == a[x]) {
			if (b[r] > a[y]) {
				min ++;
				r --;
				y --;
			} else {
				if (b[r] < a[x]) min --;
				r --;
				x ++;
			}
			continue;
		}
	}
	max += n;
	min = 2 * n - (min + n);
	std::cout << max << ' ' << min << '\n';
}	
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}