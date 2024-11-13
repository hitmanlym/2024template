#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 1e9 + 7;
struct Node {
	int l, r;
	mutable int v;
	Node(int l, int r = 0, int v = 0) : l(l), r(r), v(v) {}
	bool operator < (const Node &a) const {
		return l < a.l;
	}
};
struct Rank {
	int num, cnt;
	Rank(int num, int cnt) : num(num), cnt(cnt) {}
	bool operator < (const Rank &a) const {
		return num < a.num;
	}
};

int qmi(int a, int b, int MOD) {
    if (a == 0) return 0;
    int res = 1;
    while (b) {
        if (b & 1) {
            res = 1ll * res * a % MOD;
        }
        a = 1ll * a * a % MOD;
        b >>= 1;
    }
    return res;
}
void solve() {
	int n, m, seed, vmax;
	std::cin >> n >> m >> seed >> vmax;
	std::vector<int> a(n + 1);
	std::set<Node> st;
	auto rnd = [&]() -> int {
		int res = seed;
		seed = (seed * 7 + 13) % mod;
		return res;
	};
	for (int i = 1; i <= n; i ++) {
		a[i] = rnd() % vmax + 1;
		st.insert(Node(i, i, a[i]));
	}
	// 以 pos 作切割, 找到包含 pos 的区间, 分成 [l, pos - 1], [pos, r]
	auto split = [&](int pos) -> std::set<Node>::iterator {
		auto it = st.lower_bound(Node(pos));
		if (it != st.end() && it -> l == pos) {
			return it;
		}
		it --;
		if (it -> r < pos) return st.end();
		int l = it -> l, r = it -> r, v = it -> v;
		st.erase(it);
		st.insert(Node(l, pos - 1, v));
		return st.insert(Node(pos, r, v)).first;
	};
	// 先计算 itr, 后 itl, 可能释放 itl
	auto add = [&](int l, int r, int x) -> void {
		auto itr = split(r + 1);
		auto itl = split(l);
		for (auto i = itl; i != itr; i ++) {
			i -> v += x;
		}
	};

	auto assign = [&](int l, int r, int x) -> void {
		auto itr = split(r + 1);
		auto itl = split(l);
		st.erase(itl, itr);
		st.insert(Node(l, r, x)); // [)
	};
	auto rnk = [&](int l, int r, int x) -> int {
		auto itr = split(r + 1);
		auto itl = split(l);
		std::vector<Rank> v;
		for (auto i = itl; i != itr; i ++) {
			v.push_back(Rank(i -> v, i -> r - i -> l + 1));
		}
		std::sort(v.begin(), v.end());
		int i;
		for (i = 0; i < v.size(); i ++) {
			if (v[i].cnt < x) {
				x -= v[i].cnt;
			} else {
				break;
			}
		}
		return v[i].num;
	};

	auto calc = [&](int l, int r, int x, int y) -> int {
		auto itr = split(r + 1);
		auto itl = split(l);
		int ans = 0;
		for (auto i = itl; i != itr; i ++) {
			ans = (ans + qmi((i -> v) % y, x, y) * (i -> r - i -> l + 1) % y) % y;
		}
		return ans;
	};

	for (int i = 1; i <= m; i ++) {
		int op, l, r, x, y;
		op = rnd() % 4 + 1;
		l = rnd() % n + 1;
		r = rnd() % n + 1;
		if (l > r) std::swap(l, r);

		if (op == 3) {
			x = rnd() % (r - l + 1) + 1;
		} else {
			x = rnd() % vmax + 1;
		}
		if (op == 4) {
			y = rnd() % vmax + 1;
		}

		if (op == 1) {
			add(l, r, x);
		} else if (op == 2) {
			assign(l, r, x);
		} else if (op == 3) {
			for (auto it : st) {
			}
			std::cout << rnk(l, r, x) << '\n';
		} else {
			//std::cout << "!!!\n";
			std::cout << calc(l, r, x, y) << '\n'; // sigma( v^x )% y
		}
	}
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