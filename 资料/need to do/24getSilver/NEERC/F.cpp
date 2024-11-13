#include<bits/stdc++.h>
using i64 = long long;
#define int i64
void solve() {
	int n;
	std::cin >> n;
	std::priority_queue<int> q1, q2, q0;
	int num = 0, ans = 0;
	for (int i = 0; i < n; i ++) {
		std::string s;
		std::cin >> s;
		int op = (s[0] - '0') * 2 + (s[1] - '0');
		int x;
		std::cin >> x;
		if (op == 3) {
			num ++;	
			ans += x;
		} else {
			if (op == 1) {
				q1.push(x);
			} else if (op == 2) {
				q2.push(x);
			} else {	
				q0.push(x);
			}
		}
	}
	while (q1.size() && q2.size()) {
		ans += q1.top() + q2.top();
		q1.pop();
		q2.pop();
	}
	while (q1.size()) {
		q0.push(q1.top());
		q1.pop();
	}
	while (q2.size()) {
		q0.push(q2.top());
		q2.pop();
	}
	while (num && q0.size()) {
		num --;
		ans += q0.top();
		q0.pop();
	}
	std::cout << ans << '\n';
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