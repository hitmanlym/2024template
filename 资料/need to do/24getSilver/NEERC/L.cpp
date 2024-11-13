#include<bits/stdc++.h>
using i64 = long long;

int til = 0; // 最少用前几个.
struct xorGuess {
	int n, m;
	std::vector<std::bitset<2010> > M;
	void init(int n, int m, std::vector<std::vector<bool> > &X) {
		this -> n = n;
		this -> m = m;
		M.assign(m + 1, std::bitset<2010>());
		for (int i = 1; i <= m; i ++) {
			for (int j = 0; j <= n; j ++) {
				M[i].set(j, X[i][j]);
			}
		}
	}
	std::vector<std::array<int, 2> > get() { // 0 位置是常数.
		int use = 0;
		std::vector<bool> go(m + 1);
		for (int i = 1; i <= n; i ++) {
			int cur = i;
			while (cur <= m && ! M[cur][i]) cur ++;
			if (cur > m) {
				continue;
			}
			til = std::max(til, cur);
			if (cur != i) std::swap(M[i], M[cur]);
			for (int j = 1; j <= m; j ++) {
				if (i == j) continue;
				if (M[j][i]) {
					M[j] ^= M[i];
				}
			}
			go[i] = 1;
			use ++;
		}
		for (int i = 1; i <= m; i ++) {
			if (go[i]) continue;
			if (M[i][0]) return std::vector<std::array<int, 2> >(0); // 无解
		}
		// b[0] 位置 —— 存在自由元
		std::vector<std::array<int, 2> > b(n + 1, {0, 0});
		if (use < n) b[0][0] = 1; // 当存在自由元的检测.
		for (int i = 1; i <= n; i ++) {
			b[i] = {go[i], M[i][0]}; // if have, answer.
		}
		return b;
	}
} tr;

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<bool> > a(n + 1, std::vector<bool>(n + 1));
	std::vector<int> d(n + 1);
	std::vector<std::vector<int> > e(n + 1);
	for (int i = 1; i <= m; i ++) {
		int u, v;
		std::cin >> u >> v;
		d[u] ++;
		d[v] ++;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	bool f = 0;
	std::vector<int> ans(n + 1);
	for (int i = 1; i <= n; i ++) {
		if (d[i] & 1) f = 1;
	}
	if (! f) {
		for (int i = 1; i <= n; i ++) {
			ans[i] = 1;
		}
	} else {
		for (int i = 1; i <= n; i ++) {
			for (auto it : e[i]) {
				a[i][it] = 1;
			}
			if (d[i] & 1) {
				a[i][i] = 1;
				a[i][0] = 1;
			} 
		}

		til = 0;
		tr.init(n, n, a);
		auto it = tr.get();
		for (int i = 1; i <= n; i ++) {
			ans[i] = (int)it[i][1] + 1;
		}
	}
	std::cout << f + 1 << '\n';
	for (int i = 1; i <= n; i ++) {
		std::cout << ans[i] << ' ';
	}
	std::cout << '\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}