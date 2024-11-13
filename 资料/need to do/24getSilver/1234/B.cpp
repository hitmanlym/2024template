#include<bits/stdc++.h>
using i64 = long long;
#define int i64
// const int inf = 1e17;
void solve() {
	std::string s;
	std::cin >> s;
	std::vector<int> a;
	for (auto c : s) {
		a.push_back(c - '0');
	}
	int n = s.size();
	for (int i = 0; i < n; i ++) {
		if (i & 1) {
			if (a[i] != 2) a[i] ^= 1;
		}
	}
	int num0 = 0, num1 = 0, res = 0;
	for (auto o : a) {
		if (o == 0) num0 ++;
		else if (o == 1) num1 ++;
	}
	res = n - num0 - num1;
	if (std::abs(num0 - num1) >= res) {
		std::cout << std::abs(num0 - num1) - res << '\n';
	} else {
		std::cout << ((res - std::abs(num0 - num1)) & 1) << '\n';
	}
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

/// 


// aabcc
// ccbaa

// aabccccbaa
// ccbaabcc

/*
3
4 5 3
ULDDRR
4 5 0
UUUUUUU
4 5 10
UUUUUUU
*/