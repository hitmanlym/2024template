#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
const int N = 3e3 + 10;
struct Trie { // number
	static const int mx = 30;
	int root, cnt = 0, nxt[N * mx][2];
	int val[N * mx];
	int newnode() {
		++ cnt;
		memset(nxt[cnt], 0, sizeof nxt[cnt]);
		val[cnt] = 0;
		return cnt;
	}
	void init() {
		cnt = 0;
		memset(nxt[cnt], 0, sizeof nxt[cnt]);
		val[cnt] = 0;
		root = newnode();
	}
	void add(int x, int v = 1) {
		int u = root;
		for (int i = mx; i >= 0; i --) {
			val[u] ++;
			int t = (x >> i) & 1;
			if (! nxt[u][t]) nxt[u][t] = newnode();
			u = nxt[u][t];
		}

		val[u] ++;
	}
	int query(int x) {
		int u = root, res = 0;
		for (int i = mx; i >= 0; i --) {
			int t = (x >> i) & 1;
			if (val[nxt[u][t]] == (1 << i)) {
				res += (1 << i);
				u = nxt[u][t ^ 1];
			} else {
				u = nxt[u][t];
			}
 		}
		return res;
	}
};
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n + 1), oc(N);
	std::set<int> st;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		oc[a[i]] = 1;
		st.insert(a[i]);
	}
	std::vector<int> max(N);
	Trie t;
	for (auto u : st) {
		// for (int i = 0; ; i ++) {
		// 	if ((u ^ i) < N && oc[u ^ i]) {
		// 		max[u] ++;
		// 	} else {
		// 		break;
		// 	}
		// }
		t.add(u);
	}	
	// for (int i = 0; i <= n; i ++) {
	// 	std::cout << max[i] << ' ';
	// }
	// std::cout << '\n';
	int now = 0;
	while (m --) {
		int x;
		std::cin >> x;
		now ^= x;
		// int id = t.query(now);
		// if (id != -1)
		// std::cout << max[now] << '\n';
		// else {
		// 	std::cout << 0 << '\n';
		// }
		std::cout << t.query(now) << '\n';
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