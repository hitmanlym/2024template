#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int inf = 1e9;
void solve() {
	std::string s, t;
	std::cin >> s;
	std::vector<int> a;
	std::cin >> s; 
	char var;
	std::cin >> var;
	std::cin >> s; std::cin >> s;
	int from = 0, to = 0, step = 1;
	int op = 0;

	// std::cout << "\n!!" << s << '\n';
	for (int i = 6; i < s.size(); i ++) {
		if (s[i] != '-' && (s[i] < '0' || s[i] > '9')) {
			continue;
		}
		int num = 0, f = 1;
		if (s[i] == '-') {
			f = -1;
			i ++;
		}
		while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
			num = num * 10 + s[i] - '0';
			i ++;
		}	

		num *= f;
		if (op == 0) {
			op = 1;
			from = num;
		} else if (op == 1) {
			op = 2;
			to = num;
		} else if (op == 2) {
			step = num;
			op = 3;
		}
	}
	if (step > 0) {
		while (from < to) {
			a.push_back(from);
			from += step;
		}
	} else {
		while (from > to) {
			a.push_back(from);
			from += step;
		}
	}
	std::cin >> s;
	std::cin >> s;
	std::cin >> s;
	std::cin >> s;
	step = 1; from = 0; to = 0; op = 0;
	for (int i = 6; i < s.size(); i ++) {
		int num = 0, f = 1;

		if (s[i] != '-' && (s[i] < '0' || s[i] > '9') && s[i] != var) {
			continue;
		}
		if (s[i] == var) {
			if (op == 0) {
				from = inf;
				op = 1;
			} else if (op == 1) {
				op = 2;
				to = inf;
			} else if (op == 2) {
				step = inf;
				op = 3;
			}
			i ++;
			continue;
		}

		if (s[i] == '-') {
			f = -1;
			i ++;
		}
		while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
			num = num * 10 + s[i] - '0';
			i ++;
		}
		num *= f;

		if (op == 0) {
			op = 1;
			from = num;
		} else if (op == 1) {
			op = 2;
			to = num;
		} else if (op == 2) {
			step = num;
			op = 3;
		}
	}
	i64 ans = 0;
	// std::cout << '\n';
	for (auto it : a) {

		// std::cout << it << ' ';

		int x, y, z;
		if (from == inf) {
			x = it;
		} else {
			x = from;
		}

		if (to == inf) {
			y = it;
		} else {
			y = to;
		}

		if (step == inf) {
			z = it;
		} else {
			z = step;
		}
		if (z > 0) {
			if (y <= x) continue; 
			int l = 0, r = 1e6, op;
			while (l <= r) {
				int mid = l + r >> 1;
				if (x + z * mid < y) {
					op = mid;
					l = mid + 1; 
				} else {
					r = mid - 1;
				}
			}
			//std::cout << x << ' ' << y << ' ' << z << ' ' << op << '\n';
			int L = x, R = x + op * z;
			ans += 1ll * (L + R) * (op + 1) / 2;
		} else {
			if (y >= x) continue;
			int l = 0, r = 1e6, op;
			while (l <= r) {
				int mid = l + r >> 1;
				if (x + z * mid > y) {
					op = mid;
					l = mid + 1;
				} else {
					r = mid - 1;
				}
			}
			//std::cout << x << ' ' << y << ' ' << z << ' ' << op << '\n';
			int L = x, R = x + op * z;
			//std::cout << L << ' ' << R << ' ' << op << '\n';
			ans += 1ll * (L + R) * (op + 1) / 2;
		}
	}
	// std::cout << '\n';
	std::cin >> s;
	std::cin >> s;
	std::cout << ans << '\n';
}
signed main() {	
	int t = 1;
	while (t --) {
		solve();
	}

	return 0;
}