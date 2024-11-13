#include<bits/stdc++.h>
using i64 = long long;

const int mod = 1e9 + 7;
struct Matrix {
	int n;
	std::vector<std::vector<int> > M;
	Matrix() {}
	void init(int n) {
		this -> n = n;
		M.assign(n + 1, std::vector<int>(n + 1, 0));
	}
	void norm() {
		for (int i = 1; i <= n; i ++) {
			M[i][i] = 1;
		}
	}
	Matrix friend operator * (const Matrix &a, const Matrix &b) {
		Matrix ans;
		int n = a.n;
		ans.init(n);
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= n; j ++) {
				for (int k = 1; k <= n; k ++) {
					ans.M[i][j] = (ans.M[i][j] + 1ll * a.M[i][k] * b.M[k][j]) % mod;
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
	int n;
	i64 k;
	std::cin >> n >> k;
	Matrix a;
	a.init(n);
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			std::cin >> a.M[i][j];
		}
	}
	Matrix res = qmi(a, k);
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			std::cout << res.M[i][j] << ' ';
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