#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int inf = 1e18;
struct event {
	int pos, num, val;
	friend bool operator < (const event& A, const event& B) {
		return A.pos < B.pos;
	}
};
struct data {
	int num, val;
	data(int num = 0, int val = 0) {
		this -> num = num;
		this -> val = val;
	}
	friend bool operator < (const data& A, const data& B) {
		return A.val > B.val;
	}
};
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<event> a(n + m + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i].pos;
		a[i].num = 1, a[i].val = -1;
	} 
	int sum = 0, ans = 0;
	for (int i = n + 1; i <= n + m; i ++) {
		std::cin >> a[i].pos >> a[i].val >> a[i].num;
		sum += a[i].num;
	}
	if (sum < n) {
		std::cout << -1 << '\n';
		return ;
	}
	std::sort(a.begin() + 1, a.end());

	std::priority_queue<data> A, B;
	A.push(data(n, inf));
	for (int i = 1; i <= n + m; i ++) {
		if (a[i].val == -1) { // 兔子
			data it = A.top();
			A.pop();
			ans += it.val + a[i].pos;
			it.num --;
			if (it.num) {
				A.push(it);
			}
			B.push(data(1, -it.val - 2ll * a[i].pos));
		} else {
			int NUM = a[i].num, select = 0;
			while (NUM && ! B.empty()) {
				data it = B.top();
				if (it.val + a[i].pos + a[i].val >= 0) break;
				B.pop();
				int use = std::min(NUM, it.num);
				it.num -= use;
				NUM -= use;
				select += use;
				ans += use * (it.val + a[i].pos + a[i].val);
				if (it.num) {
					B.push(it);
				}
				A.push(data(use, -it.val - 2ll * a[i].pos));
			}
			if (select) {
				B.push(data(select, -a[i].pos - a[i].val));
			} 
			if (NUM) {
				A.push(data(NUM, a[i].val - a[i].pos));
			}
		}
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