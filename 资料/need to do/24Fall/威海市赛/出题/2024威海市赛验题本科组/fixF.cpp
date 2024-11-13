#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n, q;
	std::cin >> n >> q;
	std::vector<int> v(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> v[i];
	}
	// 我知道了，这个还和q有关，呃呃呃
	std::vector<std::array<int, 2> > t((n + q + 1) * 20);
	std::vector<int> num((n + q + 1) * 20);
	int cnt = 0, ans = 0;
	auto insert = [&](int x, int val) -> void {
		int u = 0;
		for (int i = 0; i <= 18; i ++) {
			int b = x & 1;
			if (! t[u][b]) {
				t[u][b] = ++ cnt;
			}
			u = t[u][b];
			num[u] += val;
			if (b) {
				ans ^= (1 << i);
			}
			x >>= 1;
		}
	};
	auto rev = [&]() -> void {
		int u = 0;
		for (int i = 0; i <= 18; i ++) {
			std::swap(t[u][0], t[u][1]);
			if ((num[t[u][0]] + num[t[u][1]]) & 1) {
				ans ^= (1 << i);
			}
			if (t[u][0]) {
				u = t[u][0];
			} else {
				break;
			}
		}
	};
	for (int i = 1; i <= n; i ++) {
		insert(v[i], 1);
	}
	int add = 0;
	while (q --) {
		int op;
		std::cin >> op;
		if (op == 0) {
			int x, p;
			std::cin >> x >> p;
			insert(v[x] + add, -1);
			v[x] = p - add;
			insert(p, 1);
		} else if (op == 1) {
			add ++;
			rev();
		} else {
			std::cout << ans << '\n';
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