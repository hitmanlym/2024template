#include<bits/stdc++.h>
using i64 = long long;

const int mod = 1e9 + 7;
struct invMatrix {
	int n;
	std::vector<std::vector<int> > M;
	invMatrix() {}
	void init(int n, std::vector<std::vector<int> > &X) {
		this -> n = n;
		M.assign(n + 1, std::vector<int>(n * 2 + 1, 0));
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= n; j ++) {
				M[i][j] = X[i][j];
			}
			M[i][i + n] = 1;
		}
	}
	i64 exgcd(int a, int b, i64& x, i64& y) {
	    if (b == 0) {
	        x = 1, y = 0;
	        return a;
	    }
	    i64 d = exgcd(b, a % b, x, y);
	    i64 z = x;
	    x = y;
	    y = z - (a / b) * y;
	    return d;
	}
	std::vector<std::vector<int> > get() {
		std::vector<std::vector<int> > f;
		for (int i = 1; i <= n; i ++) {
			for (int j = i; j <= n; j ++) {
				if (M[j][i]) {
					for (int k = 1; k <= n * 2; k ++) {
						std::swap(M[i][k], M[j][k]);
					}
					break;
				}
			}
			if (! M[i][i]) {
				return f;
			}
			i64 inv, y;
			exgcd(M[i][i], mod, inv, y);
			inv = (inv % mod + mod) % mod;
			for (int j = i; j <= n * 2; j ++) {
				M[i][j] = M[i][j] * inv % mod;
			}
			for (int j = 1; j <= n; j ++) {
				if (j == i) continue;
				y = M[j][i];
				for (int k = i; k <= n * 2; k ++) {
					M[j][k] = (M[j][k] - y * M[i][k] % mod + mod) % mod;
				}
			}
		}
		f.assign(n + 1, std::vector<int>(n + 1, 0));
		for (int i = 1; i <= n; i ++) {
			for (int j = n + 1; j <= n * 2; j ++) {
				f[i][j - n] = M[i][j];
			}
		}
		return f;
	}
} tr;

void solve() { 
	int n;
	std::cin >> n;
	std::vector<std::vector<int> > a(n + 1, std::vector<int>(n + 1));
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			std::cin >> a[i][j];
		}
	}
	tr.init(n, a);
	auto it = tr.get();
	if (! it.size()) {
		std::cout << "No Solution\n";
		return ;
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			std::cout << it[i][j] << ' ';
		}
		std::cout << '\n';
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