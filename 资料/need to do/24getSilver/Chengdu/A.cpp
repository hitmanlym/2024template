#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
void solve() {
	std::string s;
	std::cin >> s;
	std::vector<pii> ans;
	bool f = 0;
	for (auto c : s) {
		if (c == '-') f = 1;
	}
	int n = s.size();
	int l = 0;
	while (l < n - 4 && s[l] == '>') {
		ans.push_back({l + 1, n});
		l ++;
	}
	if (! f || l == 0 || s[n - 1] == '-' || s[n - 2] == '-' || s[n - 3] == '-') {
		std::cout << "No\n";
		return ;
	}
	int L = ans.back()[0];
	ans.pop_back();
	int r = n;
	while (r >= l) {
		if (r - l + 1 <= 5) {
			ans.push_back({L, L + 4});
			break;
		}
		ans.push_back({L, r});
		r -= 3;
	}
	std::vector<pii> h;
	for (int i = 0; i < n; i ++) {
		if (s[i] == '>') continue;
 		int j = i;
		while (j < n && s[j] == '-') {
			j ++;
		}
		int num = j - i;
		// std::cout << i << ' ' << num << ' ' << j  << '\n';
		ans.push_back({i, i + num + 3});
		i = j - 1;
	}
	std::cout << "Yes " << ans.size() << '\n';
	for (auto it : ans) {
		std::cout << it[0] << ' ' << it[1] - it[0] + 1 << '\n';
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
/*
4
>>->>>
>>>->
>>>>>
>->>>>>>

1
>>>->>>
 */