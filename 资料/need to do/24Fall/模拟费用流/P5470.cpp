#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
void solve() {
	int n, k, l;
	std::cin >> n >> k >> l;
	std::vector<pii> a(n + 1);
	std::priority_queue<pii> p1, p2;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i][0];
		p1.push({a[i][0], i});
	}
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i][1];
		p2.push({a[i][1], i});
	}
	int ans = 0;
	std::vector<int> status(n + 1); // 0, 1, 2, 3
	for (int i = 1; i <= k; i ++) {
		auto x = p1.top();
		auto y = p2.top();
		p1.pop(), p2.pop();
		ans += x[0] + y[0];
		status[x[1]] |= 1;
		status[y[1]] |= 2;
	}
	int res = l;
	std::priority_queue<pii, std::vector<pii>, std::less<pii> >
		q1, q2, q3, q4, q5, q6;
	for (int i = 1; i <= n; i ++) {
		if (status[i] == 3) {
			res --;
		}
		if (status[i] == 0) {
			q5.push({a[i][0] + a[i][1], i});
		} else if (status[i] == 1) {
			q2.push({-a[i][0], i});
			q3.push({a[i][1], i + n});
		} else if (status[i] == 2) {
			q4.push({-a[i][1], i + n});
			q1.push({a[i][0], i});
		} else {
			q6.push({-a[i][0] - a[i][1], i});
		}
	}
	for (int i = 1; i <= res; i ++) { // roll back
		int min = -1e15, op = 0, p, q, r;
		while (q1.size() && status[q1.top()[1]] != 2) q1.pop();
		while (q2.size() && status[q2.top()[1]] != 1) q2.pop();
		while (q3.size() && status[q3.top()[1] - n] != 1) q3.pop();
		while (q4.size() && status[q4.top()[1] - n] != 2) q4.pop();
		while (q5.size() && status[q5.top()[1]] != 0) q5.pop();
		while (q6.size() && status[q6.top()[1]] != 3) q6.pop();
		if (q1.size() && q2.size() && q1.top()[0] + q2.top()[0] > min) {
			min = q1.top()[0] + q2.top()[0];
			p = q1.top()[1];
			q = q2.top()[1];
			op = 1;
		}
		if (q3.size() && q4.size() && q3.top()[0] + q4.top()[0] > min) {
			min = q3.top()[0] + q4.top()[0];
			p = q3.top()[1] - n;
			q = q4.top()[1] - n;
			op = 2;
		}
		if (q5.size() && q2.size() && q4.size() && q5.top()[0] + q2.top()[0] + q4.top()[0] > min) {
			min = q5.top()[0] + q2.top()[0] + q4.top()[0];
			p = q2.top()[1];
			q = q4.top()[1] - n;
			r = q5.top()[1];
			op = 3;
		}
		if (q6.size() && q1.size() && q3.size() && q6.top()[0] + q1.top()[0] + q3.top()[0] > min) {
			min = q6.top()[0] + q1.top()[0] + q3.top()[0];
			p = q1.top()[1];
			q = q3.top()[1] - n;
			r = q6.top()[1];
			op = 4;
		}
		assert(min <= 0);
		ans += min;

		if (op == 1) {
			status[p] = 3;
			status[q] = 0;
			q5.push({a[q][0] + a[q][1], q});
			q6.push({-a[p][0] - a[p][1], p});
		} else if (op == 2) {
			status[p] = 3;
			status[q] = 0;
			q5.push({a[q][0] + a[q][1], q});
			q6.push({-a[p][0] - a[p][1], p});
		} else if (op == 3) {
			status[p] = 0;
			status[q] = 0;
			status[r] = 3;
			q5.push({a[p][0] + a[p][1], p});
			q5.push({a[q][0] + a[q][1], q});
			q6.push({-a[r][0] - a[r][1], r});
		} else {
			status[p] = 3;
			status[q] = 3;
			status[r] = 0;
			q5.push({a[r][0] + a[r][1], r});
			q6.push({-a[p][0] - a[p][1], p});
			q6.push({-a[q][0] - a[q][1], q});
		}
		// std::cout << "??? " << ans << ' ' << op << ' ' << min << '\n';
		// std::cout << "!!! " << p << ' ' << q << ' ' << r << '\n';
		// for (int i = 1; i <= n; i ++) {
		// 	std::cout << status[i] << ' ';
		// }
		// std::cout << '\n';
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