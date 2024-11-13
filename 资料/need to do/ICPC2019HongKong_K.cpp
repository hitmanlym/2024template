#include<bits/stdc++.h>
using i64 = long long;

const i64 inf = 1e18;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> d(n);
	for (int i = 1; i < n; i ++) {
		std::cin >> d[i];
	}
	std::vector<std::vector<i64> > a(n + 1), b(n + 1);
	for (int i = 1; i <= m; i ++) {
		int x, c;
		std::cin >> x >> c;
		a[x].push_back(c);
	}
	for (int i = 1; i <= m; i ++) {
		int x, c;
		std::cin >> x >> c;
		b[x].push_back(c);
	}
	for (int i = 1; i <= n; i ++) {
		a[i].push_back(inf);
		b[i].push_back(inf);
		std::sort(a[i].begin(), a[i].end(), [&](auto x, auto y) {
			return x > y;
		});
		std::sort(b[i].begin(), b[i].end(), [&](auto x, auto y) {
			return x > y;
		});
	}
	std::vector<int> flows(n);

	auto lr = [&](int &x, int &y) -> i64 {
		i64 res = a[1].back() + b[1].back();
		x = y = 1;
		int pre = 1;
		i64 preval = a[1].back();
		for (int i = 2; i <= n; i ++) {
			preval = preval + (flows[i - 1] >= 0 ? d[i - 1] : -d[i - 1]);
			if (a[i].back() < preval) {
				pre = i;
				preval = a[i].back();
			}
			if (preval + b[i].back() < res) {
				res = preval + b[i].back();
				x = pre;
				y = i;
			}
		}
		return res;
	};
	auto rl = [&](int &x, int &y) -> i64 {
		i64 res = a[n].back() + b[n].back();
		x = y = n;
		int pre = n;
		i64 preval = a[n].back();
		for (int i = n - 1; i >= 1; i --) {
			preval = preval + (flows[i] <= 0 ? d[i] : -d[i]);
			if (a[i].back() < preval) {
				pre = i;
				preval = a[i].back();
			}
			if (preval + b[i].back() < res) {
				res = preval + b[i].back();
				x = pre;
				y = i;
			}
		}
		return res;
	};

	i64 ans = 0;
	for (int i = 1; i <= m; i ++) {
		int lx, ly, rx, ry;
		i64 lres, rres;
		lres = lr(lx, ly); // a_x. b_y
		rres = rl(rx, ry); // b_y. a_x
		ans += std::min(lres, rres);
		if (lres <= rres) {
			a[lx].pop_back();
			b[ly].pop_back();
			for (int j = lx; j < ly; j ++) {
				flows[j] ++;
			}
		} else {
			a[rx].pop_back();
			b[ry].pop_back();
			for (int j = ry; j < rx; j ++) {
				flows[j] --;
			}
		}
		std::cout << ans << '\n';
	}
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}