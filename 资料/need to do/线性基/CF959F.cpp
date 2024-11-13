#include<bits/stdc++.h>
using i64 = long long;
#define int i64

struct Basis {
    std::vector<int> a, map;
    int n, basecnt = 0;
    int sizofarr; // must set.
    bool zero;
    Basis() {}
    void init(int n) {
    	this -> n = n;
    	a.assign(n, 0);
    	map.clear();
    }
    bool insert(int x) {
    	for (int i = n - 1; i >= 0; i --) {
    		if (! (x >> i & 1)) continue;
    		if (a[i]) x ^= a[i];
    		else {
    			for (int j = 0; j < i; j ++) {
    				if (a[j] && (x >> j & 1)) {
    					x ^= a[j];
    				}
    			}
    			for (int j = i + 1; j < n; j ++) {
    				if (a[j] >> i & 1) {
    					a[j] ^= x;
    				}
    			}
    			a[i] = x;
    			basecnt ++;
    			return true;
    		}
    	}
    	return false;
    }
    void build(std::vector<int> b, int siz) {
    	sizofarr = siz;
    	basecnt = 0, zero = 0;
    	for (int i = 1; i <= siz; i ++) {
    		insert(b[i]);
    	}
    	zero = (basecnt != sizofarr); // 是否有零行
    	for (int i = 0; i < n; i ++) {
    		if (a[i]) map.push_back(i);
    	}// 对应下标，方便
    }

    int query_max() {
    	int res = 0;
    	for (int i = 0; i < n; i ++) {
    		res ^= a[i];
    	}
    	return res;
    }

    int query_min() {
    	zero = (basecnt != sizofarr);
    	if (zero) return 0;
    	if (! map.size()) return -1;
    	return a[map[0]];
    }

    int query_kth(int k) { // kth_small
    	zero = (basecnt != sizofarr);
    	int res = 0;
    	if (zero) k --;
    	int siz = map.size();
    	if (k >= (1ll << siz)) return -1; 
    	for (int i = 0; i < siz; i ++) {
    		if (k >> i & 1) {
    			res ^= a[map[i]];
    		}
    	}
    	return res;
    }

    int query_rank(int x) {
		zero = (basecnt != n);
		int siz = map.size(), res = zero;
		res = 0; // 本题,空为0
		for (int i = 0; i < siz; i ++) {
			if (x >> map[i] & 1) {
				res += 1ll << i;
			}
		}
		return res;
    }

    bool check_in(int x) {
    	for (int i = n - 1; i >= 0; i --) {
    		if (x >> i & 1) x ^= a[i];
    	}
    	return x == 0;
    }

    void mergeFrom(const Basis &other) {
    	for (int i = 0; i < n; i ++) {
    		int it = other.a[i];
    		if (it) insert(it);
    	}
    }
    friend Basis operator +(const Basis &a, const Basis &b) {
    	Basis res = a;
    	int X = res.n;
    	for (int i = 0; i < X; i ++) {
    		int it = b.a[i];
    		if (it) res.insert(it);
    	}
    	return res;
    } // 用于线段树维护线性基
};
const int mod = 1e9 + 7;
int qmi(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) {
			res = res * a % mod;
		}
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
void solve() {
	int n, q;
	std::cin >> n >> q;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	std::vector<std::array<int, 3> > b(q);
	for (int i = 0; i < q; i ++) {
		std::cin >> b[i][0] >> b[i][1];
		b[i][2] = i + 1;
	}
	std::vector<int> ans(q + 1);
	std::sort(b.begin(), b.end());
	int l = 1;
	Basis t;
	t.init(21);
	for (int i = 0; i < q; i ++) {
		while (l <= b[i][0]) {
			t.insert(a[l]);
			l ++;
		}
		int res = 0;
		if (t.check_in(b[i][1])) {
			res = qmi(2, l - 1 - t.basecnt);
		} 
		ans[b[i][2]] = res;
	}
	for (int i = 1; i <= q; i ++) {
		std::cout << ans[i] << '\n';
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