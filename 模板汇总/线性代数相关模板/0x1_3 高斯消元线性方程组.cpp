#include<bits/stdc++.h>
using i64 = long long;
using db = double;


const db eps = 1e-5;
struct Guess {
	int n;
	std::vector<std::vector<db>> a;
	std::vector<db> b;

	Guess() {}
	void init(int n, std::vector<std::vector<db>> x, std::vector<db> y) {
		this -> n = n;
		a.assign(n + 1, {});
		b.assign(y.begin(), y.end());
		for (int i = 1; i <= n; i ++) {
			a[i].assign(x[i].begin(), x[i].end());
		}
	}
	int work() {
		int l = 1;
		for (int i = 1; i <= n; i ++) {
			int fg = l;   
			for (int j = l; j <= n; j ++) {
				if (std::fabs(a[j][i]) > std::fabs(a[l][i])) {
					l = j;
				}
			}
			for (int k = i; k <= n; k ++) {
				std::swap(a[l][k], a[fg][k]);
			}
			std::swap(b[l], b[fg]);
			l = fg;
			if (std::fabs(a[l][i]) < eps) {
				continue;
			}

			for (int j = 1; j <= n; j ++) {
				if (j != l && std::fabs(a[j][i]) > eps) {
					db delta = a[j][i] / a[l][i];
					for (int k = i; k <= n; k ++) {
						a[j][k] -= delta * a[l][k];
					}
					b[j] -= delta * b[l];
				}
			}
			l ++;
		}
		
		int f = 0;
		for (int i = l; i <= n; i ++) {	// 无解
			if (std::fabs(b[i]) > eps) {
				f = -1;
				break;
			}
		}
		if (f != -1 && l <= n) {	// 无穷多解
			f = -2;
		}
		if (f == 0) {
			for (int i = 1; i <= n; i ++) {
				b[i] /= a[i][i]; // b[i] is the ans
				a[i][i] = 1.0;
			}
		}
		return f;
	}
};

void solve() {
	int n;
	std::cin >> n;
	std::vector<std::vector<db>> a(n + 1, std::vector<db>(n + 1));
	std::vector<db> b(n + 1);
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			std::cin >> a[i][j];
		}
		std::cin >> b[i];
	}

	Guess t;
	t.init(n, a, b);
	int f = t.work();
	if (f == 0) {
		for (int i = 1; i <= n; i ++) {
			printf("x%d=%.2lf\n", i, t.b[i]);
		}
	} else {
		//std::cout << "No Solution\n";
		if (f == -1) std::cout << f << '\n';
		else std::cout << 0 << '\n';
	}
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}