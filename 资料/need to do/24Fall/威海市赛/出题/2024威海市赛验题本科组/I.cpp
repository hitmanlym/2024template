#include<bits/stdc++.h>
using i64 = long long;
const int M = 1001;
struct Matrix {
	int n;
	std::bitset<M> v[M];
	Matrix() {}
	void init(int n) {
		this -> n = n;
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= n; j ++) {
				v[i][j] = 0;
			}
		}
	}
	void norm() {
		for (int i = 1; i <= n; i ++) {
			v[i][i] = 1;
		}
	}
	Matrix friend operator * (const Matrix &a, const Matrix &b) {
		Matrix ans;
		int n = a.n;
		ans.init(n);
		for (int i = 1; i <= n; i ++) {
			for (int k = 1; k <= n; k ++) {
				if (a.v[i][k]) {
					ans.v[i] |= b.v[k];
				}
			}
		}
		return ans;
	}
};
Matrix qmi(Matrix a, i64 b) {
	Matrix ans;
	int n = a.n;
	ans.init(n);
	ans.norm();
	while (b) {
		if (b & 1) ans = ans * a;
		a = a * a;
		b >>= 1;
	}
	return ans;
}
void solve() {
	int n, m, k;
	std::cin >> n >> m;
	Matrix mp;
	mp.init(n);
	for (int i = 1; i <= m; i ++) {
		int u, v;
		std::cin >> u >> v;
		mp.v[u][v] = 1;
	}
	std::cin >> k;
	mp = qmi(mp, k);
	Matrix f;
	f.init(n);
	f.norm();
	f = f * mp;
	for (int i = 1; i <= n; i ++) {
		for (int k = 1; k <= n; k ++) {
			if (f.v[i][k]) {
				std::cout << i << ' ' << k << '\n';
			}
		}
	}
}
int main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}