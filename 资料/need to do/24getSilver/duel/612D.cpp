#include<bits/stdc++.h>
using i64 = long long;
const int mod = 998244353;
const int inf = -2e9;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::array<int, 2> > a(n + 1);
	std::map<int, std::vector<int> > stt;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i][0] >> a[i][1];
		stt[a[i][0]].push_back(a[i][1]);
	}
	std::vector<std::array<int, 2> > ans;
	std::priority_queue<int, std::vector<int>, std::greater<int> > q;
	int now = 0;
	int st = inf, lst = inf;
	for (auto it : stt) {
		std::sort(it.second.begin(), it.second.end());
		int v = it.first;
		while (q.size() && q.top() < v) {
			if (now >= m && st != inf) {
				lst = q.top();
			}
			q.pop();
			now --;
		}
		if (now < m && st != inf) {
			ans.push_back({st, lst});
			st = inf;
			lst = inf;
		}

		// for (auto it : it.second) {
		// 	if (it != v) break;
		// 	now ++;
		// 	q.push(v);
		// 	if (now >= m) {
		// 		if (st == inf) st = v;
		// 		lst = v;
		// 	}
		// 	break;
		// }
		for (auto it : it.second) {
			// if (it == v) continue;
			now ++;
			q.push(it);
		}
		if (now >= m) {
			if (st == inf) st = v;
			lst = v;
		}
		// std::cout << now << ' ' << st << ' ' << lst << '\n';
	}
	while (q.size()) {
		if (now >= m && st != inf) {
			lst = q.top();
		} else {
			break;
		}
		q.pop();
		now --;
	}
	if (st != inf) {
		ans.push_back({st, lst});
	}
	std::cout << ans.size() << '\n';
	for (auto it : ans) {
		std::cout << it[0] << ' ' << it[1] << '\n';
	}
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