#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	std::vector<std::array<i64, 2> > p(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; i ++) {
		p[i][0] = i;
		p[i][1] = p[i - 1][1] + a[i];
	}
	std::sort(p.begin() + 1, p.end());
	auto len2 = [&](int x, int y) -> i64 {
		return 1ll * (x - y) * (x - y);
	};
	auto dis = [&](auto x, auto y) -> i64 {
		return len2(x[0], y[0]) + len2(x[1], y[1]);
	};
	auto rev = [&](auto it) -> std::array<i64, 2> {
		std::array<i64, 2> res = {it[1], it[0]};
		return res;
	};
	i64 d = dis(p[1], p[2]);
	std::set<std::array<i64, 2> > st; // 用 y 来当第一维
	for (int r = 1, l = 1; r <= n; r ++) {
		auto op = rev(p[r]);
		while (d && d <= len2(p[l][0], p[r][0])) {
			st.erase(rev(p[l ++]));
		}
		auto it = st.lower_bound(op), k = it;
		while (k != st.end() && len2((*k)[0], op[0]) < d) {
			d = std::min(d, dis(*k, op));
			k ++;
		}
		k = it;
		while (k != st.begin()) {
			k --;
			if (len2((*k)[0], op[0]) >= d) break;
			d = std::min(d, dis(*k, op));
		}
		st.insert(op);
	}
	std::cout << d << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}