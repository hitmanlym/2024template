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

void solve() { /*
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
	}*/
	int n;
	std::cin >> n;
	Matrix a;
	a.init(5);
	a.M[1][1] = a.M[1][2] = a.M[2][1] = a.M[3][3] = a.M[3][4] = a.M[4][3] = a.M[5][5] = 1;
	a.M[1][3] = 2;
	a.M[1][5] = -2;
	if (n <= 2) {
		std::cout << 0 << '\n';
		return ;
	}
	Matrix res = qmi(a, n - 2);
	int ans = 0;
	std::vector<int> b(5 + 1);
	b[3] = 2, b[4] = b[5] = 1; 
	for (int i = 1; i <= 5; i ++) {
		ans += 1ll * res.M[1][i] * b[i] % mod;
		ans %= mod;
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