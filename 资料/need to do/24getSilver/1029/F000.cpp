#include<bits/stdc++.h>
using i64 = long long;
#define int i64
int NUM(int x, int k) {
	int res = 0;
	for (int i = 0; i < k; i ++) {
		if (x % 4 == 0) {
			res -= 2;
		} else if (x % 4 == 1) {
			res -= 1;
		} else if (x % 4 == 2) {

		} else if (x % 4 == 3) {
			res += 1;
		}
		x /= 4;
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
	int pp = 1;
	for (int i = 0; i < k; i ++) {
		pp = pp * 4;
	}
	auto check = [&](int op) -> void {
		std::vector<int> a(k);
		for (int i = 0; i < k; i ++) {
			if (op % 4 == 0) {
				a[i] = num - 2;
			} else if (op % 4 == 1) {
				a[i] = num - 1;
			} else if (op % 4 == 2) {
				a[i] = num;
			} else if (op % 4 == 3) {
				a[i] = num + 1;
			}
			op /= 4;
			if (a[i] < 1) return ;
		}

		// for (int i = 0; i < k; i ++) {
		// 	std::cout << a[i] << ' ';
		// }
		// std::cout << '\n';

		std::string now = "";
		int l = 0;
		for (int i = 0; i < k; i ++) {
			std::string t = "";
			// if (a[i] > num + 1 && s[l] > s[l + 1]) {
			// 	return ;
			// }
			for (int j = 0; j < a[i]; j ++) {
				t += s[l ++];
			}
			// std::cout << "??? " << now << ' ' << t << '\n';
			now = add(now, t);
			if (now.size() > ans.size()) return ;
		}
		// std::cout << "!!! " << now << '\n';
		// update ans.
		if (now.size() < ans.size()) {
			ans = now;
		} else if (now < ans) {
			ans = now;
		}
	};
	for (int i = 0; i < pp; i ++) {
		if (NUM(i, k) != res) continue;
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

1
6 2
911111
*/