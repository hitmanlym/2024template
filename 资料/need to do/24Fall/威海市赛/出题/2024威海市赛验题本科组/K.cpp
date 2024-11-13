#include<bits/stdc++.h>
using i64 = long long;
const int N = 1e7 + 1;
std::vector<int> kmp(std::string s) {
	int n = s.size();
	std::vector<int> f(n + 1);
	for (int i = 1, j = 0; i < n; i ++) {
		while (j && s[i] != s[j]) {
			j = f[j];
		}
		j += (s[i] == s[j]);
		f[i + 1] = j;
	}
	return f;
}
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::string s;
	std::cin >> s;
	auto p = kmp(s);
	std::vector<std::vector<int > > e(n + 2); // 1 means empty
	for (int i = 1; i <= n; i ++) {
		e[p[i] + 1].push_back(i + 1);
		e[i + 1].push_back(p[i] + 1); // tmd是双向边....
	}
	n ++;
	std::vector<int> a(n + 1), qs(m + 1), ans(m + 1);
	std::vector<bool> have(N);
	for (int i = 2; i <= n; i ++) {
		a[i] = (i - 1) ^ p[i - 1];
	}	
	for (int i = 1; i <= m; i ++) {
		std::cin >> qs[i];
	}

	// for (int i = 1; i <= n; i ++) {
	// 	std::cout << a[i] << ' ';
	// }
	// std::cout << '\n';
	// for (int i = 1; i < n; i ++) {
	// 	std::cout << p[i] + 1 << ' ' << i + 1 << '\n';
	// }

	std::vector<bool> vis(n + 1);
	std::vector<int> maxp(n + 1), siz(n + 1);
	int rt, Sum = n;
	maxp[rt = 0] = n;
	
	auto getRoot = [&](auto self, int u, int p) -> void {
		siz[u] = 1;
		maxp[u] = 0;
		for (auto v : e[u]) {
			if (v == p || vis[v]) continue;
			self(self, v, u);
			siz[u] += siz[v];
			maxp[u] = std::max(maxp[u], siz[v]);
		}
		maxp[u] = std::max(maxp[u], Sum - siz[u]);
		if (maxp[u] < maxp[rt]) rt = u;
	};

	std::vector<int> sum(n + 1), qsum(n + 1), qremove(n + 1);
	auto getSum = [&](auto self, int u, int p) -> void {
		qsum[++ qsum[0]] = sum[u];
		for (auto v : e[u]) {
			if (v == p || vis[v]) continue;
			sum[v] = sum[u] + a[v];
			self(self, v, u);
		}
	};
	auto calc = [&](int u) -> void {
		// std::cout << "??? : " << u << '\n';
		qremove[0] = 0;
		for (auto v : e[u]) {
			if (vis[v]) continue;
			sum[v] = a[v];
			qsum[0] = 0;
			getSum(getSum, v, u);
			for (int i = 1; i <= qsum[0]; i ++) {
				for (int j = 1; j <= m; j ++) {
					if (a[u] + qsum[i] <= qs[j]) {
						ans[j] |= have[qs[j] - a[u] - qsum[i]];
					}
				}
			}
			for (int i = 1; i <= qsum[0]; i ++) {
				if (qsum[i] < N) {
					have[qsum[i]] = 1;
					qremove[++ qremove[0]] = qsum[i];
				}
			}
		}
		// 必须是前缀吧.

		for (int i = 1; i <= qremove[0]; i ++) {
			have[qremove[i]] = 0;
		}
	};
	auto dfz = [&](auto self, int u) -> void {
		vis[u] = 1;
		have[0] = 1;
		calc(u);
		for (auto v : e[u]) {
			if (vis[v]) continue;
			Sum = siz[v];
			maxp[rt = 0] = Sum;
			getRoot(getRoot, v, 0);
			self(self, rt);
		}
	};
	getRoot(getRoot, 1, 0);
	dfz(dfz, rt);
	for (int i = 1; i <= m; i ++) {
		if (ans[i]) {
			std::cout << "Yes\n";
		} else {
			std::cout << "No\n";
		}
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}