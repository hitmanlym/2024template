#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int N = 5e5 + 10;
// 堆+Tire
/*
给定长度为n的序列a_i
一个区间[l,r]的价值为从a_l到a_r之间的每个数字进行的异或值。
求这个序列中价值最大的k个区间的价值和。
*/

namespace Tire {
	struct {
		int id, s, ch[2];
	} e[N * 100];
	int cnt = 1, rt[N];

	void insert(int &p, int pre, int bit, int id, int val) {
		p = ++ cnt;
		e[p] = e[pre], ++ e[p].s;
		if (bit == -1) {
			e[p].id = id;
			return ;
		}
		int b = (val >> bit) & 1;
		insert(e[p].ch[b], e[pre].ch[b], bit - 1, id, val);
	}
	int query(int l, int r, int bit, int val) {
		if (bit == -1) {
			return e[r].id;
		}
		int b = (val >> bit) & 1;
		if (e[e[r].ch[b ^ 1]].s > e[e[l].ch[b ^ 1]].s) {
			return query(e[l].ch[b ^ 1], e[r].ch[b ^ 1], bit - 1, val);
		} else {
			return query(e[l].ch[b], e[r].ch[b], bit - 1, val);
		}
	}
}
using namespace Tire;

std::vector<int> sum(N + 1);

struct node {
	int st, l, r, pos;
	bool operator < (const node a) const {
		return (sum[pos] ^ sum[st - 1]) < (sum[a.pos] ^ sum[a.st - 1]);
	}
	node(int _st, int _l, int _r) {
		st = _st;
		l = _l;
		r = _r;
		pos = query(rt[l - 1], rt[r], 32, sum[st - 1]);
	}
};
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::priority_queue<node> q;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; i ++) {
		sum[i] = sum[i - 1] ^ a[i];
	}
	for (int i = 1; i <= n; i ++) {
		insert(rt[i], rt[i - 1], 32, i, sum[i]);
	}
	for (int i = 1; i <= n; i ++) {
		q.push(node(i, i, n));
	}
	int ans = 0;
	while (m --) {
		node it = q.top();
		q.pop();
		ans += sum[it.pos] ^ sum[it.st - 1];
		if (it.l < it.pos) {
			q.push(node(it.st, it.l, it.pos - 1));
		}
		if (it.pos < it.r) {
			q.push(node(it.st, it.pos + 1, it.r));
		}
	}
	std::cout << ans << '\n';
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}