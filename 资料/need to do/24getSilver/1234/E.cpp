#include<bits/stdc++.h>
using i64 = long long;
#define int i64
// const int inf = 1e17;
const int N = 1e6 + 10;
// char s[N + 1];
void solve() {
	int n, k;

	std::cin >> n >> k;
	std::string s;
	std::cin >> s;
	s = " " + s;
	
	// scanf("%s", s);
	int max = 0;
	if (n < 7) {
		std::cout << 0 << '\n';
		return ;
	}
	for (int i = 0; i <= std::min(k, 7ll); i ++) {
		std::string t = "";
		for (int j = i; j < n; j ++) {
			t += s[j];
		}
		for (int j = 0; j < i; j ++) {
			t += s[j];
		}
		int res = 0;
		for (int j = 0; j + 6 < n; j ++) {// nanjing
			std::string op = "";
			for (int k = j; k <= j + 6; k ++) {
				op += t[k];
			}
			if (op == "nanjing") {
				j += 6;
				res ++;
			}
		}
		max = std::max(max, res);
	}
	std::cout << max << '\n';
}
signed main() {
	// std::ios::sync_with_stdio(false);
	// std::cin.tie(nullptr);
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