#include<bits/stdc++.h>
using i64 = long long;

int mod;
struct W { // 行列式
	int n;
	std::vector<std::vector<int> > a;
	void init(int n, std::vector<std::vector<int> > &X) {
		this -> n = n;
		a.assign(X.begin(), X.end());
	}
	int get() {
		i64 ans = 1, v = 1;
		for (int i = 1; i <= n; i ++) {
			for (int j = i + 1; j <= n; j ++) {
				while (a[i][i]) {
					i64 x = a[j][i] / a[i][i];
					for (int k = i; k <= n; k ++) {
						a[j][k] = (a[j][k] - x * a[i][k] % mod + mod) % mod;
					}
					std::swap(a[i], a[j]);
					v = -v;
				}
				std::swap(a[i], a[j]);
				v = -v;
			}
		}
		for (int i = 1; i <= n; i ++) {
			ans = ans * a[i][i] % mod;
		}
		return (ans * v + mod) % mod;
	}
} tr;

void solve() {
	int n;
	std::cin >> n >> mod;
	std::vector<std::vector<int> > a(n + 1, std::vector<int>(n + 1));
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			std::cin >> a[i][j];
		}
	}
	tr.init(n, a);
	int res = tr.get();
	std::cout << res << '\n';
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