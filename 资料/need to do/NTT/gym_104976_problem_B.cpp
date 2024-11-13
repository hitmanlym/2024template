#include<bits/stdc++.h>
using i64 = long long;
const int N = 2500001, B = 501;
std::bitset<N> q, all, ex[B];
void solve() {
	int n, Q, id = -1;
	std::cin >> n >> Q;
	std::vector<int> x(n + 1), c(n + 1), rev(n + 1);
	std::vector<std::vector<int> > col(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> x[i] >> c[i];
		col[c[i]].push_back(x[i]);
		all.set(x[i]);
	}
	for (int i = 1; i <= n; i ++) {
		if (col[i].size() > B) {
			rev[i] = ++ id;
			for (auto it : col[i]) {
				ex[id].set(it);
			}
		}
	}
	std::vector<int> k(Q + 1), ans(N);
	for (int i = 1; i <= Q; i ++) {
		std::cin >> k[i];
		q.set(k[i]);
	}

	for (int i = 1; i <= n; i ++) {
		std::bitset<N> cur = all, tmp = q;
		if (col[c[i]].size() <= B) {
			for (auto it : col[c[i]]) cur.reset(it);
		} else {
			cur ^= ex[rev[c[i]]];
		}

		tmp &= (cur >> x[i]);
		for (int j = tmp._Find_first(); j != tmp.size(); j = tmp._Find_next(j)) {
			ans[j] = i;
			q.reset(j);
		}
	}
	for (int i = 1; i <= Q; i ++) {
		std::cout << ans[k[i]] << '\n';
	}
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