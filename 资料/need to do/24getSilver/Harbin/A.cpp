#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
void solve() {
	int l, r;
	std::cin >> l >> r;
	if (l == r) {
		std::vector<int> b;
		while (l) {
			b.push_back(l % 2);
			l /= 2;
		}
		std::reverse(b.begin(), b.end());

		std::cout << b.size() + 1 << '\n';
		for (int i = 0; i < (int)b.size(); i ++) {
			std::cout << 1 << ' ';
			std::cout << i + 2 << ' ' << b[i] << '\n';
		}
		std::cout << 0 << '\n';
		return ;
	}
	int cnt = 0;
	int s = ++ cnt;
	int t = ++ cnt;
	std::vector<int> L, R;
	while (l) {
		L.push_back(l % 2);
		l /= 2;
	}
	while (r) {
		R.push_back(r % 2);
		r /= 2;
	}
	int o = R.size();
	o --;
	std::vector<int> free(o + 1); // x 位随便
	free[0] = t;
	std::vector<std::vector<pii> > e((o + 1) * 4 + 1);
	for (int i = 1; i <= o; i ++) {
		free[i] = ++ cnt;
		e[cnt].push_back({free[i - 1], 0});
		e[cnt].push_back({free[i - 1], 1});
	}
	if (L.size() == R.size()) {

		std::reverse(L.begin(), L.end());
		std::reverse(R.begin(), R.end());
		int pre = s, now = 0;
		while (L[now] == R[now]) {
			e[pre].push_back({++ cnt, L[now]});
			pre = cnt;
			now ++;
		}
		int max = 2;
		int U = cnt;
		{	
			pre = U;
			for (int i = now; i < L.size(); i ++) {
				if (i == L.size() - 1) {
					e[pre].push_back({t, L[i]});
				} else {
					e[pre].push_back({++ cnt, L[i]});
				}
				if (L[i] == 0 && pre != U) {
					e[pre].push_back({free[L.size() - 1 - i], 1});
					max = std::max(max, free[L.size() - 1 - i]);
				}
				pre = cnt;
			}
			pre = U;
			for (int i = now; i < R.size(); i ++) {
				if (i == R.size() - 1) {
					e[pre].push_back({t, R[i]});
				} else {
					e[pre].push_back({++ cnt, R[i]});
				}
				if (R[i] == 1 && pre != U) {
					e[pre].push_back({free[R.size() - 1 - i], 0});
					max = std::max(max, free[R.size() - 1 - i]);
				}
				pre = cnt;
			}
		}

		int d = o + 2 - max;
		// std::cout << "!!  " << max << ' ' << d << '\n';
		// if (max != 0) {
		// 	std::cout << "!!! " << max << '\n';
		// 	d = o - max;
		// }

		// std::cout << d << '\n';
		// return ;
		// > max --> -d
		std::cout << cnt - d << '\n';
		for (int i = 1; i <= cnt; i ++) {
			if (i > max && i < max + d + 1) continue;
			std::cout << e[i].size() << ' ';
			for (auto it : e[i]) {
				int v = it[0], w = it[1];
				if (v > max) v -= d;
				std::cout << v << ' ' << w << ' ';
			}
			std::cout << '\n';
		}
		return ;
	}
	int max = 2;
	for (int i = L.size(); i < R.size() - 1; i ++) {
		e[s].push_back({free[i], 1});
		max = std::max(max, free[i]);
		// std::cout << "??? " << i << '\n';
	}
	std::reverse(L.begin(), L.end());
	std::reverse(R.begin(), R.end());
	int pre;
	pre = s;
	
	for (int i = 0; i < L.size(); i ++) {
		if (i == L.size() - 1) {
			e[pre].push_back({t, L[i]});
		} else {
			e[pre].push_back({++ cnt, L[i]});
		}
		if (L[i] == 0 && pre != s) {
			e[pre].push_back({free[L.size() - 1 - i], 1});
			// std::cout << "!!! " << L.size() - 1 - i << '\n'; 
			max = std::max(max, free[L.size() - 1 - i]);
		}
		pre = cnt;
	}
	pre = s;
	for (int i = 0; i < R.size(); i ++) {
		if (i == R.size() - 1) {
			e[pre].push_back({t, R[i]});
		} else {
			e[pre].push_back({++ cnt, R[i]});
		}
		if (R[i] == 1 && pre != s) {
			e[pre].push_back({free[R.size() - 1 - i], 0});
			// std::cout << "!!! " << R.size() - 1 - i << '\n'; 
			max = std::max(max, free[R.size() - 1 - i]);
		}
		pre = cnt;
	}
	int d = o + 2 - max;
	// std::cout << "!!! " << max << ' ' << d << ' ' << o << '\n';
	std::cout << cnt - d << '\n';
	for (int i = 1; i <= cnt; i ++) {
		if (i > max && i < max + d + 1) continue;
		std::cout << e[i].size() << ' ';
		for (auto it : e[i]) {
			int v = it[0], w = it[1];
			if (v > max) v -= d;
			std::cout << v << ' ' << w << ' ';
		}
		std::cout << '\n';
	}
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}