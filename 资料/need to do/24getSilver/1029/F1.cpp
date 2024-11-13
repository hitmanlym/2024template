#include<bits/stdc++.h>
using i64 = long long;
// #define int i64
int NUM(int x, int k) {
	int res = 0;
	for (int i = 0; i < k; i ++) {
		if (x % 3 == 0) {
			res --;
		} else if (x % 3 == 1) {
			res ++;
		} else if (x % 3 == 2) {

		}
		x /= 3;
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
		pp = pp * 3;
	}
	auto check = [&](int op, int fg) -> void {
		std::vector<int> a(k);
		for (int i = 0; i < k; i ++) {
			if (op % 3 == 0) {
				a[i] = num - 1 + fg;
			} else if (op % 3 == 1) {
				a[i] = num + 1 + fg;
			} else {
				a[i] = num + fg;
			}
			op /= 3;
			if (a[i] < 1 || a[i] > ans.size()) {
				return ;
			}
		}

		std::string now = "";
		int l = 0;
		for (int i = 0; i < k; i ++) {
			std::string t = "";
			for (int j = 0; j < a[i]; j ++) {
				t += s[l ++];
			}
			// std::cout << "??? " << now << ' ' << t << '\n';
			if (t.size() > ans.size()) return ;
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
		int it = NUM(i, k);
		if (it == res) {
			check(i, 0);
		} else if (it == res - k) {
			check(i, 1);
		}
		
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