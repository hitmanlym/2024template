#include<bits/stdc++.h>
using i64 = long long;
const int mod = 1e9 + 7;

const int N = 2e5 + 10;
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
	void add(int x, int v) {
		int u = root;
		for (int i = mx; i >= 0; i --) {
			int t = (x >> i) & 1;
			if (! nxt[u][t]) nxt[u][t] = newnode();
			u = nxt[u][t];
			val[u] = (val[u] + v) % mod;
		}
	}
	int query(int x, int k) { // x xor it <= k
		int u = root;
		int res = 0;
		for (int i = mx; i >= 0; i --) {
			int t = (x >> i) & 1;
			if ((k >> i) & 1) {
				if (nxt[u][t]) {
					res = (res + val[nxt[u][t]]) % mod;
				}
				u = nxt[u][t ^ 1];
			} else {
				u = nxt[u][t];
			}
		}
		res = (res + val[u]) % mod;
		return res;
	}
};
void solve() {
	
}
signed main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}