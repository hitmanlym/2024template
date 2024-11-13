#include<bits/stdc++.h>
using i64 = long long;

const int N = 6e5 + 10;
struct Trie {
	int nxt[N][26], cnt;
	bool vis[N];
	int exist[N];
	void init() {
		memset(nxt, 0, sizeof nxt);
		cnt = 1;
	}
	void insert(const std::string &s) {
		int cur = 1;
		for (auto c : s) {
			if (! nxt[cur][c - 'a']) {
				nxt[cur][c - 'a'] = ++ cnt;
			}
			cur = nxt[cur][c - 'a'];
			exist[cur] ++;
		}
	}
	int finds(const std::string &s) {
		int cur = 1, ans = 0;
		for (auto c : s) {
			if (! nxt[cur][c - 'a']) {
				return ans;
			}
			cur = nxt[cur][c - 'a'];
			ans += exist[cur];
		}
		return ans;
	}
};

void solve() {
	Trie T;
    T.init();
	int n;
	std::cin >> n;
	std::vector<std::string> s(n);
	for (int i = 0; i < n; i ++) {
		std::cin >> s[i];
	}
	int ans = 0;
	for (int i = n - 1; i >= 0; i --) {
		ans = (ans + T.finds(s[i]));
		T.insert(s[i]);
	}
	std::cout << ans << '\n';
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