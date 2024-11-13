#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
#include<map>
#include<numeric>
using i64 = long long;
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
    void init(int n, std::vector<int> a, std::vector<int> b) {
    	//f.resize(n + 1);
        f.assign(a.begin(), a.end());
        siz.assign(b.begin(), b.end());
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

void solve() {
	int n, m, d, k;
	std::cin >> n >> m >> d >> k;
	std::vector<DSU> t(d + 2);
	t[0].init(n);
	i64 ans = 0;
	for (int i = 1; i <= m; i ++) {
		int u, v;
		std::cin >> u >> v;
		if (! t[0].same(u, v)) {
			ans += 1ll * t[0].size(u) * t[0].size(v);
			t[0].merge(u, v);
		}
	}
	for (int i = 1; i <= d + 1; i ++) {
		t[i].init(n, t[0].f, t[0].siz);
	}
	for (int i = 1; i <= k; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		if (! t[w].same(u, v)) {
			t[w].merge(u, v);
			bool f = 1;
			for (int i = 1; i <= d + 1; i ++) {
				if (! t[i].same(u, v)) {
					f = 0;
				}
			}
			if (f) {
				ans += 1ll * t[0].size(u) * t[0].size(v);
				t[0].merge(u, v);
			}
		}
		std::cout << ans << '\n';
	}
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