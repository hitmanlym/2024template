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
std::map<std::array<int, 2>, std::vector<std::vector<int> > > mp;
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
		// std::cout << ok << '\n';
		while (ok) {
			res.push_back((char)(ok % 10 + '0'));
			ok /= 10;
		}
		std::reverse(res.begin(), res.end());
		return res;
	};
	auto check = [&](std::vector<int> a) -> void {
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
			if (now.size() > ans.size()) return ;
		}
		// std::cout << "!!! " << now << '\n';
		// update ans.
		if (now.size() < ans.size()) {
			ans = now;
		} else if (now < ans) {
			ans = now;
		}
	}; // 
	
	std::array<int, 2> lol;
	std::vector<int> fk;
	auto dfs = [&](auto self, int i, int sum) {
		if (i == lol[0]) {
			if (sum == lol[1])
			mp[lol].push_back(fk);
			return ;
		}
		for (int j = 0; j <= std::min(num, lol[1] - sum); j ++) {
			fk[i] = j;
			self(self, i + 1, sum + j);
		}
	};
	for (int i = 0; i < (1 << k); i ++) {
		int x = NUM(i);
		if (x < res || x == k) continue;
		std::vector<int> a(k), b(k);
		for (int j = 0; j < k; j ++) {
			if (i >> j & 1) {
				a[j] = num + 1;
			}
		}
		int o = k - x;
		int bear = x - res;
		// std::cout << "??? " << o << ' ' << bear << '\n';
		if (! mp[{o, bear}].size()) {
			fk.resize(o);
			lol = {o, bear};
			dfs(dfs, 0, 0);
		}
		for (auto it : mp[{o, bear}]) {
			int l = 0;
			for (int j = 0; j < k; j ++) {
				if (a[j]) b[j] = a[j];
				else {
					b[j] = num - it[l];
					if (b[j] < 1) break;
					l ++;
				}
			}
			if (l == o) {
				check(b);
			}
		}
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