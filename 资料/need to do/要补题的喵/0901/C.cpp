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
        basecnt = 0, zero = 0;
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
const int mod = 998244353;
int qmi(int a, int b) {
    if (a == 0) return 0;
    int res = 1;
    while (b) {
        if (b & 1) {
            res = 1ll * res * a % mod;
        }
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}
struct Comb {
    int n;
    std::vector<int> _fac, _invfac, _inv;
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    void init(int m) {
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i ++) {
            _fac[i] = 1ll * _fac[i - 1] * i % mod;
        }
        _invfac[m] = qmi(_fac[m], mod - 2);
        for (int i = m; i > n; i --) {
            _invfac[i - 1] = 1ll * _invfac[i] * i % mod;
            _inv[i] = 1ll * _invfac[i] * _fac[i - 1] % mod;
        }
        n = m;
    }
    int fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    int invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    int inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    int binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return 1ll * fac(n) * invfac(m) % mod * invfac(n - m) % mod;
    }
} comb;
void solve() { // no need zero check
    int n;
    std::cin >> n;
    std::vector<int> tp(n + 1);
    tp[0] = 1;
    for (int i = 1; i <= n; i ++) {
    	tp[i] = tp[i - 1] * 2 % mod;
    }
    std::vector<int> a(n + 1);
    Basis t;
    t.init(20);
    for (int i = 1; i <= n; i ++) {
    	std::cin >> a[i];
    	t.insert(a[i]);
    }
    //std::cout << t.basecnt << '\n';
    int ans = 0;
    ans = (ans + tp[n - t.basecnt] - 1) % mod;
    std::sort(a.begin() + 1, a.end());
    std::vector<int> c(n + 1);
    for (int i = 1; i <= n; i ++) {
    	c[a[i]] ++;
    }
    std::vector<std::vector<int> > d(n + 1);
    for (int i = 1; i <= n; i ++) {
    	if (! c[i]) continue;
    	for (int j = i * 2; j <= n; j += i) {
    		d[j].push_back(i);
    	}
    }
    for (int i = 1; i <= n; i ++) {
    	Basis fuck;
    	fuck.init(20);
    	int b = 0;
    	if (! c[i]) continue;
    	for (int j = 1; j <= c[i]; j += 2) {
    		b = (b + comb.binom(c[i], j)) % mod;
    	}
    	int tot = 0;
    	for (auto p : d[i]) {
    		//if (! c[p]) continue;
    		tot += c[p];
    		fuck.insert(p);
    	}
    	ans = (ans + 1ll * b * tp[2, tot - fuck.basecnt] % mod) % mod;
    }
    std::cout << ans << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}