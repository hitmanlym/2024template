#include<bits/stdc++.h>
using i64 = long long;

using pii = std::array<int, 2>;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> b1(m + 1), b2(m + 1), f1(m + 1), f2(m + 1), t(m + 1);
	for (int i = 1; i <= m; i ++) {
		std::cin >> t[i];
		char c;
		for (int j = 0; j < n; j ++) {
			std::cin >> c;
			if (c == '+') {
				b1[i] |= 1 << j;
			} else if (c == '-') {
				b2[i] |= 1 << j;
			}
		}
		for (int j = 0; j < n; j ++) {
			std::cin >> c;
			if (c == '-') {
				f1[i] |= 1 << j;
			} else if (c == '+') {
				f2[i] |= 1 << j;
			}
		}
	}

	int now = (1 << n) - 1;
	std::vector<bool> vis(now + 1);
	std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
	q.push({0, now});
	while (! q.empty()) {
		auto it = q.top(); q.pop();
		int u = it[1], w = it[0];
		if (u == 0) {
			std::cout << w << '\n';
			return ;
		}
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = 1; i <= m; i ++) {
			if ((u | b1[i]) != u || (u & (~ b2[i])) != u) continue;
			int v = (u & (~ f1[i])) | f2[i];
			q.push({w + t[i], v});
		}
	}
	std::cout << 0 << '\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}