#include<bits/stdc++.h>
using i64 = long long;
#define int i64
int NUM(int x) {
	int res = 0;
	while (x) {
		res ++;
		x -= (x & (-x));
	}
	return res;
}
void solve() {
	int n, k;
	std::cin >> n >> k;
	k ++;
	std::string s;
	std::cin >> s;
	int num = n / k, res = n % k;
	// std::cout << "??? " << num << '\n';
	std::string ans = s;
	auto add = [&](std::string a, std::string b) -> std::string {
		if (a.size() == 0) return b;
		if (b.size() == 0) return a;

		// std::cout << a << ' ' << b << '\n';
		std::string res = "";
		int ok = 0;
		while (a.size() && b.size()) {
			int u = a.back() - '0', v = b.back() - '0';
			ok = ok + u + v;
			res.push_back((char)(ok % 10 + '0'));
			ok /= 10;
			a.pop_back();
			b.pop_back();
		}
		while (a.size()) {
			int u = a.back() - '0';
			ok = ok + u;
			res.push_back((char)(ok % 10 + '0'));
			ok /= 10;
			a.pop_back();
		}
		while (b.size()) {
			int v = b.back() - '0';
			ok = ok + v;
			res.push_back((char)(ok % 10 + '0'));
			ok /= 10;
			b.pop_back();
		}
		while (ok) {
			res.push_back((char)(ok % 10 + '0'));
			ok /= 10;
		}
		std::reverse(res.begin(), res.end());
		return res;
	};
	auto check = [&](int op) -> void {
		std::vector<int> a(k);
		for (int i = 0; i < k; i ++) {
			if ((op >> i) & 1) {
				a[i] = num + 1;
			} else {
				a[i] = num;
			}
			// std::cout << a[i] << ' ';
		}
		// for (int i = 0; i < k; i ++) {
		// 	std::cout << a[i] << ' ';
		// }
		// std::cout << '\n';

		std::string now = "";
		int l = 0;
		for (int i = 0; i < k; i ++) {
			std::string t = "";
			for (int j = 0; j < a[i]; j ++) {
				t += s[l ++];
			}
			// std::cout << "??? " << now << ' ' << t << '\n';
			now = add(now, t);
		}
		// std::cout << "!!! " << now << '\n';
		// update ans.
		if (now.size() > ans.size()) {
			return ;
		}
		if (now.size() < ans.size()) {
			ans = now;
		} else if (now < ans) {
			ans = now;
		}
	};
	for (int i = 0; i < (1ll << k); i ++) {
		if (NUM(i) != res) continue;
		check(i);
		// std::cout << i << ' ' << ans << '\n';
	}
	std::cout << ans << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}
/*
1
2 1
42
*/