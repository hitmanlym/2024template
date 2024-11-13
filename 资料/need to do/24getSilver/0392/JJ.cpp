#include<bits/stdc++.h>
using i64 = long long;
const int N = 1e5 + 10;

std::bitset<N> bit, now, ok;
void solve() {
	int n;
	std::cin >> n;
	std::string s, t;
	std::cin >> s >> t;
	std::vector<int> pre(n + 1);
	for (int i = 0; i < n; i ++) {
		pre[i + 1] = pre[i] + (s[i] == '1' ? 1 : -1);
		bit[i + 1] = 1;
	}
	std::map<int, std::vector<int> > mp;
	for (int i = 0; i <= n; i ++) {
		now[i] = 0;
		mp[pre[i]].push_back(i);
	}
	for (auto it : mp) {
		for (auto pos : it.second) {
			if (pos == 0) continue;
			ok = (now >> (n - pos));
			if (now[n]) {
				ok |= (bit >> pos) << pos;
			}
			if (t[pos - 1] == '0') {
				bit &= ok.flip();
			} else {
				bit &= ok;
			}
		}
		for (auto pos : it.second) {
			now[n - pos] = 1;
		}
	}
	for (int i = 1; i <= n; i ++) {
		std::cout << bit[i];
	}
	std::cout << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}