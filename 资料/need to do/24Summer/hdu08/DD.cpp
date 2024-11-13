#include<bits/stdc++.h>
using i64 = long long;
#define int __int128
using pii = std::array<int, 2>;
void solve() {
	i64 n;
	std::cin >> n;
	std::vector<std::array<i64, 5> > a(n + 1);
	std::vector<std::array<int, 3> > ans(n + 1);
	std::vector<bool> d(n + 1);
	std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
	std::queue<pii> death;
	int num = 0;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i][0];
		if (a[i][0] == 1) {
			std::cin >> a[i][1];
			ans[i] = {a[i][1], 0, 0};
		}
		if (a[i][0] == 2) {
			std::cin >> a[i][1] >> a[i][2] >> a[i][3];
			ans[i] = {1, a[i][2], a[i][1]};
		}
		if (a[i][0] == 3) {
			std::cin >> a[i][1];
			num ++;
			ans[i] = {a[i][1], 0, 0};
		}
		a[i][4] = i;
		if (i > 1) {
			q.push({a[i][1], i});
		}
	}
	death.push({a[1][0], 1});
	if (a[1][0] != 2) ans[1] = {0, 0, 0}; /// ----------

	int total = 0;
	while (death.size()) {
		std::vector<pii> op;
		auto top = death.front();
		d[top[1]] = 1;
		death.pop();

		if (top[0] == 1) {
			ans[top[1]][0] = 0;
			int h = total + num + 1;
			total += num + 1;
			while (q.size() && q.top()[0] <= h) {
				//std::cout << "IF? " << q.top()[1] << '\n';
				auto it = q.top();
				q.pop();
				int id = it[1];
				if (a[id][0] == 3) {
					num --;
					d[id] = 1;
					ans[id][0] = 0;
					continue;
				} else {
					op.push_back({id, a[id][0]});
				}
			}
		} else if (top[0] == 2) {
			int id = top[1];
			if (ans[id][1] == 0) {
				ans[id] = {0, 0, 0};
				d[id] = 1;
				continue;
			}
			auto it = ans[id];
			//std::cout << "??? " << a[id][1] << '\n';
			ans[id] = {a[id][3] * it[0], it[1] - 1, it[2] * 2};
			q.push({ans[id][2] + total, id});
		}
		std::sort(op.begin(), op.end());
		for (auto it : op) {
			death.push({it[1], it[0]});
		}
	}
	while (q.size()) {
		auto it = q.top(); // 生命值和编号
		q.pop();
		int id = it[1], h = it[0];
		if (a[id][0] == 2) {
			ans[id][2] = h - total;
		} else {
			ans[id][0] = h - total;
		}
	}
    auto print128 = [](__int128_t x) -> void
    {
        if (!x)
        {
            std::cout << 0;
            return;
        }
        bool fg = (x < 0);
        if (fg)
            x = -x;
        std::vector<i64> dig;
        while (x)
        {
            dig.push_back(x % 10);
            x /= 10;
        }
        std::reverse(dig.begin(), dig.end());
        if (fg)
            std::cout << '-';
        for (i64 i : dig)
            std::cout << i;
    };

	for (int i = 1; i <= n; i ++) {
		if (a[i][0] == 2) {
            print128(ans[i][0]);
            std::cout << ' ';
            print128(ans[i][1]);
            std::cout << ' ';
            print128(ans[i][2]);
            std::cout << '\n';
			//std::cout << ans[i][0] << ' ' << ans[i][1] << ' ' << ans[i][2] << '\n';
		} else {
            print128(ans[i][0]);
			std::cout << '\n';
		}
	}
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	i64 t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}