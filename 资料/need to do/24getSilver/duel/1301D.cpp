#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 998244353;
int qmi(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) {
			res = 1ll * res * a % mod;
		}
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return res;
}
void solve() {
	int n, m, k;
	std::cin >> n >> m >> k;
	int num = n * m * 4 - (n + m) * 2;
	if (k > num) {
		std::cout << "NO" << '\n';
		return ;
	}
	std::cout << "YES\n";
	std::vector<int> ans_p;
	std::vector<std::string> ans_s;
	// 1
	int ti;
	ti = std::min(m - 1, k / (2 * (n - 1) + 1));
	k -= ti * (2 * (n - 1) + 1);
	for (int j = 1; j <= ti; j ++) {
		ans_p.push_back(1);
		ans_s.push_back("R");
		if (n - 1) {
			ans_p.push_back(n - 1);
			ans_s.push_back("D");
			ans_p.push_back(n - 1);
			ans_s.push_back("U");
		}
	}
	if (k && ti < m - 1) { // 不够了
		ans_p.push_back(1);
		ans_s.push_back("R");
		k --;
		if (k) {
			int op = std::min(k, n - 1);
			ans_p.push_back(op);
			ans_s.push_back("D");
			k -= op;
		}
		if (k) {
			int op = std::min(k, n - 1);
			ans_p.push_back(op);
			ans_s.push_back("U");
			k -= op;
		}
	}
	// 2
	ti = std::min(m - 1, k);
	k -= ti;
	if (ti) {
		ans_p.push_back(ti);
		std::string t = "L";
		ans_s.push_back(t);
	}
	// 3
	ti = std::min(n - 1, k / (2 * (m - 1) + 1));
	k -= ti * (2 * (m - 1) + 1);
	for (int j = 1; j <= ti; j ++) {
		ans_p.push_back(1);
		ans_s.push_back("D");
		if (m - 1) {
			ans_p.push_back(m - 1);
			ans_s.push_back("R");
			ans_p.push_back(m - 1);
			ans_s.push_back("L");
		}
	}
	if (k && ti < n - 1) { // 不够了
		ans_p.push_back(1);
		ans_s.push_back("D");
		k --;
		if (k) {
			int op = std::min(k, m - 1);
			ans_p.push_back(op);
			ans_s.push_back("R");
			k -= op;
		}
		if (k) {
			int op = std::min(k, m - 1);
			ans_p.push_back(op);
			ans_s.push_back("L");
			k -= op;
		}
	}
	// 4
	ti = std::min(n - 1, k);
	k -= ti;
	if (ti) {
		ans_p.push_back(ti);
		std::string t = "U";
		ans_s.push_back(t);
	}
	std::cout << ans_p.size() << '\n';
	for (int i = 0; i < ans_p.size(); i ++) {
		std::cout << ans_p[i] << ' ' << ans_s[i] << '\n';
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
/*
*/