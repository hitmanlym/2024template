#include<bits/stdc++.h>
using i64 = long long;

const int inf = 1e9;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 2);
	int sum = 0, min = -inf;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		sum += a[i];
		min = std::max(min, a[i]);
	}
	for (int i = 1; i <= n; i ++) {
		a[i] += a[i - 1];
	}
	a[n + 1] = inf;
	int B = std::max((int)std::sqrt(sum), min);

	std::vector<int> ans(B + 1, -1);
	for (int i = min; i <= B; i ++) {
		int num = 0, now = 0;
		for (int j = 1; j <= n + 1; j ++) {
			if (a[j] - now > i) {
				now = a[j - 1];
				num ++;
			}
		}
		ans[i] = num;
	}
	std::vector<int> b(ans[B] + 1);
	b[ans[B]] = B;
	auto check = [&](int x, int p) -> bool { // t p's
		int o = 0;
		for (int i = 1; i <= p; i ++) {
			int l = o, r = n + 1, res = -1;
			while (l <= r) {
				int mid = l + r >> 1;
				if (a[mid] - a[o] > x) {
					r = mid - 1;
				} else {
					// std::cout << mid << ' ' << l << ' ' << a[mid] - a[l] << '\n';
					res = mid;
					l = mid + 1;
				}
			}
			// std::cout << i << ' ' << res << '\n';
			o = res;
		}
		// std::cout << "!!! " << x << ' ' << p << ' ' << o << '\n';
		return o >= n;
	};
	for (int j = ans[B] - 1; j >= 1; j --) { // 这种批次的最小 t
		int l = b[j + 1], r = sum, res = 0;
		// std::cout << "??? " << j << '\n';
		while (l <= r) {
			int mid = l + r >> 1;
			if (check(mid, j)) {
				res = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		b[j] = res;
	}
	// std::cout << B << '\n';
	// for (int i = 1; i <= ans[B]; i ++) {
	// 	std::cout << b[i] << ' ';
	// }
	// std::cout << '\n';

	int q;
	std::cin >> q;
	while (q --) {
		int t;
		std::cin >> t;
		if (t <= B) {
			if (ans[t] != -1) {
				std::cout << ans[t] << '\n';
			} else {
				std::cout << "Impossible\n";
			}
			continue;
		}
		for (int i = 1; i <= ans[B]; i ++) {
			if (t >= b[i]) {
				std::cout << i << '\n';
				break;
			}
		}
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}