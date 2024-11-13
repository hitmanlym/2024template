#include<bits/stdc++.h>
using i64 = long long;
struct Basis {
    std::vector<int> a, map;
    int n, basecnt;
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
    bool have(int x) {
    	for (int i = n - 1; i >= 0; i --) {
            if (! (x >> i & 1)) continue;
            if (a[i]) x ^= a[i];
            else {
                return false;
            }
        }
        return true;
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
std::vector<int> minp, primes;
void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}
struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n + 1);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};
std::vector<int> rev(1e7 + 1);
void solve() {
	sieve(1e7 + 1);
	int siz = primes.size();
	for (int i = 0; i < siz; i ++) {
		rev[primes[i]] = i + 1;
	}
	DSU t(siz);
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), p(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		int it = minp[a[i]];
		int now = a[i];
		if (! it) continue;
		while (now % it == 0) now /= it;
		while (minp[now]) {
			t.merge(rev[it], rev[minp[now]]);
			it = minp[now];
			while (now % it == 0) {
				now /= it;
			}
		}
	}
	std::vector<Basis> rev2(siz + 1);
	for (int i = 1; i <= siz; i ++) {
		rev2[i].init(24);
	}

	for (int i = 1; i <= n; i ++) {
		std::cin >> p[i];
		int it = minp[a[i]];
		if (it) {
			int res = t.find(rev[it]);
			rev2[res].insert(p[i]);
		}
	}
	int m;
	std::cin >> m;
	while (m --) {
		int u, v, w;
		std::cin >> u >> v >> w;
		u = minp[u], v = minp[v];
		if (! u || ! v) {
			std::cout << "No\n";
			continue;
		}
		u = rev[u], v = rev[v];
		if (! t.same(u, v)) {
			std::cout << "No\n";
			continue;
		}
		int fa = t.find(u);
		if (rev2[fa].have(w)) {
			std::cout << "Yes\n";
		} else {
			std::cout << "No\n";
		}
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