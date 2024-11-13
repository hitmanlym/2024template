#include<bits/stdc++.h>
using i64 = long long;
struct Dikaer {
	int n, ans;
	std::vector<std::vector<int>> st;
	std::vector<int> a, b;
	Dikaer() {}

	void init(int n, std::vector<int> s, std::vector<int> t) {
		this -> n = n;
		st.assign(n + 1, std::vector<int>(std::__lg(n) + 1));
		a.assign(s.begin(), s.end());
		b.assign(t.begin(), t.end());
		ans = 0;

		Pre();
	}
	int cmp(int x, int y) {
		return a[x] > a[y] ? x : y;
	}

	void Pre() {
		for (int i = 1; i <= n; i ++) {
			st[i][0] = i;
		}
		for (int j = 1; j <= std::__lg(n); j ++) {
			for (int i = 1; i <= n; i ++) {
				if (i + (1 << j) - 1 > n) break;
				st[i][j] = cmp(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
			}
		}
	}
	int rmq(int l, int r) {
		int x = std::__lg(r - l + 1);
		return cmp(st[l][x], st[r - (1 << x) + 1][x]);
	}
	void work(int l, int r) {
		if (l >= r) return ;
		int mid = rmq(l, r), sum = a[mid];
		if (r - mid > mid - l) {
			for (int i = l; i < mid; i ++) {
				int to = b[sum - a[i]];

				ans += (to > mid && to <= r);
			}
		} else {
			for (int i = mid + 1; i <= r; i ++) {
				int to = b[sum - a[i]];
				ans += (to >= l && to < mid);
			}
		}
		work(l, mid - 1);
		work(mid + 1, r);
	}
};
void solve() { // 排列中 [l, r] 满足 a[l] + a[r] = max{a[k]} (k \in [l, r])
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		b[a[i]] = i;
	}
	Dikaer t;
	t.init(n, a, b);
	t.work(1, n);
	int ans = t.ans;
	std::cout << ans << '\n';
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
/*
#include<bits/stdc++.h>
using i64 = long long;
struct Dikaer {
	int n, ans;
	std::vector<std::vector<int>> st;
	std::vector<int> a, maxpre, minnxt;
	Dikaer() {}

	void init(int n, std::vector<int> s, std::vector<int> t, std::vector<int> r) {
		this -> n = n;
		st.assign(n + 1, std::vector<int>(std::__lg(n) + 1));
		a.assign(s.begin(), s.end());
		maxpre.assign(t.begin(), t.end());
		minnxt.assign(r.begin(), r.end());
		ans = 0;

		Pre();
	}
	int cmp(int x, int y) {
		return a[x] > a[y] ? x : y;
	}

	void Pre() {
		for (int i = 1; i <= n; i ++) {
			st[i][0] = i;
		}
		for (int j = 1; j <= std::__lg(n); j ++) {
			for (int i = 1; i <= n; i ++) {
				if (i + (1 << j) - 1 > n) break;
				st[i][j] = cmp(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
			}
		}
	}
	int rmq(int l, int r) {
		int x = std::__lg(r - l + 1);
		return cmp(st[l][x], st[r - (1 << x) + 1][x]);
	}
	void work(int l, int r) {
		if (l > r) return ;
		if (l == r) {
			ans += (a[l] == 1);
			return ;
		}
		int mid = rmq(l, r), max = a[mid];
		if (r - mid > mid - l) {
			for (int i = l; i <= mid; i ++) {
				int j = i + max - 1;
				if (j < mid || j > r || j >= minnxt[i]) continue;
				ans ++;
			}
		} else {
			for (int i = mid; i <= r; i ++) {
				int j = i - max + 1;
				if (j < l || j > mid || j <= maxpre[i]) continue;
				ans ++;
			}
		}
		work(l, mid - 1);
		work(mid + 1, r);
	}
};
void solve() { // 排列中满足 [l, r] 中元素为 {1, 2, ... r - l + 1}
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), pos(n + 1), pre(n + 1), nxt(n + 1), maxpre(n + 1), minnxt(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; i ++) {
		pre[a[i]] = pos[a[i]];
		pos[a[i]] = i;
		maxpre[i] = std::max(maxpre[i - 1], pre[a[i]]);
	}
	std::fill(pos.begin(), pos.end(), n + 1);
	for (int i = n; i >= 1; i --) {
		nxt[a[i]] = pos[a[i]];
		pos[a[i]] = i;
		if (i == n) minnxt[i] = nxt[a[i]];
		else minnxt[i] = std::min(minnxt[i + 1], nxt[a[i]]);
	}

	Dikaer t;
	t.init(n, a, maxpre, minnxt);
	t.work(1, n);
	int ans = t.ans;
	std::cout << ans << '\n';
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
*/