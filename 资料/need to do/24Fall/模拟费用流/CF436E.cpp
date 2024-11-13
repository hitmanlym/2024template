#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
void solve() {
	int n, w;
	std::cin >> n >> w;
	std::vector<pii> a(n + 1);
	// 
	std::priority_queue<pii, std::vector<pii>, std::greater<pii> >
		q1, q2, q3, q4, q5;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i][0] >> a[i][1];
		q1.push({a[i][0], i});
		q3.push({a[i][1], i});
	}
	std::vector<int> status(n + 1); // 0, 1, 2
	i64 ans = 0;
	for (int i = 1; i <= w; i ++) {
		int op = 0, min = 1e9, p, q;
		// op1
		while (q1.size() && status[q1.top()[1]] != 0) q1.pop();
		if (q1.size() && q1.top()[0] < min) {
			min = q1.top()[0];
			op = 1;
			p = q1.top()[1];
		}
		// op2
		while (q2.size() && status[q2.top()[1]] != 1) q2.pop();
		if (q2.size() && q2.top()[0] < min) {
			min = q2.top()[0];
			op = 2;
			p = q2.top()[1];
		}
		// op3
		while (q3.size() && status[q3.top()[1]] != 0) q3.pop();
		while (q4.size() && status[q4.top()[1]] != 1) q4.pop();
		if (q3.size() && q4.size() && q3.top()[0] + q4.top()[0] < min) {
			min = q3.top()[0] + q4.top()[0];
			op = 3;
			p = q3.top()[1];
			q = q4.top()[1];
		}
		// op4
		while (q3.size() && status[q3.top()[1]] != 0) q3.pop();
		while (q5.size() && status[q5.top()[1]] != 2) q5.pop();
		if (q3.size() && q5.size() && q3.top()[0] + q5.top()[0] < min) {
			min = q3.top()[0] + q5.top()[0];
			op = 4;
			p = q3.top()[1];
			q = q5.top()[1];
		}
		ans += min;
		if (op == 1) {
			status[p] = 1;
			q2.push({a[p][1] - a[p][0], p});
			q4.push({-a[p][0], p});
		} else if (op == 2) {
			status[p] = 2;
			q5.push({a[p][0] - a[p][1], p});
		} else if (op == 3) {
			status[p] = 2;
			status[q] = 0;
			q5.push({a[p][0] - a[p][1], p});

			q1.push({a[q][0], q});
			q3.push({a[q][1], q});
		} else {
			status[p] = 2;
			status[q] = 1;
			q5.push({a[p][0] - a[p][1], p});

			q2.push({a[q][1] - a[q][0], q});
			q4.push({-a[q][0], q});
		}
	}
	std::cout << ans << '\n';
	for (int i = 1; i <= n; i ++) {
		std::cout << status[i];
	}
	std::cout << '\n';
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