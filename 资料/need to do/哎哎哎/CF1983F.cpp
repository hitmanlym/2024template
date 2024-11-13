#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}

	std::vector<std::array<int, 2> > t(n * 100);
	std::vector<int> b(n * 100);
	int tot = 1;
	auto insert = [&](int x, int pos) -> void {
		int now = 1;
		for (int i = 29; i >= 0; i --) {
			int p = (x >> i) & 1;
			if (! t[now][p]) t[now][p] = ++ tot;
			now = t[now][p];
			b[now] = std::max(b[now], pos);
		}
	};
	auto query = [&](int x, int y) -> int {
		int now = 1, pos = 0;
		for (int i = 29; i >= 0; i --) {
			// {x ^ (what) <= y } -> number
			int u = (x >> i) & 1, v = (y >> i) & 1;
			if (v) {
				pos = std::max(pos, b[t[now][u]]); // less sqe
				now = t[now][u ^ 1];
			} else {
				now = t[now][u];
			}
		}
		pos = std::max(pos, b[now]);
		//std::cout << "!!! " << pos << '\n';
		return pos;
	};

	auto check = [&](int x) -> int {
		int res = 0, pos = 0;
		for (int i = 1; i <= n; i ++) {
			pos = std::max(pos, query(a[i], x));
			insert(a[i], i);
			//std::cout << pos << '\n';
			res += pos;
		}
		//std::cout << res << ' ' << k << '\n';
		for (int i = 1; i <= tot; i ++) {
			t[i] = {0, 0};
			b[i] = 0;
		}
		tot = 1;
		return res;
	};

	int l = 0, r = (1 << 30) - 1, ans;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(mid) >= k) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	std::cout << ans << '\n';
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