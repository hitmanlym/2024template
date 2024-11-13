#include<bits/stdc++.h>
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
const int N = 5e4 + 10;
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::bitset<N> g[n + 1];
	std::vector<int> col(n + 1);
	DSU d(n);
	int cntW = 0, cntB = 0;
	for (int i = 1; i <= n; i ++) {
		std::cin >> col[i];
		if (col[i] == 0) {
			cntW ++;
		} else {
			cntB ++;
		}
	}
	while (m --) {
		int op, x, y;
		std::cin >> op;
		if (op == 1) {
			std::cin >> x >> y;
			int px = d.find(x), py = d.find(y);
			if (px == py) {
				continue;
			} else {
				if (col[px] == col[py]) {
					d.merge(px, py);
					g[px] |= g[py];
					if (col[x] == 0) {
						cntW --;
					} else {
						cntB --;
					}
				} else {
					g[px][y] = 1;
					g[py][x] = 1;
				}
			}
		} 
		if (op == 2) {
			std::cin >> x;
			if (x == 0) {
				std::cout << cntW << '\n';
			} else {
				std::cout << cntB << '\n';
			}
		}
		if (op == 3) {
			std::cin >> x >> y;
			int px = d.find(x), py = d.find(y);
			if (px == py) {
				std::cout << -1 << '\n';
			} else {
				std::cout << (g[px] & g[py]).count() << '\n';
			}
		}
	}
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